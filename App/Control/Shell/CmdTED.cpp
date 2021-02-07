#include "Cmd.hpp"
#include <TESys/Property/Tester.hpp>
#include <TESys/Property/Path.hpp>
#include <TED/Api.h>
#include <TESys/TED/PowerSource.hpp>

namespace AppControlShell {
    namespace Cmd {


#if 0
         bool TED::LdoAdc(int argc, const char** argv) {

             //TedLdoAdcGetChannelCount(0);
             
             return true;
         }
#endif

         bool TED::ChipID(int argc, const char** argv) {

             unsigned char chipIDArr[8];
             char szMsg[256]="";
             const int dutIdx = 0;

             TedSysSetBoardID(10);
             TedANA670X_GetChipIDCount();
             TedANA670X_GetChipID(dutIdx, chipIDArr);

             for (int i = 0; i < TedANA670X_GetChipIDCount(); i++) {
                 char szTmp[32];
                 sprintf(szTmp, "0x%02X ", (int)chipIDArr[i]&0xFF);
                 strcat(szMsg, szTmp);
             }
             PRINTF("CHIPID(%d) :  %s \n", dutIdx, szMsg);

             return true;
         }

         bool TED::Test1(int argc, const char** argv) {

#if 0
             unsigned char chipIDArr[8];
             char szMsg[256] = "";
             const int dutIdx = 0;

             TedANA670X_GetChipIDCount();
             TedANA670X_GetChipID(dutIdx, chipIDArr);

             for (int i = 0; i < TedANA670X_GetChipIDCount(); i++) {
                 char szTmp[32];
                 sprintf(szTmp, "0x%02X ", (int)chipIDArr[i] & 0xFF);
                 strcat(szMsg, szTmp);
             }
             PRINTF("CHIPID(%d) :  %s \n", dutIdx, szMsg);
#endif


#if 1

             TedPatternScreenVerify(0, 0, 0);


#endif

             return true;
         }

         bool TED::PatternDrawConnect(int argc, const char** argv) {
         
             TedPatternConnect();

             return true;
         }

         bool TED::PatternDrawDisconnect(int argc, const char** argv) {
         
             TedPatternDisconnect();

             return true;
         }

         bool TED::PatternDrawSendCommand(int argc, const char** argv) {
         
             TedPatternSetCommand("Paint,0x00000000");

             return true;
         }

         bool TED::PatternScreenVerify(int argc, const char** argv) {

             bool isVerify;
             unsigned char r, g, b;

             printf("<<TED::PatternScreenVerify>> \n");

             if (argc == 3) {
                 r = (unsigned char)atoi(argv[0]);
                 g = (unsigned char)atoi(argv[1]);
                 b = (unsigned char)atoi(argv[2]);
             }
             else {
                 printf("ERROR : argument error \n");
                 printf("\t ex1) #ted ptrn_screen_verify [red] [green] [blue]\n");
                 return false;
             }

             printf("R = %d \n", (int)r&0xff);
             printf("G = %d \n", (int)g & 0xff);
             printf("B = %d \n", (int)b & 0xff);

         
             isVerify = TedPatternScreenVerify(r /*Red*/, g /*green*/, b /*blue*/);

             printf("------------------------------------------------\n");
             printf("Verify %s \n", isVerify?"OK" : "FAIL" );
             printf("------------------------------------------------\n");
             printf("\n");

             return true;
         }

         bool TED::AgingMeasureADC(int argc, const char** argv) {

             TedAgingMeasureADC(0, NULL);
             return true;
         }

         bool TED::MonitorEXTCurrent(int argc, const char** argv) {
         
             int loop = 0;
             int dutIdx = 0;
             int groupIdx = TedAdcGetGroupIndexByName(dutIdx, "EXT");
             int chIdx = 0;
             int chCnt = TedAdcGetChannelCount(dutIdx, groupIdx);
             char* szMsg = new char[8196];
             assert(szMsg);


             while (true) {

                 strcpy(szMsg, "");

                 for (int ich = 0; ich < chCnt; ich++) {
                     char szTmp[64];
                     char chName[64];
                     TedAdcGetChannelName(dutIdx, groupIdx, ich, chName);
                     int adcValue = TedAdcGetCurrent(dutIdx, groupIdx, ich);
                     sprintf(szTmp, "%s=%5d  ", chName, adcValue);
                     strcat(szMsg, szTmp);
                 }
                 PRINTF("%d. %s \n", loop+1, szMsg);
                 Comm::OAL::Thread::Sleep(1000);

                 loop++;
             }

             delete[] szMsg;
             return true;
         }

         bool TED::FlashVerify(int argc, const char** argv) {

             /*
                Verify ¸í·É 
                    #echo "0x39 0xc0 0x00 0x00 0x00 0x00 0x51" > /sys/devices/platform/12870000.dsim/mipi2_rw

                    #echo "0x39 0xc0 0x0f 0x00 0x00 0xff 0x01" >  /sys/devices/platform/12870000.dsim/mipi2_rw

                    #echo "0x06 0xc1 0xff" > /sys/devices/platform/12870000.dsim/mipi2_rw
             */

             return true;
         }
                 

         bool TED::SetFrameRate(int argc, const char** argv) {
         
             int frameRate;

             if (argc == 1) {
                 frameRate = atoi(argv[0]);
             }
             else {
                 printf("ERROR : argument error \n");
                 printf("\t ex1) #ted setfr [frameRate]   ## fr = 30, 60, 90\n");
                 return false;
             }

             return TedANA670X_SetFrameRate(0, frameRate);
         }

         bool TED::GetFrameRate(int argc, const char** argv) {
         
             int fr = TedANA670X_GetFrameRate(0);
             PRINTF("Fr = %d \n", fr);

             return true;
         }


         bool TED::Test2(int argc, const char** argv) {

             int dutIdx = 0;
             int groupIdx = TedAdcGetGroupIndexByName(dutIdx, "EXT");
             int chCnt = TedAdcGetChannelCount(dutIdx, groupIdx);
             //int chIdx = 1;
             char szTmp[128];
             char* szMsg = new char[1024 * 8];
             assert(szMsg);

             const int FR_COUNT = 3;
             int frameRateArr[FR_COUNT] = { 30, 60, 120 };

             int volt[32];
             int curr[32];
             
             while (true) {

                 for (int ifr = 0; ifr < FR_COUNT; ifr++) {
                     
                     PRINTF("------------------------------------------- \n");
                     PRINTF("SetFR : %d\n", frameRateArr[ifr]);
                     PRINTF("------------------------------------------- \n");
                     TedANA670X_SetFrameRate(dutIdx, frameRateArr[ifr]);

                     for (int iloop = 0; iloop < 60; iloop++) {
                         TedAdcGetAllVoltage(dutIdx, groupIdx, volt);
                         TedAdcGetAllCurrent(dutIdx, groupIdx, curr);

                         strcpy(szMsg, "V[");
                         for (int i = 0; i < chCnt; i++) {
                             //PRINTF("%s=%3.2fmA \n", szChName, (float)adcValue / 100.0f);
                             sprintf(szTmp, "%d ", volt[i]);
                             strcat(szMsg, szTmp);
                         }
                         strcat(szMsg, "] A[");
                         for (int i = 0; i < chCnt; i++) {
                             sprintf(szTmp, "%d ", curr[i]);
                             strcat(szMsg, szTmp);
                         }
                         strcat(szMsg, "]");

                         PRINTF("%s \n", szMsg);
                         Comm::OAL::Thread::Sleep(1000);
                     }

                     PRINTF("\n\n");
                 }
             }

             delete[] szMsg;

             return true;
         }
    };
};


