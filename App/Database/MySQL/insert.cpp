#include "AppDefine.hpp"

namespace TESysDB {

    /*
        태초에   TED와  장착할 수 있는 보드가 있었다.

        Base Table  :   Ted    Board  JOb

    */

    static void CmdProc_PyStart(std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack) {

        assert(rcvPack->GetCommand() == TESys::Net::Command::Aging::PyStart);

    }

    static void CmdProc_JobBegin(std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack, int reqJobID = -1, int reqScID = -1, int reqTcID = -1) {

        assert(rcvPack->GetCommand() == TESys::Net::Command::Aging::JobBegin);

        bool isRun = false;

        if ((reqJobID == -1)
            || (rcvPack->GetJobID() == reqJobID)) {
            isRun = true;
        }

        if (isRun) {
            //Insert Job
            TESys::DB::Single::Job::Inst()->Insert(rcvPack);

            //Insert TedList
            TESys::DB::Single::TedList::Inst()->Insert(rcvPack);

            //Insert JobList
            TESys::DB::Single::JobList::Inst()->Insert(rcvPack);
        }
    }

    static void CmdProc_JobEnd(std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack, int reqJobID = -1, int reqScID = -1, int reqTcID = -1) {

        assert(rcvPack->GetCommand() == TESys::Net::Command::Aging::JobEnd);

        bool isRun = false;

        if ((reqJobID == -1)
            || (rcvPack->GetJobID() == reqJobID)) {
            isRun = true;
        }

        if (isRun) {
            time_t endTime = rcvPack->GetUtcTime();
            unsigned int jobListAK = TESys::DB::Single::JobList::Inst()->GetAK(rcvPack);
            TESys::DB::Single::JobList::Inst()->UpdateEndTime(jobListAK, endTime);
        }
    }

    static void CmdProc_ScBegin(std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack, int reqJobID = -1, int reqScID = -1, int reqTcID = -1) {

        assert(rcvPack->GetCommand() == TESys::Net::Command::Aging::ScBegin);

        bool isRun = false;

        if ((reqJobID == -1)
            || (rcvPack->GetJobID() == reqJobID)) {

            if ((reqScID == -1)
                || (rcvPack->GetScID() == reqScID)) {

                isRun = true;
            }
        }

        if (isRun) {
            //Insert Sc
            TESys::DB::Single::Sc::Inst()->Insert(rcvPack);

            //Insert ScList
            TESys::DB::Single::ScList::Inst()->Insert(rcvPack);
        }
    }

    static void CmdProc_ScEnd(std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack, int reqJobID = -1, int reqScID = -1, int reqTcID = -1) {

        assert(rcvPack->GetCommand() == TESys::Net::Command::Aging::ScEnd);

        bool isRun = false;

        if ((reqJobID == -1)
            || (rcvPack->GetJobID() == reqJobID)) {

            if ((reqScID == -1)
                || (rcvPack->GetScID() == reqScID)) {

                isRun = true;
            }
        }

        if (isRun) {
            time_t endTime = rcvPack->GetUtcTime();
            unsigned int scListAK = TESys::DB::Single::ScList::Inst()->GetAK(rcvPack);
            TESys::DB::Single::JobList::Inst()->UpdateEndTime(scListAK, endTime);
        }
    }

    static void CmdProc_TcBegin(std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack, int reqJobID = -1, int reqScID = -1, int reqTcID = -1) {

        assert(rcvPack->GetCommand() == TESys::Net::Command::Aging::TcBegin);

        bool isRun = false;

        if ((reqJobID == -1)
            || (rcvPack->GetJobID() == reqJobID)) {

            if ((reqScID == -1)
                || (rcvPack->GetScID() == reqScID)) {

                if ((reqTcID == -1)
                    || (rcvPack->GetTcID() == reqTcID)) {

                    isRun = true;
                }
            }
        }

        if(isRun) {
            //Insert TC
            TESys::DB::Single::Tc::Inst()->Insert(rcvPack);

            //Inser TcList
            TESys::DB::Single::TcList::Inst()->Insert(rcvPack);
        }
    }

    static void CmdProc_TcEnd(std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack, int reqJobID = -1, int reqScID = -1, int reqTcID = -1) {

        assert(rcvPack->GetCommand() == TESys::Net::Command::Aging::TcEnd);

        bool isRun = false;

        if ((reqJobID == -1)
            || (rcvPack->GetJobID() == reqJobID)) {

            if ((reqScID == -1)
                || (rcvPack->GetScID() == reqScID)) {

                if ((reqTcID == -1)
                    || (rcvPack->GetTcID() == reqTcID)) {

                    isRun = true;
                }
            }
        }
        
        if (isRun) {

            time_t endTime = rcvPack->GetUtcTime();
            unsigned int tcListAK = TESys::DB::Single::TcList::Inst()->GetAK(rcvPack);
            TESys::DB::Single::TcList::Inst()->UpdateEndTime(tcListAK, endTime);
        }
    }

    static void CmdProc_TcStepBegin(std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack, int reqJobID = -1, int reqScID = -1, int reqTcID = -1) {

        assert(rcvPack->GetCommand() == TESys::Net::Command::Aging::TcStepBegin);

        bool isRun = false;

        if ((reqJobID == -1)
            || (rcvPack->GetJobID() == reqJobID)) {

            if ((reqScID == -1)
                || (rcvPack->GetScID() == reqScID)) {

                if ((reqTcID == -1)
                    || (rcvPack->GetTcID() == reqTcID)) {

                    isRun = true;
                }
            }
        }

        if (isRun) {

            //Insert TC
            TESys::DB::Single::TcStep::Inst()->Insert(rcvPack);

            //Insert TCStepList
            TESys::DB::Single::TcStepList::Inst()->Insert(rcvPack);
        }

    }

    static void CmdProc_TcStepEnd(std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack, int reqJobID = -1, int reqScID = -1, int reqTcID = -1) {

        assert(rcvPack->GetCommand() == TESys::Net::Command::Aging::TcStepEnd);

        bool isRun = false;

        if ((reqJobID == -1)
            || (rcvPack->GetJobID() == reqJobID)) {

            if ((reqScID == -1)
                || (rcvPack->GetScID() == reqScID)) {

                if ((reqTcID == -1)
                    || (rcvPack->GetTcID() == reqTcID)) {

                    isRun = true;
                }
            }
        }

        if (isRun) {

            time_t endTime = rcvPack->GetUtcTime();
            unsigned int tcStepListAK = TESys::DB::Single::TcStepList::Inst()->GetAK(rcvPack);
            TESys::DB::Single::TcStepList::Inst()->UpdateEndTime(tcStepListAK, endTime);

        }
    }


    static void CmdProc_MeasureAdc(std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack, int reqJobID = -1, int reqScID = -1, int reqTcID = -1) {

        assert(rcvPack->GetCommand() == TESys::Net::Command::Aging::MeasureAdc);

        bool isRun = false;

        if ((reqJobID == -1)
            || (rcvPack->GetJobID() == reqJobID)) {

            if ((reqScID == -1)
                || (rcvPack->GetScID() == reqScID)) {

                if ((reqTcID == -1)
                    || (rcvPack->GetTcID() == reqTcID)) {

                    isRun = true;
                }
            }
        }

        
        if (isRun) {

            unsigned int tcStepListAK = TESys::DB::Single::TcStepList::Inst()->GetAK(rcvPack);
            assert(tcStepListAK != UINT_MAX);

            TESys::DB::Single::AdcExtV::Inst()->Insert(tcStepListAK, rcvPack);
            TESys::DB::Single::AdcExtA::Inst()->Insert(tcStepListAK, rcvPack);
            TESys::DB::Single::AdcLdoV::Inst()->Insert(tcStepListAK, rcvPack);
            TESys::DB::Single::AdcRegV::Inst()->Insert(tcStepListAK, rcvPack);
            TESys::DB::Single::AdcSoutV::Inst()->Insert(tcStepListAK, rcvPack);
            TESys::DB::Single::AdcErr::Inst()->Insert(tcStepListAK, rcvPack);
        }
    }

    void Insert(std::vector<std::string> rawDBFileNameVector, int reqJobID, int reqScID, int reqTcID) {

        long long totalRawDataByteSize = 0;
        long long totalReadByteSize = 0;
        long long startTick = Comm::OAL::System::GetTickCount64();
        long long beforeTick = startTick;
        long long curTick = startTick;

        unsigned char* recordBuf = new unsigned char[TESys::Data::DataAcqDBRaw::GetRecrodBufFixedByteSize()];
        assert(recordBuf);

        //Cal Total FileSize 
        for (std::vector<std::string>::const_iterator it = rawDBFileNameVector.cbegin();
            it != rawDBFileNameVector.cend();
            it++) {

            long long fileByteSize;
            std::string strRawDBPathFileName = (*it);
            FILE* fp = fopen(strRawDBPathFileName.c_str(), "rb");
            assert(fp);
            STDC_FSEEK64(fp, 0, SEEK_END);
            fileByteSize = STDC_FTELL64(fp);
            fclose(fp);

            totalRawDataByteSize += fileByteSize;
        }


        for (std::vector<std::string>::const_iterator it = rawDBFileNameVector.cbegin();
            it != rawDBFileNameVector.cend();
            it++) {

            long long fileByteSize;
            long long beforeFilePos;
            std::string strRawDBPathFileName = (*it);
            std::string strRawDBFileName = Comm::Utils::StringTool::SplitFileName(strRawDBPathFileName);

            PRINTF("File: %s \n", strRawDBPathFileName.c_str());

            FILE* fp = fopen(strRawDBPathFileName.c_str(), "rb");
            assert(fp);

            STDC_FSEEK64(fp, 0, SEEK_END);
            fileByteSize = STDC_FTELL64(fp);
            beforeFilePos = STDC_FSEEK64(fp, 0, SEEK_SET);

            while (true) {

                long long filePos0 = STDC_FTELL64(fp);

                //CLOGD("");
                if (TESys::Data::DataAcqDBRaw::ReadRecord(fp, recordBuf) == true) {

                    std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack = TESys::Data::DataAcqDBRaw::ConvertRawRecordDataToPacketDataAcq(recordBuf);

                    TESys::Net::Command::Aging cmd = rcvPack->GetCommand();
                    switch (cmd) {

                    case TESys::Net::Command::Aging::PyStart:
                        //CmdProc_PyStart(rcvPack);
                        break;

                    case TESys::Net::Command::Aging::PyStop:
                        //this->LoadPacket(jobID, rcvPack);
                        break;

                    case TESys::Net::Command::Aging::JobBegin:
                        //CLOGD("");
                        CmdProc_JobBegin(rcvPack, reqJobID, reqScID, reqTcID);
                        break;

                    case TESys::Net::Command::Aging::JobEnd:
                        //CLOGD("");
                        CmdProc_JobEnd(rcvPack, reqJobID, reqScID, reqTcID);
                        break;

                    case TESys::Net::Command::Aging::ScBegin:
                        if (rcvPack->GetScID() != 2) {
                            CmdProc_ScBegin(rcvPack, reqJobID, reqScID, reqTcID);
                        }
                        break;

                    case TESys::Net::Command::Aging::ScEnd:
                        if (rcvPack->GetScID() != 2) {
                            CmdProc_ScEnd(rcvPack, reqJobID, reqScID, reqTcID);
                        }
                        break;

                    case TESys::Net::Command::Aging::TcBegin:
                        if (rcvPack->GetScID() != 2) {
                            CmdProc_TcBegin(rcvPack, reqJobID, reqScID, reqTcID);
                        }
                        break;

                    case TESys::Net::Command::Aging::TcEnd:
                        if (rcvPack->GetScID() != 2) {
                            CmdProc_TcEnd(rcvPack, reqJobID, reqScID, reqTcID);
                        }
                        break;

                    case TESys::Net::Command::Aging::TcStepBegin:
                        if (rcvPack->GetScID() != 2) {
                            CmdProc_TcStepBegin(rcvPack, reqJobID, reqScID, reqTcID);
                        }
                        break;

                    case TESys::Net::Command::Aging::TcStepEnd:
                        if (rcvPack->GetScID() != 2) {
                            CmdProc_TcStepEnd(rcvPack, reqJobID, reqScID, reqTcID);
                        }
                        break;

                    case TESys::Net::Command::Aging::MeasureAdc:
                        if (rcvPack->GetScID() != 2) {
                            CmdProc_MeasureAdc(rcvPack, reqJobID, reqScID, reqTcID);
                        }
                        break;

                    default:
                        //if ((jobID == rcvPack->GetJobID())
                            //  && (scID == rcvPack->GetScID())
                            //)
                        //{
                            //this->LoadPacket(jobID, rcvPack);
                        //}
                        break;
                    }

                    long long filePos = STDC_FTELL64(fp);
                    curTick = Comm::OAL::System::GetTickCount64();

                    totalReadByteSize += (filePos - filePos0);

                    //printf("%lld ", curTick - beforeTick);

                    if ((curTick - beforeTick) >= 1000LL) {

                        beforeTick = curTick;
                        beforeFilePos = filePos;

                        double durSec = (double)(curTick - startTick) / 1000.0f;
                        double fprog = (double)(totalReadByteSize * 100LL) / (double)totalRawDataByteSize;
                        double expectedSec = (double)(durSec * 100LL) / fprog;

                        printf("%3.2f. %s %lld/%lld %lld%c,   %lld/%lld %3.2f%c  (Expected: %3.2f,  Remain: %3.2f sec) \n", 
                            durSec,
                            strRawDBFileName.c_str(), 
                            filePos, fileByteSize, (filePos * 100LL) / fileByteSize, '%',
                            totalReadByteSize, totalRawDataByteSize, fprog, '%',
                            expectedSec,
                            expectedSec - durSec
                        );
                    }

                }
                else {
                    break;
                }
            }

            fclose(fp);
        }

        curTick = Comm::OAL::System::GetTickCount64();
        PRINTF("\n\nDone,  Dur=%lld  \n", (curTick - startTick)/1000LL);

        delete[] recordBuf;
    }

};