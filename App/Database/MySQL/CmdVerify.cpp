#include "Cmd.hpp"
#include <Comm/Utils/argparse.h>

namespace AppDatabaseMySQL {
    namespace Cmd {
        

        #if (CommOS==CommOS_WIN)
        #define CSV_PATH "Z:\\TESysRawData\\ExportCSV\\Monitor"
        #elif (CommOS==CommOS_LINUX)
        #define CSV_PATH "/home/hthwang/TESysRawData/ExportCSV/Monitor"
        #else
        #error "Select OS"
        #endif

        struct CsvRow {
            
            int boardID;
            int dutIdx;
            time_t utcTime;
            int jobDur;
            int tcDur;
            int tcStepDur;

            int jobID;
            int scID;
            int tcID;
            int tcStepID;
            char tcDesc[256];
            char tcStepDesc[256];

            float adcV[4][16];
            float adcA[4][16];

            unsigned short mipiErr;
            unsigned short t2mErr;
            unsigned short esdErr;
            unsigned short ptrnAppErr;
            unsigned long long sysErr;

            int chipID[5];
            int otpREV[6];

        };

#ifdef __STDC__
//#error "Stdc Version defined"

        
#endif

        static bool VerifyCsvWithDB_Job13(int jobID) {

            bool isVerifyOk = false;
            int verifyErr = 0;

            const int pwrGrpCnt = 5;
            const TESys::TED::PowerSource::Group grpEnum[pwrGrpCnt] = {
                TESys::TED::PowerSource::Group::External,
                TESys::TED::PowerSource::Group::External,
                TESys::TED::PowerSource::Group::Ldo,
                TESys::TED::PowerSource::Group::Reg,
                TESys::TED::PowerSource::Group::Sout
            };
            const bool grpIsVolt[pwrGrpCnt] = { true, false, true, true, true };

            const TESys::TED::PowerSource::Reg c_GrpRegCsvFmtOrder[] = {
                TESys::TED::PowerSource::Reg::VLOUT3_2,
                TESys::TED::PowerSource::Reg::VCI1,
                TESys::TED::PowerSource::Reg::VCIR,
                TESys::TED::PowerSource::Reg::VREG1,
                TESys::TED::PowerSource::Reg::VREG1OUT,
                TESys::TED::PowerSource::Reg::VREF1,
                TESys::TED::PowerSource::Reg::VBOT,
                TESys::TED::PowerSource::Reg::VGH,
                TESys::TED::PowerSource::Reg::VGL,
                TESys::TED::PowerSource::Reg::VINT,
                TESys::TED::PowerSource::Reg::VGHH,
                TESys::TED::PowerSource::Reg::VGLL,
                TESys::TED::PowerSource::Reg::VEH,
                TESys::TED::PowerSource::Reg::VAINT,
                TESys::TED::PowerSource::Reg::BML,
            };

            long long startTick = Comm::OAL::System::GetTickCount64();
            long long beforeTick = startTick;
            long long curTick;

            const int dutIndex = 0;
            std::shared_ptr<TESys::TED::VerifyBoard> verifyBoard = TESys::TED::VerifyBoard::Inst();
            std::shared_ptr<struct CsvRow> rowCsv = std::make_shared<struct CsvRow>();

            std::string strFilePathName = CSV_PATH;
            strFilePathName += Comm::Property::Path::GetFilePathDelimChar();
            strFilePathName += Comm::Utils::StringFormat("JOB_%04d.csv", jobID);

            const int bufMaxByteSize = 1024 * 16;
            char* buf = new char[bufMaxByteSize];
            assert(buf);

            FILE* fp;
            
            fp = fopen(strFilePathName.c_str(), "r");
            assert(fp);
            STDC_FSEEK64(fp, 0, SEEK_END);
            long long csvFileByteSize = STDC_FTELL64(fp);
            fclose(fp);

            
            fp = fopen(strFilePathName.c_str(), "r");
            assert(fp);

            //Header 읽기 
            fgets(buf, bufMaxByteSize, fp);

            //데이타 읽기
            while (true) {


                char* a, * b;
                char* p = fgets(buf, bufMaxByteSize, fp);
                if (p == NULL) {
                    break;
                }
                a = buf;

                //ChipID
                for (int i = 0; i < 5; i++) {
                    b = strchr(a, ',');
                    assert(b);
                    rowCsv->chipID[i] = strtol(a, &b, 16);
                    a = b + 1;
                }

                //BoardID
                b = strchr(a, ',');
                assert(b);
                rowCsv->boardID = strtol(a, &b, 10);
                a = b + 1;

                //DutIdx
                b = strchr(a, ',');
                assert(b);
                rowCsv->dutIdx = strtol(a, &b, 10);
                a = b + 1;

                //날짜, 시간 
                std::string dateTime;
                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                dateTime = a;
                dateTime += ' ';
                a = b + 1;

                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                dateTime += a;
                a = b + 1;
                rowCsv->utcTime = Comm::OAL::DateTime::GetUtcTime_KST_SqlFmtDateTime(dateTime);

                //JobDur
                b = strchr(a, ',');
                assert(b);
                rowCsv->jobDur = strtol(a, &b, 10);
                a = b + 1;

                //TcDur
                b = strchr(a, ',');
                assert(b);
                rowCsv->tcDur = strtol(a, &b, 10);
                a = b + 1;

                //TcStepDur
                b = strchr(a, ',');
                assert(b);
                rowCsv->tcStepDur = strtol(a, &b, 10);
                a = b + 1;

                //JobID
                b = strchr(a, ',');
                assert(b);
                rowCsv->jobID = strtol(a, &b, 10);
                a = b + 1;

                //ScID
                b = strchr(a, ',');
                assert(b);
                rowCsv->scID = strtol(a, &b, 10);
                a = b + 1;

                //TcID
                b = strchr(a, ',');
                assert(b);
                rowCsv->tcID = strtol(a, &b, 10);
                a = b + 1;

                //TcStepID
                b = strchr(a, ',');
                assert(b);
                rowCsv->tcStepID = strtol(a, &b, 10);
                a = b + 1;

                //TcDesc
                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                strcpy(rowCsv->tcDesc, a);
                a = b + 1;

                //TcStepDesc
                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                strcpy(rowCsv->tcStepDesc, a);
                a = b + 1;


                char szTmp[128];
                std::string strAdc;

                //ExtV
                for (int ipwr = 0; ipwr < pwrGrpCnt; ipwr++) {
                    int grpIdx, chCnt;
                    grpIdx = verifyBoard->AdcGetGroupIndexByEnum(dutIndex, grpEnum[ipwr]);
                    chCnt = verifyBoard->AdcGetChannelCount(dutIndex, grpEnum[ipwr]);

                    strAdc += "[";
                    for (int i = 0; i < chCnt; i++) {
                        b = strchr(a, ',');
                        assert(b);
                        *b = '\0';
                        float fadc = (float)atof(a);
                        if (grpIsVolt[ipwr]) {
                            rowCsv->adcV[grpIdx][i] = fadc;
                        }
                        else {
                            rowCsv->adcA[grpIdx][i] = fadc;
                        }
                        a = b + 1;

                        sprintf(szTmp, "%3.4f ", fadc);
                        strAdc += szTmp;
                    }
                    strAdc += "] ";
                }

                //RegV Rearrange
                {
                    const int regChannelCount = verifyBoard->AdcGetChannelCount(dutIndex, TESys::TED::PowerSource::Group::Reg);
                    const int grpIdx = verifyBoard->AdcGetGroupIndexByEnum(dutIndex, TESys::TED::PowerSource::Group::Reg);
                    float tmpAdc[16];
                    for (int i = 0; i < regChannelCount; i++) {
                        tmpAdc[i] = rowCsv->adcV[grpIdx][i];
                    }
                    for (int i = 0; i < regChannelCount; i++) {

                        const TESys::TED::PowerSource::Reg psId = c_GrpRegCsvFmtOrder[i];
                        int idx = verifyBoard->AdcGetChannelIndexByPsID(dutIndex, (int)psId);
                        rowCsv->adcV[grpIdx][idx] = tmpAdc[i];
                    }
                }

                //Read MipiErr
                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                rowCsv->mipiErr = (unsigned short)strtol(a, &b, 16);
                a = b + 1;

                //Read T2MErr
                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                rowCsv->t2mErr = (unsigned short)strtol(a, &b, 16);
                a = b + 1;

                //Read ESDErr
                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                rowCsv->esdErr = (unsigned short)strtol(a, &b, 16);
                a = b + 1;

                //Read SystemErr
                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                rowCsv->sysErr = strtoll(a, &b, 16);
                a = b + 1;

                //Read PtrnErr, Last Parameter
                a[6] = '\0';
                rowCsv->ptrnAppErr = (unsigned short)strtol(a, &b, 16);
                a = b + 1;


#if 0
                printf("chipID=[0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X] BID(%d, %d) DT(%s) Dur(%d %d %d) ID(%d %d %d %d) [%s] [%s] %s",
                    rowCsv->chipID[0], rowCsv->chipID[1], rowCsv->chipID[2], rowCsv->chipID[3], rowCsv->chipID[4],
                    rowCsv->boardID, rowCsv->dutIdx,
                    Comm::OAL::DateTime::GetKstDateTimeString(rowCsv->utcTime).c_str(),
                    rowCsv->jobDur, rowCsv->tcDur, rowCsv->tcStepDur,
                    rowCsv->jobID, rowCsv->scID, rowCsv->tcID, rowCsv->tcStepID,
                    rowCsv->tcDesc, rowCsv->tcStepDesc,
                    strAdc.c_str()
                );
#endif

                std::shared_ptr<struct CsvRow> rowdb = std::make_shared<struct CsvRow>();
                rowdb->boardID = rowCsv->boardID;
                rowdb->dutIdx = rowCsv->dutIdx;
                rowdb->jobID = rowCsv->jobID;
                rowdb->scID = rowCsv->scID;
                rowdb->tcID = rowCsv->tcID;
                rowdb->tcStepID = rowCsv->tcStepID;

                if (rowdb->scID != 2) {

                    unsigned int hardwareAK = TESys::DB::Single::Hardware::Inst()->GetAK(rowdb->boardID, TESys::Property::Tester::SocPcbID::MV8865_BASE_V2_1, TESys::Property::Tester::DutPcbID::AGING_DUT_QTAB_ANA6707_P_10321);
                    unsigned int tedListAK = TESys::DB::Single::JobList::Inst()->GetTedListAK(rowdb->jobID, hardwareAK, rowdb->dutIdx);
                    unsigned int jobListAK = TESys::DB::Single::JobList::Inst()->GetAK(rowdb->jobID, hardwareAK, rowdb->dutIdx);
                    unsigned int scAK = TESys::DB::Single::Sc::Inst()->GetAK(rowdb->jobID, rowdb->scID);
                    unsigned int scListAK = TESys::DB::Single::ScList::Inst()->GetAK(jobListAK, scAK);
                    unsigned int tcAK = TESys::DB::Single::Tc::Inst()->GetAKWithJob(rowdb->jobID, rowdb->tcID);
                    unsigned int tcListAK = TESys::DB::Single::TcList::Inst()->GetAK(scListAK, tcAK);
                    unsigned int tcStepAK = TESys::DB::Single::TcStep::Inst()->GetAK(tcAK, rowdb->tcStepID);
                    const unsigned int tcStepListAK = TESys::DB::Single::TcStepList::Inst()->GetAK(tcListAK, tcStepAK);

                    assert(tedListAK != UINT_MAX);
                    assert(tcStepListAK != UINT_MAX);

                    //read ChipID
                    std::vector<unsigned char> cidVec = TESys::DB::Single::TedList::Inst()->GetChipIdVec(tedListAK);
                    for (int i = 0; i < 5; i++) {
                        rowdb->chipID[i] = cidVec[i];
                    }

                    //read AdcData
                    for (int ipwr = 0; ipwr < pwrGrpCnt; ipwr++) {

                        std::shared_ptr<TESys::DB::Single::AdcBase> adcBase = TESys::DB::Single::AdcBase::Inst(grpEnum[ipwr], grpIsVolt[ipwr]);
                        const int grpIdx = verifyBoard->AdcGetGroupIndexByEnum(dutIndex, grpEnum[ipwr]);
                        const int channelCount = verifyBoard->AdcGetChannelCount(dutIndex, grpEnum[ipwr]);
                        std::vector<float> adcVec = adcBase->GetAdcValue(tcStepListAK, channelCount);

                        for (int i = 0; i < channelCount; i++) {
                            if (grpIsVolt[ipwr]) {
                                rowdb->adcV[grpIdx][i] = adcVec[i];
                            }
                            else {
                                rowdb->adcA[grpIdx][i] = adcVec[i];
                            }
                        }
                    }

                    //Verify ChipID
                    for (int i = 0; i < 5; i++) {
                        if (rowCsv->chipID[i] == rowdb->chipID[i]) {

                        }
                        else {

                            printf("[Verify FAIL, ChipID]] tcStepListAK=%d BID=%d jobID=%d scID=%d tcID=%d tcStepID=%d  DB(0x%02X 0x%02X 0x%02X 0x%02X 0x%02X) csv(0x%02X 0x%02X 0x%02X 0x%02X 0x%02X) \n",
                                tcStepListAK,
                                rowdb->boardID, rowdb->jobID, rowdb->scID, rowdb->tcID, rowdb->tcStepID,
                                (int)rowdb->chipID[0]&0xFF, (int)rowdb->chipID[1] & 0xFF, (int)rowdb->chipID[2] & 0xFF, (int)rowdb->chipID[3] & 0xFF, (int)rowdb->chipID[4] & 0xFF, 
                                (int)rowCsv->chipID[0] & 0xFF, (int)rowCsv->chipID[1] & 0xFF, (int)rowCsv->chipID[2] & 0xFF, (int)rowCsv->chipID[3] & 0xFF, (int)rowCsv->chipID[4] & 0xFF
                            );


                            printf("Verify FAIL:  ChipID \n");
                            verifyErr++;
                            break;
                        }
                    }
                    assert(verifyErr == 0);
                    if (verifyErr > 0) {
                        break;
                    }

                    //Verify ADC 
                    for (int ipwr = 0; ipwr < pwrGrpCnt; ipwr++) {
                        const int grpIdx = verifyBoard->AdcGetGroupIndexByEnum(dutIndex, grpEnum[ipwr]);
                        const int channelCount = verifyBoard->AdcGetChannelCount(dutIndex, grpEnum[ipwr]);
                        for (int i = 0; i < channelCount; i++) {
                            if (grpIsVolt[ipwr]) {
                                if (rowdb->adcV[grpIdx][i] != rowCsv->adcV[grpIdx][i]) {
                                    printf("Verify FAIL:  ADCD \n");
                                    verifyErr++;
                                    assert(verifyErr == 0);
                                    break;
                                }
                            }
                            else {
                                if (rowdb->adcA[grpIdx][i] != rowCsv->adcA[grpIdx][i]) {
                                    printf("Verify FAIL:  ADCD \n");
                                    verifyErr++;
                                    assert(verifyErr == 0);
                                    break;
                                }
                            }
                        }

                        if (verifyErr > 0) {
                            break;
                        }
                    }
                    assert(verifyErr == 0);
                    if (verifyErr > 0) {
                        break;
                    }

                    //Verify Data/Time and TcStepEndTime
                    rowdb->utcTime = TESys::DB::Single::TcStepList::Inst()->GetEndTime(tcStepListAK);

                    /*
                        30초 범위내에 있으면  Verify OK
                    */
                    if ((rowdb->utcTime < (rowCsv->utcTime + 30))
                        && (rowdb->utcTime > (rowCsv->utcTime - 30))
                        ) {
                        /* nothing to do */
                    }
                    else {

                        printf("FAIL-[rowdb->utcTime] tcStepListAK=%d baordID=%d jobID=%d scID=%d tcID=%d tcStepID=%d  DB(%s) csv(%s) \n", 
                               tcStepListAK, 
                               rowdb->boardID, rowdb->jobID, rowdb->scID, rowdb->tcID, rowdb->tcStepID,
                               Comm::OAL::DateTime::GetKstDateTimeString(rowdb->utcTime).c_str(),
                                Comm::OAL::DateTime::GetKstDateTimeString(rowCsv->utcTime).c_str()
                        );
                        verifyErr++;
                    }
                    assert(verifyErr == 0);
                    if (verifyErr > 0) {
                        break;
                    }

                    //Verfiy JobDur and JobBeginTime/JobEndTime,  
                    //CSV파일에는 누적시간이 기록되므로  비교할 수 없다.
                    //rowdb->jobDur = TESys::DB::Single::JobList::Inst()->GetDurSecond(jobListAK);
                    //assert(rowdb->jobDur == rowCsv->jobDur);

                    //Verfiy tcDur and JobBeginTime/JobEndTime
                    ////CSV파일에는 누적시간이 기록되므로  비교할 수 없다.
                    //rowdb->tcDur = TESys::DB::Single::TcList::Inst()->GetDurSecond(tcListAK);
                    //assert(rowdb->tcDur == rowCsv->tcDur);

                    //Verfiy tcStepDur and JobBeginTime/JobEndTime
                    rowdb->tcStepDur = TESys::DB::Single::TcStepList::Inst()->GetDurSecond(tcStepListAK);
                    int tcStepDiff = rowdb->tcStepDur - rowCsv->tcStepDur;
                    if ( (rowdb->jobID != 15)
                       && (rowdb->jobID != 17)
                        ) {
                        /*
                            Job_0015.csv 에서는 TcStepDur 값이  이상하다. 
                        */
                        assert(abs(tcStepDiff) < 5);
                    }

                    //Verfiy TcDesc
                    strcpy(rowdb->tcDesc, TESys::DB::Single::Tc::Inst()->GetDesc(tcAK).c_str());
                    if (strcmp(rowdb->tcDesc, rowCsv->tcDesc) != 0) {
                        printf("Alert-[tcDesc] tcStepListAK=%d baordID=%d jobID=%d scID=%d tcID=%d tcStepID=%d  rowdb->tcDesc(%s) rowCsv->tcDesc(%s) \n",
                            tcStepListAK,
                            rowdb->boardID, rowdb->jobID, rowdb->scID, rowdb->tcID, rowdb->tcStepID,
                            rowdb->tcDesc,
                            rowCsv->tcDesc);
                    }
                    //assert(strcmp(rowdb->tcDesc,rowCsv->tcDesc)==0);

                    //Verfiy TcStepDesc
                    strcpy(rowdb->tcStepDesc,TESys::DB::Single::TcStep::Inst()->GetDesc(tcStepAK).c_str());

                    if (strcmp(rowdb->tcStepDesc, rowCsv->tcStepDesc) != 0) {
                        printf("AlertL-[tcStepDesc] tcStepListAK=%d baordID=%d jobID=%d scID=%d tcID=%d tcStepID=%d  rowdb->tcStepDesc(%s) rowCsv->tcStepDesc(%s) \n",
                            tcStepListAK,
                            rowdb->boardID, rowdb->jobID, rowdb->scID, rowdb->tcID, rowdb->tcStepID,
                            rowdb->tcStepDesc,
                            rowCsv->tcStepDesc);
                    }
                    //assert(strcmp(rowdb->tcStepDesc, rowCsv->tcStepDesc)==0);

                    //Verify MipiErr
                    rowdb->mipiErr = TESys::DB::Single::AdcErr::Inst()->GetMipiErr(tcStepListAK);
                    assert(rowdb->mipiErr == rowCsv->mipiErr);
                    
                    //Verify T2MErr
                    rowdb->t2mErr = TESys::DB::Single::AdcErr::Inst()->GetT2MErr(tcStepListAK);
                    assert(rowdb->t2mErr == rowCsv->t2mErr);

                    //Verify ESD
                    rowdb->esdErr = TESys::DB::Single::AdcErr::Inst()->GetESDErr(tcStepListAK);
                    assert(rowdb->esdErr == rowCsv->esdErr);
               
                    //Verify PatrnApp
                    rowdb->ptrnAppErr = TESys::DB::Single::AdcErr::Inst()->GetPtrnAppErr(tcStepListAK);
                    assert(rowdb->ptrnAppErr == rowCsv->ptrnAppErr);

                    //Verify System
                    rowdb->sysErr = TESys::DB::Single::AdcErr::Inst()->GetSysErr(tcStepListAK);
                    assert(rowdb->sysErr == rowCsv->sysErr);

                } //if (rowdb->scID != 2) {


                long long filePos = STDC_FTELL64(fp);
                curTick = Comm::OAL::System::GetTickCount64();

                if ((curTick - beforeTick) > 1000LL) {

                    double durSec = (double)(curTick - startTick) / 1000.0f;
                    double fprog = (double)(filePos * 100LL) / (double)csvFileByteSize;

                    // durSec : fprop = expectedSec : 100.0f
                    // expectedSec = durSec*100.0f / fprog
                    double expectedSec = (double)(durSec * 100LL) / fprog;

                    printf("[JOB_%04d] %3.2f. %lld/%lld %2.2f%c (Expected: %3.2f,  Remain: %3.2f sec) \n",
                        jobID, 
                        durSec,
                        filePos, csvFileByteSize, fprog, '%',
                        expectedSec,
                        expectedSec - durSec
                    );

                    beforeTick = curTick;
                }
            }

            fclose(fp);
            delete[] buf;

            if (verifyErr == 0) {
                isVerifyOk = true;
            }

            return isVerifyOk;
        }



        static bool VerifyCsvWithDB_Job21(int jobID) {

            bool isVerifyOk = false;
            int verifyErr = 0;

            const int pwrGrpCnt = 5;
            const TESys::TED::PowerSource::Group grpEnum[pwrGrpCnt] = {
                TESys::TED::PowerSource::Group::External,
                TESys::TED::PowerSource::Group::External,
                TESys::TED::PowerSource::Group::Ldo,
                TESys::TED::PowerSource::Group::Reg,
                TESys::TED::PowerSource::Group::Sout
            };
            const bool grpIsVolt[pwrGrpCnt] = { true, false, true, true, true };

            const TESys::TED::PowerSource::Reg c_GrpRegCsvFmtOrder[] = {
                TESys::TED::PowerSource::Reg::VLOUT3_2,
                TESys::TED::PowerSource::Reg::VCI1,
                TESys::TED::PowerSource::Reg::VCIR,
                TESys::TED::PowerSource::Reg::VREG1,
                TESys::TED::PowerSource::Reg::VREG1OUT,
                TESys::TED::PowerSource::Reg::VREF1,
                TESys::TED::PowerSource::Reg::VBOT,
                TESys::TED::PowerSource::Reg::VGH,
                TESys::TED::PowerSource::Reg::VGL,
                TESys::TED::PowerSource::Reg::VINT,
                TESys::TED::PowerSource::Reg::VGHH,
                TESys::TED::PowerSource::Reg::VGLL,
                TESys::TED::PowerSource::Reg::VEH,
                TESys::TED::PowerSource::Reg::VAINT,
                TESys::TED::PowerSource::Reg::BML,
            };

            long long startTick = Comm::OAL::System::GetTickCount64();
            long long beforeTick = startTick;
            long long curTick;

            const int dutIndex = 0;
            std::shared_ptr<TESys::TED::VerifyBoard> verifyBoard = TESys::TED::VerifyBoard::Inst();
            std::shared_ptr<struct CsvRow> rowCsv = std::make_shared<struct CsvRow>();

            std::string strFilePathName = CSV_PATH;
            strFilePathName += Comm::Property::Path::GetFilePathDelimChar();
            strFilePathName += Comm::Utils::StringFormat("JOB_%04d.csv", jobID);

            const int bufMaxByteSize = 1024 * 16;
            char* buf = new char[bufMaxByteSize];
            assert(buf);

            FILE* fp;

            fp = fopen(strFilePathName.c_str(), "r");
            assert(fp);
            STDC_FSEEK64(fp, 0, SEEK_END);
            long long csvFileByteSize = STDC_FTELL64(fp);
            fclose(fp);


            fp = fopen(strFilePathName.c_str(), "r");
            assert(fp);

            //Header 읽기 
            fgets(buf, bufMaxByteSize, fp);

            //데이타 읽기
            while (true) {


                char* a, * b;
                char* p = fgets(buf, bufMaxByteSize, fp);
                if (p == NULL) {
                    break;
                }
                a = buf;
                                
                //BoardID
                b = strchr(a, ',');
                assert(b);
                rowCsv->boardID = strtol(a, &b, 10);
                a = b + 1;

                //DutIdx
                b = strchr(a, ',');
                assert(b);
                rowCsv->dutIdx = strtol(a, &b, 10);
                a = b + 1;

                //날짜, 시간 
                std::string dateTime;
                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                dateTime = a;
                dateTime += ' ';
                a = b + 1;

                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                dateTime += a;
                a = b + 1;
                rowCsv->utcTime = Comm::OAL::DateTime::GetUtcTime_KST_SqlFmtDateTime(dateTime);

                //JobDur
                b = strchr(a, ',');
                assert(b);
                rowCsv->jobDur = strtol(a, &b, 10);
                a = b + 1;

                //TcDur
                b = strchr(a, ',');
                assert(b);
                rowCsv->tcDur = strtol(a, &b, 10);
                a = b + 1;

                //TcStepDur
                b = strchr(a, ',');
                assert(b);
                rowCsv->tcStepDur = strtol(a, &b, 10);
                a = b + 1;

                //JobID
                b = strchr(a, ',');
                assert(b);
                rowCsv->jobID = strtol(a, &b, 10);
                a = b + 1;

                //ScID
                b = strchr(a, ',');
                assert(b);
                rowCsv->scID = strtol(a, &b, 10);
                a = b + 1;

                //TcID
                b = strchr(a, ',');
                assert(b);
                rowCsv->tcID = strtol(a, &b, 10);
                a = b + 1;

                //TcStepID
                b = strchr(a, ',');
                assert(b);
                rowCsv->tcStepID = strtol(a, &b, 10);
                a = b + 1;

                //TcDesc
                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                strcpy(rowCsv->tcDesc, a);
                a = b + 1;

                //TcStepDesc
                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                strcpy(rowCsv->tcStepDesc, a);
                a = b + 1;


                char szTmp[128];
                std::string strAdc;

                //ExtV
                for (int ipwr = 0; ipwr < pwrGrpCnt; ipwr++) {
                    int grpIdx, chCnt;
                    grpIdx = verifyBoard->AdcGetGroupIndexByEnum(dutIndex, grpEnum[ipwr]);
                    chCnt = verifyBoard->AdcGetChannelCount(dutIndex, grpEnum[ipwr]);

                    strAdc += "[";
                    for (int i = 0; i < chCnt; i++) {
                        b = strchr(a, ',');
                        assert(b);
                        *b = '\0';
                        float fadc = (float)atof(a);
                        if (grpIsVolt[ipwr]) {
                            rowCsv->adcV[grpIdx][i] = fadc;
                        }
                        else {
                            rowCsv->adcA[grpIdx][i] = fadc;
                        }
                        a = b + 1;

                        sprintf(szTmp, "%3.4f ", fadc);
                        strAdc += szTmp;
                    }
                    strAdc += "] ";
                }

                //RegV Rearrange
                {
                    const int regChannelCount = verifyBoard->AdcGetChannelCount(dutIndex, TESys::TED::PowerSource::Group::Reg);
                    const int grpIdx = verifyBoard->AdcGetGroupIndexByEnum(dutIndex, TESys::TED::PowerSource::Group::Reg);
                    float tmpAdc[16];
                    for (int i = 0; i < regChannelCount; i++) {
                        tmpAdc[i] = rowCsv->adcV[grpIdx][i];
                    }
                    for (int i = 0; i < regChannelCount; i++) {

                        const TESys::TED::PowerSource::Reg psId = c_GrpRegCsvFmtOrder[i];
                        int idx = verifyBoard->AdcGetChannelIndexByPsID(dutIndex, (int)psId);
                        rowCsv->adcV[grpIdx][idx] = tmpAdc[i];
                    }
                }

                //Read MipiErr
                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                rowCsv->mipiErr = (unsigned short)strtol(a, &b, 16);
                a = b + 1;

                //Read T2MErr
                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                rowCsv->t2mErr = (unsigned short)strtol(a, &b, 16);
                a = b + 1;

                //Read ESDErr
                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                rowCsv->esdErr = (unsigned short)strtol(a, &b, 16);
                a = b + 1;

                //Read SystemErr
                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                rowCsv->sysErr = strtoll(a, &b, 16);
                a = b + 1;

                //Read PtrnErr, Last Parameter
                b = strchr(a, ',');
                assert(b);
                *b = '\0';
                rowCsv->ptrnAppErr = (unsigned short)strtol(a, &b, 16);
                a = b + 1;

                //ChipID
                for (int i = 0; i < 5; i++) {
                    b = strchr(a, ',');
                    assert(b);
                    rowCsv->chipID[i] = strtol(a, &b, 16);
                    a = b + 1;
                }

                //OtpRev
                for (int i = 0; i < 5; i++) {
                    b = strchr(a, ',');
                    assert(b);
                    rowCsv->otpREV[i] = strtol(a, &b, 16);
                    a = b + 1;
                }
                a[4] = '\0';
                rowCsv->otpREV[5] = strtol(a, NULL, 16);

#if 0
                printf("chipID=[0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X] BID(%d, %d) DT(%s) Dur(%d %d %d) ID(%d %d %d %d) [%s] [%s] %s",
                    rowCsv->chipID[0], rowCsv->chipID[1], rowCsv->chipID[2], rowCsv->chipID[3], rowCsv->chipID[4],
                    rowCsv->boardID, rowCsv->dutIdx,
                    Comm::OAL::DateTime::GetKstDateTimeString(rowCsv->utcTime).c_str(),
                    rowCsv->jobDur, rowCsv->tcDur, rowCsv->tcStepDur,
                    rowCsv->jobID, rowCsv->scID, rowCsv->tcID, rowCsv->tcStepID,
                    rowCsv->tcDesc, rowCsv->tcStepDesc,
                    strAdc.c_str()
                );
#endif

                std::shared_ptr<struct CsvRow> rowdb = std::make_shared<struct CsvRow>();
                rowdb->boardID = rowCsv->boardID;
                rowdb->dutIdx = rowCsv->dutIdx;
                rowdb->jobID = rowCsv->jobID;
                rowdb->scID = rowCsv->scID;
                rowdb->tcID = rowCsv->tcID;
                rowdb->tcStepID = rowCsv->tcStepID;

                if (rowdb->scID != 2) {

                    unsigned int hardwareAK = TESys::DB::Single::Hardware::Inst()->GetAK(rowdb->boardID, TESys::Property::Tester::SocPcbID::MV8865_BASE_V2_1, TESys::Property::Tester::DutPcbID::AGING_DUT_QTAB_ANA6707_P_10321);
                    unsigned int tedListAK = TESys::DB::Single::JobList::Inst()->GetTedListAK(rowdb->jobID, hardwareAK, rowdb->dutIdx);
                    unsigned int jobListAK = TESys::DB::Single::JobList::Inst()->GetAK(rowdb->jobID, hardwareAK, rowdb->dutIdx);
                    unsigned int scAK = TESys::DB::Single::Sc::Inst()->GetAK(rowdb->jobID, rowdb->scID);
                    unsigned int scListAK = TESys::DB::Single::ScList::Inst()->GetAK(jobListAK, scAK);
                    unsigned int tcAK = TESys::DB::Single::Tc::Inst()->GetAKWithJob(rowdb->jobID, rowdb->tcID);
                    unsigned int tcListAK = TESys::DB::Single::TcList::Inst()->GetAK(scListAK, tcAK);
                    unsigned int tcStepAK = TESys::DB::Single::TcStep::Inst()->GetAK(tcAK, rowdb->tcStepID);
                    const unsigned int tcStepListAK = TESys::DB::Single::TcStepList::Inst()->GetAK(tcListAK, tcStepAK);

                    assert(tedListAK != UINT_MAX);
                    assert(tcStepListAK != UINT_MAX);

                    //read ChipID
                    std::vector<unsigned char> cidVec = TESys::DB::Single::TedList::Inst()->GetChipIdVec(tedListAK);
                    for (int i = 0; i < 5; i++) {
                        rowdb->chipID[i] = cidVec[i];
                    }

                    //read OptRev
                    std::vector<unsigned char> optRevVec = TESys::DB::Single::TedList::Inst()->GetOtpRevVec(tedListAK);
                    for (int i = 0; i < 6; i++) {
                        rowdb->otpREV[i] = optRevVec[i];
                    }

                    //read AdcData
                    for (int ipwr = 0; ipwr < pwrGrpCnt; ipwr++) {

                        std::shared_ptr<TESys::DB::Single::AdcBase> adcBase = TESys::DB::Single::AdcBase::Inst(grpEnum[ipwr], grpIsVolt[ipwr]);
                        const int grpIdx = verifyBoard->AdcGetGroupIndexByEnum(dutIndex, grpEnum[ipwr]);
                        const int channelCount = verifyBoard->AdcGetChannelCount(dutIndex, grpEnum[ipwr]);
                        std::vector<float> adcVec = adcBase->GetAdcValue(tcStepListAK, channelCount);

                        for (int i = 0; i < channelCount; i++) {
                            if (grpIsVolt[ipwr]) {
                                rowdb->adcV[grpIdx][i] = adcVec[i];
                            }
                            else {
                                rowdb->adcA[grpIdx][i] = adcVec[i];
                            }
                        }
                    }

                    //Verify ChipID
                    for (int i = 0; i < 5; i++) {
                        if (rowCsv->chipID[i] == rowdb->chipID[i]) {

                        }
                        else {
                            printf("[Verify FAIL, ChipID]] tcStepListAK=%d BID=%d jobID=%d scID=%d tcID=%d tcStepID=%d  DB(0x%02X 0x%02X 0x%02X 0x%02X 0x%02X) csv(0x%02X 0x%02X 0x%02X 0x%02X 0x%02X) \n",
                                tcStepListAK,
                                rowdb->boardID, rowdb->jobID, rowdb->scID, rowdb->tcID, rowdb->tcStepID,
                                (int)rowdb->chipID[0] & 0xFF, (int)rowdb->chipID[1] & 0xFF, (int)rowdb->chipID[2] & 0xFF, (int)rowdb->chipID[3] & 0xFF, (int)rowdb->chipID[4] & 0xFF,
                                (int)rowCsv->chipID[0] & 0xFF, (int)rowCsv->chipID[1] & 0xFF, (int)rowCsv->chipID[2] & 0xFF, (int)rowCsv->chipID[3] & 0xFF, (int)rowCsv->chipID[4] & 0xFF
                            );

                            verifyErr++;
                            break;
                        }
                    }
                    assert(verifyErr == 0);
                    if (verifyErr > 0) {
                        break;
                    }

                    //Verify OtpRev
                    for (int i = 0; i < 6; i++) {
                        if (rowCsv->otpREV[i] == rowdb->otpREV[i]) {

                        }
                        else {
                            printf("Verify FAIL:  otpREV \n");
                            verifyErr++;
                            break;
                        }
                    }
                    assert(verifyErr == 0);
                    if (verifyErr > 0) {
                        break;
                    }


                    //Verify ADC 
                    for (int ipwr = 0; ipwr < pwrGrpCnt; ipwr++) {
                        const int grpIdx = verifyBoard->AdcGetGroupIndexByEnum(dutIndex, grpEnum[ipwr]);
                        const int channelCount = verifyBoard->AdcGetChannelCount(dutIndex, grpEnum[ipwr]);
                        for (int i = 0; i < channelCount; i++) {
                            if (grpIsVolt[ipwr]) {
                                if (rowdb->adcV[grpIdx][i] != rowCsv->adcV[grpIdx][i]) {
                                    printf("Verify FAIL:  ADCD \n");
                                    verifyErr++;
                                    assert(verifyErr == 0);
                                    break;
                                }
                            }
                            else {
                                if (rowdb->adcA[grpIdx][i] != rowCsv->adcA[grpIdx][i]) {
                                    printf("Verify FAIL:  ADCD \n");
                                    verifyErr++;
                                    assert(verifyErr == 0);
                                    break;
                                }
                            }
                        }

                        if (verifyErr > 0) {
                            break;
                        }
                    }
                    assert(verifyErr == 0);
                    if (verifyErr > 0) {
                        break;
                    }

                    //Verify Data/Time and TcStepEndTime
                    rowdb->utcTime = TESys::DB::Single::TcStepList::Inst()->GetEndTime(tcStepListAK);

                    /*
                        30초 범위내에 있으면  Verify OK
                    */
                    if ((rowdb->utcTime < (rowCsv->utcTime + 30))
                        && (rowdb->utcTime > (rowCsv->utcTime - 30))
                        ) {
                        /* nothing to do */
                    }
                    else if (
                        (rowdb->boardID == 36 && rowdb->jobID == 24)
                        || (rowdb->boardID == 43 && rowdb->jobID == 24)
                        ) {
                        /*
                            nothing to do 
                            board36 번 정지되어 다시 시작했었슴 DB에서는 Verify된것으로 하고, 향후 DB구축시 유의해야함..
                        */
                    }
                    else {


                        printf("FAIL-[rowdb->utcTime] tcStepListAK=%d baordID=%d jobID=%d scID=%d tcID=%d tcStepID=%d  DB(%s) csv(%s) \n",
                            tcStepListAK,
                            rowdb->boardID, rowdb->jobID, rowdb->scID, rowdb->tcID, rowdb->tcStepID,
                            Comm::OAL::DateTime::GetKstDateTimeString(rowdb->utcTime).c_str(),
                            Comm::OAL::DateTime::GetKstDateTimeString(rowCsv->utcTime).c_str()
                        );
                        verifyErr++;
                    }
                    assert(verifyErr == 0);
                    if (verifyErr > 0) {
                        break;
                    }

                    //Verfiy JobDur and JobBeginTime/JobEndTime,  
                    //CSV파일에는 누적시간이 기록되므로  비교할 수 없다.
                    //rowdb->jobDur = TESys::DB::Single::JobList::Inst()->GetDurSecond(jobListAK);
                    //assert(rowdb->jobDur == rowCsv->jobDur);

                    //Verfiy tcDur and JobBeginTime/JobEndTime
                    ////CSV파일에는 누적시간이 기록되므로  비교할 수 없다.
                    //rowdb->tcDur = TESys::DB::Single::TcList::Inst()->GetDurSecond(tcListAK);
                    //assert(rowdb->tcDur == rowCsv->tcDur);

                    //Verfiy tcStepDur and JobBeginTime/JobEndTime
                    rowdb->tcStepDur = TESys::DB::Single::TcStepList::Inst()->GetDurSecond(tcStepListAK);
                    int tcStepDiff = rowdb->tcStepDur - rowCsv->tcStepDur;
                    if ((rowdb->jobID != 15)
                        && (rowdb->jobID != 17)
                        && (rowdb->jobID != 24)
                        ) {
                        /*
                            Job_0015.csv 에서는 TcStepDur 값이  이상하다.
                        */
                        assert(abs(tcStepDiff) < 5);
                    }

                    //Verfiy TcDesc
                    strcpy(rowdb->tcDesc, TESys::DB::Single::Tc::Inst()->GetDesc(tcAK).c_str());
                    if (strcmp(rowdb->tcDesc, rowCsv->tcDesc) != 0) {
                        printf("Alert-[tcDesc] tcStepListAK=%d baordID=%d jobID=%d scID=%d tcID=%d tcStepID=%d  rowdb->tcDesc(%s) rowCsv->tcDesc(%s) \n",
                            tcStepListAK,
                            rowdb->boardID, rowdb->jobID, rowdb->scID, rowdb->tcID, rowdb->tcStepID,
                            rowdb->tcDesc,
                            rowCsv->tcDesc);
                    }
                    //assert(strcmp(rowdb->tcDesc,rowCsv->tcDesc)==0);

                    //Verfiy TcStepDesc
                    strcpy(rowdb->tcStepDesc, TESys::DB::Single::TcStep::Inst()->GetDesc(tcStepAK).c_str());

                    if (strcmp(rowdb->tcStepDesc, rowCsv->tcStepDesc) != 0) {
                        printf("AlertL-[tcStepDesc] tcStepListAK=%d baordID=%d jobID=%d scID=%d tcID=%d tcStepID=%d  rowdb->tcStepDesc(%s) rowCsv->tcStepDesc(%s) \n",
                            tcStepListAK,
                            rowdb->boardID, rowdb->jobID, rowdb->scID, rowdb->tcID, rowdb->tcStepID,
                            rowdb->tcStepDesc,
                            rowCsv->tcStepDesc);
                    }
                    //assert(strcmp(rowdb->tcStepDesc, rowCsv->tcStepDesc)==0);

                    //Verify MipiErr
                    rowdb->mipiErr = TESys::DB::Single::AdcErr::Inst()->GetMipiErr(tcStepListAK);
                    assert(rowdb->mipiErr == rowCsv->mipiErr);

                    //Verify T2MErr
                    rowdb->t2mErr = TESys::DB::Single::AdcErr::Inst()->GetT2MErr(tcStepListAK);
                    assert(rowdb->t2mErr == rowCsv->t2mErr);

                    //Verify ESD
                    rowdb->esdErr = TESys::DB::Single::AdcErr::Inst()->GetESDErr(tcStepListAK);
                    assert(rowdb->esdErr == rowCsv->esdErr);

                    //Verify PatrnApp
                    rowdb->ptrnAppErr = TESys::DB::Single::AdcErr::Inst()->GetPtrnAppErr(tcStepListAK);
                    assert(rowdb->ptrnAppErr == rowCsv->ptrnAppErr);

                    //Verify System
                    rowdb->sysErr = TESys::DB::Single::AdcErr::Inst()->GetSysErr(tcStepListAK);
                    assert(rowdb->sysErr == rowCsv->sysErr);

                } //if (rowdb->scID != 2) {


                long long filePos = STDC_FTELL64(fp);
                curTick = Comm::OAL::System::GetTickCount64();

                if ((curTick - beforeTick) > 1000LL) {

                    double durSec = (double)(curTick - startTick) / 1000.0f;
                    double fprog = (double)(filePos * 100LL) / (double)csvFileByteSize;

                    // durSec : fprop = expectedSec : 100.0f
                    // expectedSec = durSec*100.0f / fprog
                    double expectedSec = (double)(durSec * 100LL) / fprog;

                    printf("[JOB_%04d] %3.2f. %lld/%lld %2.2f%c (Expected: %3.2f,  Remain: %3.2f sec) \n",
                        jobID, 
                        durSec,
                        filePos, csvFileByteSize, fprog, '%',
                        expectedSec,
                        expectedSec - durSec
                    );

                    beforeTick = curTick;
                }
            }

            fclose(fp);
            delete[] buf;

            if (verifyErr == 0) {
                isVerifyOk = true;
            }

            return isVerifyOk;
        }


        bool Verify::CSV(int argc, const char** argv) {
                
            int jobID = -1;
                
            static const char* const usages[] = {
                "verify csv [options] [[--] args]",
                "verify csv [options]",
                NULL,
            };

            struct argparse_option options[] = {
                OPT_HELP(),
                OPT_INTEGER('j', "jobid", &jobID, "select verify job", NULL, 0, 0),
                OPT_END(),
            };

            struct argparse argparse;
            argparse_init(&argparse, options, usages, 0);
            argparse_describe(&argparse, "\ninsert rawdata to databse", "\nAdditional description of the program after the description of the arguments.");
            argc = argparse_parse(&argparse, argc, argv);

            if (jobID != -1) {
                
                bool isVerify;
                
                printf("jobID: %d\n", jobID);

                if (jobID == 9829) {

                    /*
                    JOB18 FAIL 
                           TESysDBMySQL: /home/hthwang/develop/TED/test-system-app/TESys/DB/Table/AdcBase_TESys_DB_Table.cpp:192: virtual std::vector<float> TESys::DB::Single::AdcBase::GetAdcValue(unsigned int, int): Assertion `bRet' failed.
                    */

                    for (int j = 19; j <= 26; j++) {
                    
                        if (j < 21) {
                            isVerify = VerifyCsvWithDB_Job13(j);
                        }
                        else {
                            isVerify = VerifyCsvWithDB_Job21(j);
                        }

                        if (isVerify) {
                            printf("JOB_%04d.csv verify OK\n", j);
                        }
                        else {
                            printf("JOB_%04d.csv verify FAIL\n", j);
                        }
                    }
                }
                else {

                    if (jobID < 21) {
                        isVerify = VerifyCsvWithDB_Job13(jobID);
                    }
                    else {
                        isVerify = VerifyCsvWithDB_Job21(jobID);
                    }

                    if (isVerify) {
                        printf("JOB_%04d.csv verify OK\n", jobID);
                    }
                    else {
                        printf("JOB_%04d.csv verify FAIL\n", jobID);
                    }
                }
            }
            else {
                    
            }
                
            //select * from 
                
            return true;
        }

        
    };//namespace Cmd
};//namespace AppDatabaseMySQL

