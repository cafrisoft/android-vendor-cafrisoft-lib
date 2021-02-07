#include "Cmd.hpp"
#include <TESys/Property/Tester.hpp>
#include <TESys/Property/Path.hpp>
#include <TED/Api.h>
#include <TESys/Data/DataAcqDB.hpp>

namespace AppControlShell {
    namespace Cmd {

        static void Verify_ChipID() {

            int dutIdx = 0;
            int boardID = TESys::Property::Tester::Board::GetID();

            bool isDDEcho = TESys::Property::Tester::Board::IsDeviceDriveEchoOn();
            TESys::Property::Tester::Board::SetDeviceDriveEcho(false);

            //Write Status Flag
            unsigned char chipID[5];
            TedDD_DSIM_MipiReadReg(dutIdx, 0xD6, 0x00 /*byteOffset*/, 5, chipID, 5);
            
            printf("0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n",
                (int)chipID[0] & 0xFF,
                (int)chipID[1] & 0xFF,
                (int)chipID[2] & 0xFF,
                (int)chipID[3] & 0xFF,
                (int)chipID[4] & 0xFF);

            TESys::Property::Tester::Board::SetDeviceDriveEcho(isDDEcho);
        }


        /*
    # echo "0x39 0xc0 0x00 0x00 0x00 0x00 0x51" > / sys / devices / platform / 12870000.dsim / mipi2_rw
    # echo "0x39 0xc0 0x0f 0x00 0x00 0xff 0x01" > / sys / devices / platform / 12870000.dsim / mipi2_rw
    # echo "0x06 0xc1 0xff" > / sys / devices / platform / 12870000.dsim / mipi2_rw
    # cat / sys / devices / platform / 12870000.dsim / mipi2_rw
     0x34 0x07 0xFF 0x07 0xFF 0x07 0xFF 0x67 0x08 0x01 0x00 0x30 0x20 0x49 0x00 0x29
     0x06 0x40 0xC8 0x12 0xC1 0x90 0x1F 0x42 0x58 0x2B 0xC3 0x20 0x38 0x43 0xE8 0x44
     0xC4 0xB0 0x51 0x45 0x78 0x5D 0xC6 0x40 0x6A 0x47 0x08 0x76 0xC7 0xD0 0x83 0x48
     0x98 0x8F 0xC9 0x60 0x9C 0x4A 0x28 0xA8 0xCA 0xF0 0xB5 0x4B 0xB8 0xC1 0xCC 0x80
     0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00
     0x00

*/
        static void Verify_Flash() {

            const char* FLASH_BINARY_FILENAME = "/data/TESysData/firmware/avl8895-ted-flash.vec.bin";
            int dutIdx = 0;
            int boardID = TESys::Property::Tester::Board::GetID();

            bool isDDEcho = TESys::Property::Tester::Board::IsDeviceDriveEchoOn();
            TESys::Property::Tester::Board::SetDeviceDriveEcho(false);


            //Write Status Flag
            unsigned char cmdData1[5] = { 0x00, 0x00, 0x00, 0x00, 0x51 };
            TedDD_DSIM_MipiWriteReg15(dutIdx, 0xB0, 0x00);
            TedDD_DSIM_MipiWriteReg15(dutIdx, 0xC1 /*SPI Data*/, 0xFC);         //0xFC가 읽을 수 있게 하는 Flag인 것 같다. 
            TedDD_DSIM_MipiWriteReg39(dutIdx, 0xC0 /*regAddr*/, 5, cmdData1);   //Status Flag를 쓴다. 
            Comm::OAL::Thread::Sleep(100);

            //Send Read Command 
            const int DATA2_COUNT = 5;
            unsigned char cmdData2[DATA2_COUNT] = { 0x0f, 0x00, 0x00, 0xff, 0x01 };
            TedDD_DSIM_MipiWriteReg15(dutIdx, 0xB0, 0x00);
            TedDD_DSIM_MipiWriteReg39(dutIdx, 0xC0 /*regAddr*/, 5, cmdData2);
            Comm::OAL::Thread::Sleep(100);

            const int VERIFY_DATA_COUNT = 0xFF;
            unsigned char spibuf[VERIFY_DATA_COUNT];
            memset(spibuf, 0x0A, VERIFY_DATA_COUNT);
            TedDD_DSIM_MipiReadReg(dutIdx, 0xC1 /*regAddr*/, 0 /*byteOffset*/, VERIFY_DATA_COUNT /*readCnt*/, spibuf, VERIFY_DATA_COUNT /*maxByteSize*/);

            unsigned char filebuf[VERIFY_DATA_COUNT];
            memset(filebuf, 0x01, VERIFY_DATA_COUNT);
            FILE* fp = fopen(FLASH_BINARY_FILENAME, "rb");
            if (fp) {
                fseek(fp, 0x0F0000, SEEK_SET);
                fread(filebuf, 1, VERIFY_DATA_COUNT, fp);
                fclose(fp);
            }

            bool isVerifyOK;

            for (int i = 0; i < 32; i++) {

                //PRINTF("%d. 0x%02X 0x%02X \n", i, (int)filebuf[i] & 0xFF, (int)spibuf[i] & 0xFF);

                if (filebuf[i] == spibuf[i]) {
                    isVerifyOK = true;
                }
                else {
                    isVerifyOK = false;
                    break;
                }
            }
            
            if (isVerifyOK == true) {
                TESys::Property::Tester::ErrorClass::SetFlashWriterError(boardID, TESys::Property::Tester::ErrorClass::FlashWriter::Success);
                printf("Spi Flash Write Verify OK \n");
            }
            else {
                TESys::Property::Tester::ErrorClass::SetFlashWriterError(boardID, TESys::Property::Tester::ErrorClass::FlashWriter::VerifyFail);
                printf("Spi Flash Write Verify FAIL \n");
            }

            TESys::Property::Tester::Board::SetDeviceDriveEcho(isDDEcho);

        }
        
        static void Verify_PatternApp() {
            
            int err_cnt = 0;
            const int TEST_CNT = 3;
            int RR[TEST_CNT] = { 255, 30, 12 };
            int GG[TEST_CNT] = { 10, 255, 10 };
            int BB[TEST_CNT] = { 10, 20, 255};
            
            bool isDDEcho = TESys::Property::Tester::Board::IsDeviceDriveEchoOn();
            TESys::Property::Tester::Board::SetDeviceDriveEcho(false);

            TedPatternConnect();
            for (int i = 0; i < TEST_CNT; i++) {
                TedPatternPaint(RR[i], GG[i], BB[i], 0);
                TedPatternUpdateScreen();
                bool bflag = TedPatternScreenVerify(RR[i], GG[i], BB[i]) ? true : false;
                if (!bflag) {
                    err_cnt++;
                }
            }
            TedPatternPaint(0, 0, 0, 0);
            TedPatternUpdateScreen();
            TedPatternDisconnect();

            if (TedPatternScreenVerify(0, 0, 0) != True) {
                err_cnt++;
            }   

            if (err_cnt == 0) {
                printf("PtrnApp Verify OK\n");
            }
            else {
                printf("PtrnApp Verify FAIL (ErrCnt=%d) \n", err_cnt);
            }

            TESys::Property::Tester::Board::SetDeviceDriveEcho(isDDEcho);

        }

        bool Verify::All(int argc, const char** argv) {

            PRINTF("------------------------------------------------\n");
            PRINTF("Verify Flash\n");
            PRINTF("------------------------------------------------\n");
            Verify_Flash();
            PRINTF("\n");
            PRINTF("\n");

            PRINTF("------------------------------------------------\n");
            PRINTF("Verify PatternApp\n");
            PRINTF("------------------------------------------------\n");
            Verify_PatternApp();
            PRINTF("\n");
            PRINTF("\n");


            return true;
        }

        /*
            2020.11.13
            Regulaotr VREG1 전압은 ELVDD와 조합되어 Generator된다.
            Uboot에서 PowerSave모드가 ON이면 ELVDD 가 계단 모양을 나타낸다. 

            Blank Off/On상태에서 
            1초씩 5sample을 읽어서 표준편자 50mA 이하면 Success
        */
        static void Verify_AdcRegulatorVREG1() {
        
            int boardID = TESys::Property::Tester::Board::GetID();
            const int dutIdx = 0;
            const int psID = (int)TESys::TED::PowerSource::Reg::VREG1;
            int groupIdx = TedAdcGetGroupIndexByPsID(dutIdx, psID);
            int channelIdx = TedAdcGetChannelIndexByPsID(dutIdx, psID);
            
            const int SAMPLE_COUNT = 5;
            const int DELAY = 1000;
            int volt[SAMPLE_COUNT];

            bool isDDEcho = TESys::Property::Tester::Board::IsDeviceDriveEchoOn();
            
            TESys::Property::Tester::Board::SetDeviceDriveEcho(false);
            //PRINTF("FB_Blank ON (Panel Off)\n");
            TedDD_FB_blank(dutIdx, 1); //Blank Ok (Panel Off)
            Comm::OAL::Thread::Sleep(1000);
            //PRINTF("FB_Blank Off (Panel On)\n");
            TedDD_FB_blank(dutIdx, 0); //Blank Ok (Panel Off)
            Comm::OAL::Thread::Sleep(DELAY);
            TESys::Property::Tester::Board::SetDeviceDriveEcho(isDDEcho);
                        
            for (int i = 0; i < SAMPLE_COUNT; i++) {
                volt[i] = TedAdcGetVoltage(dutIdx, groupIdx, channelIdx);
                //PRINTF("Volt[%d] = %d \n", i, volt[i]);
                Comm::OAL::Thread::Sleep(DELAY);
            }

            int avg, stDev;
            int sum = 0;
            for (int i = 0; i < SAMPLE_COUNT; i++) {
                sum += volt[i];
            }
            avg = sum / SAMPLE_COUNT;

            sum = 0;
            for (int i = 0; i < SAMPLE_COUNT; i++) {
                sum += (volt[i]-avg) * (volt[i] - avg);
            }
            stDev = (int)sqrt(sum / SAMPLE_COUNT);

            PRINTF("AVG=%d StDev=%d \n", 
                avg, stDev);

            if (stDev < 20) {
                TESys::Property::Tester::ErrorClass::AdcRegVREG1_SetError(boardID, TESys::Property::Tester::ErrorClass::AdcRegVREG1::Success);
            }
            else {
                TESys::Property::Tester::ErrorClass::AdcRegVREG1_SetError(boardID, TESys::Property::Tester::ErrorClass::AdcRegVREG1::StDevTooBig);
            }

        }


        /*
            2020.11.19
            Static 상태에서,  
            VLIN/VCI 전류값 이상을 본다.  (시료 Shortage 발생 여부 확인)
        */
        static void Verify_AdcStaticCurrent() {

            bool bPtrnAppVerify;
            int boardID = TESys::Property::Tester::Board::GetID();
            const int dutIdx = 0;
            const int MONITORING_CURRENT_COUNT = 3;
            const int psID[MONITORING_CURRENT_COUNT] =
            {
                (int)TESys::TED::PowerSource::External::Vlin1,
                (int)TESys::TED::PowerSource::External::VCI,
                (int)TESys::TED::PowerSource::External::VDDR,
            };
            const float fAllowMaxCurr[MONITORING_CURRENT_COUNT] = { 20.00f, 3.00f, 90.00f };
            int groupIdx[MONITORING_CURRENT_COUNT];
            int channelIdx[MONITORING_CURRENT_COUNT];
            int curr[MONITORING_CURRENT_COUNT];
            float fcurr[MONITORING_CURRENT_COUNT];

            for (int i = 0; i < MONITORING_CURRENT_COUNT; i++) {
                groupIdx[i] = TedAdcGetGroupIndexByPsID(dutIdx, psID[i]);
                channelIdx[i] = TedAdcGetChannelIndexByPsID(dutIdx, psID[i]);
            }

            bool isDDEcho = TESys::Property::Tester::Board::IsDeviceDriveEchoOn();
            TESys::Property::Tester::Board::SetDeviceDriveEcho(false);
                        
            TedDD_FB_blank(dutIdx, 1); //Blank Ok (Panel Off)
            Comm::OAL::Thread::Sleep(3000);
            TedDD_FB_blank(dutIdx, 0); //Blank Ok (Panel ON)
            Comm::OAL::Thread::Sleep(3000);

            //Draw Black 
            TedPatternConnect();
            TedPatternPaint(0, 0, 0, 0);
            TedPatternUpdateScreen();
            TedPatternDisconnect();
            bPtrnAppVerify = TedPatternScreenVerify(0, 0, 0) ? true: false;

            if (bPtrnAppVerify) {

                Comm::OAL::Thread::Sleep(3000);

                //Read ADC , Current 
                for (int i = 0; i < MONITORING_CURRENT_COUNT; i++) {
                    curr[i] = TedAdcGetCurrent(dutIdx, groupIdx[i], channelIdx[i]);
                    fcurr[i] = (float)curr[i] / 100.0f;
                }

                char* szMsg = new char[8190];
                assert(szMsg);
                strcpy(szMsg, "");

                int errCnt = 0;
                //Print
                for (int i = 0; i < MONITORING_CURRENT_COUNT; i++) {
                    char szTmp[128];
                    sprintf(szTmp, "%s=%3.2fmA ", TESys::TED::PowerSource::GetName_ANA6707(psID[i]).c_str(), fcurr[i]);
                    strcat(szMsg, szTmp);

                    if (fcurr[i] >= fAllowMaxCurr[i]) {
                        errCnt++;
                    }
                }
                printf("%s ErrCnt=%d \n", szMsg, errCnt);
                delete[] szMsg;
            }
            else {
                printf("PtrnApp Verify FAIL\n");
            }

            TESys::Property::Tester::Board::SetDeviceDriveEcho(isDDEcho);
        }

        bool Verify::ChipID(int argc, const char** argv) {
            Verify_ChipID();
            return true;
        }

        bool Verify::Flash(int argc, const char** argv) {
            Verify_Flash();
            return true;
        }

        bool Verify::PatternApp(int argc, const char** argv) {
            Verify_PatternApp();
            return true;
        }

        bool Verify::AdcRegulatorVREG1(int argc, const char** argv) {
            Verify_AdcRegulatorVREG1();
            return true;
        }

        bool Verify::AdcStaticCurrent(int argc, const char** argv) {
            Verify_AdcStaticCurrent();
            return true;
        }
    };
};



