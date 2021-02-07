#include "App.hpp"
#include "Cmd.hpp"
#include <TESys/Property/Tester.hpp>

namespace TESysOperator {
    namespace Cmd {

        int ParseBoardID(int argc, const char** argv) {

            int boardID;
            
            if (argc == 0) {
                boardID = TESys::Property::Tester::Board::GetGeneralID();
            }
            else if (argc == 1) {
                boardID = atoi(argv[0]);
            }
            else {
                printf("ERROR : argument error \n");
                printf("\t ex1) #tester linuxcmd1    ## boardID=GeneralID\n");
                printf("\t ex2) #tester linuxcmd1 30  ## boardID=30       \n");
                printf("\t ex3) #tester linuxcmd1 %d  ## boardID=ExtraID\n", TESys::Property::Tester::Board::GetExtraID());
                return false;
            }

            if (boardID == TESys::Property::Tester::Board::GetGeneralID()) {
                printf("BoardID=%d (General ID) \n", boardID);
            }
            else if (boardID == TESys::Property::Tester::Board::GetExtraID()) {
                printf("BoardID=%d (Extra ID) \n", boardID);
            }
            else {
                printf("BoardID=%d \n", boardID);

                if( (boardID >= TESys::Property::Tester::Board::GetMinID()) 
                    && (boardID <= TESys::Property::Tester::Board::GetMaxID()) ) {
                    //Nothing to do 
                }
                else {
                    boardID = -1;
                }
            }

            return boardID;
        }


        bool TED::FrameRate_HS1_120Hz(int argc, const char** argv) {
        
            printf("<<FrameRate_HS1_120Hz>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            App::Oper()->C_OHT_RunLinuxCommand(boardID, "ted.wreg --offset=1 0x60 0x00");  //120Hz
            App::Oper()->C_OHT_RunLinuxCommand(boardID, "ted.wreg --offset=0 0xF7 0x07");  //Scr Update

            return true;
        }

        bool TED::FrameRate_Normal_60Hz(int argc, const char** argv) {

            printf("<<FrameRate_Normal_60Hz>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            App::Oper()->C_OHT_RunLinuxCommand(boardID, "ted.wreg --offset=1 0x60 0xC0");  //60Hz
            App::Oper()->C_OHT_RunLinuxCommand(boardID, "ted.wreg --offset=0 0xF7 0x07");  //Scr Update

            return true;
        }

        bool TED::FrameRate_HLPM_ON(int argc, const char** argv) {

            printf("<<FrameRate_HLPM_ON>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            //#VEH, BML 측정을 위하여 PWR_MODE 설정을 1로 변경 필요, 6A72h → 0x48로 설정 변경
            //    device.WREG0_15(dutIdx, 0xB0, 0x72)
            //    device.WREG0_15(dutIdx, 0x6A, 0x48)
            App::Oper()->C_OHT_RunLinuxCommand(boardID, "ted.wreg --offset=0x72 0x6A 0x48");


            //HLPM ON
            App::Oper()->C_OHT_RunLinuxCommand(boardID, "ted.wreg --offset=0 0x53 0x24");  
            

            return true;
        }

        bool TED::FrameRate_HLPM_OFF(int argc, const char** argv) {

            printf("<<FrameRate_HLPM_OFF>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            //#VEH, BML 측정을 위하여 PWR_MODE 설정을 1로 변경 필요, 6A72h → 0x48로 설정 변경
            //    device.WREG0_15(dutIdx, 0xB0, 0x72)
            //    device.WREG0_15(dutIdx, 0x6A, 0x48)
            App::Oper()->C_OHT_RunLinuxCommand(boardID, "ted.wreg --offset=0x72 0x6A 0x40");

            //HLPM OFF
            App::Oper()->C_OHT_RunLinuxCommand(boardID, "ted.wreg --offset=0 0x53 0x20");  

            return true;
        }

        bool TED::FrameRate_TE_Time(int argc, const char** argv) {

            printf("<<FrameRate_TE_Time>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "cat /sys/devices/platform/12860000.decon_f/tetime";
            App::Oper()->C_OHT_THO_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }

        bool TED::DD_FB_Blank_Enter(int argc, const char** argv) {

            printf("<<DD_FB_Blank_Enter>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "echo 1 > /sys/class/graphics/fb0/blank";
            App::Oper()->C_OHT_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }

        bool TED::DD_FB_Blank_Leave(int argc, const char** argv) {

            printf("<<DD_FB_Blank_Leave>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "echo 0 > /sys/class/graphics/fb0/blank";
            App::Oper()->C_OHT_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }

        bool TED::PatternDrawRed(int argc, const char** argv) {
        
            printf("<<PatternDrawRed>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "ted.ptrn paint,0x00FF0000";
            App::Oper()->C_OHT_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            linuxCmd = "ted.ptrn write,0";
            App::Oper()->C_OHT_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }

        bool TED::PatternDrawGreen(int argc, const char** argv) {

            printf("<<PatternDrawGreen>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "ted.ptrn paint,0x0000FF00";
            App::Oper()->C_OHT_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            linuxCmd = "ted.ptrn write,0";
            App::Oper()->C_OHT_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }
        
        bool TED::PatternDrawBlue(int argc, const char** argv) {

            printf("<<PatternDrawBlue>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "ted.ptrn paint,0x000000FF";
            App::Oper()->C_OHT_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            linuxCmd = "ted.ptrn write,0";
            App::Oper()->C_OHT_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }

        bool TED::PatternDrawWhite(int argc, const char** argv) {

            printf("<<PatternDrawWhite>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "ted.ptrn paint,0x00FFFFFF";
            App::Oper()->C_OHT_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            linuxCmd = "ted.ptrn write,0";
            App::Oper()->C_OHT_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }

        bool TED::PatternDrawBlack(int argc, const char** argv) {

            printf("<<PatternDrawBlack>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "ted.ptrn paint,0x00000000";
            App::Oper()->C_OHT_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            linuxCmd = "ted.ptrn write,0";
            App::Oper()->C_OHT_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }

        bool TED::PatternScreenVerify(int argc, const char** argv) {

            printf("<<PatternScreenVerify>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "ted.ptrn paint,0x00000000";
            App::Oper()->C_OHT_THO_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }

        bool TED::FlashWriter(int argc, const char** argv) {

            printf("<<FlashWriter>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "TESysFlashWriter";
            App::Oper()->C_OHT_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }

#if 0
        bool TED::FlashVerify(int argc, const char** argv) {
        
            printf("<<FlashVerify>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            //const char* linuxCmd = "TESysFlashWriter verify";
            const char* linuxCmd = "TESysShell verify flash";
            App::Oper()->C_OHT_THO_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }

        bool TED::AdcRegVREG1(int argc, const char** argv) {
        
            printf("<<AdcRegVREG1>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "TESysShell verify adcregvreg1";
            App::Oper()->C_OHT_THO_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }
#endif

    };
};


