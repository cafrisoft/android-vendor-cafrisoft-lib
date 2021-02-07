#include "App.hpp"
#include "Cmd.hpp"
#include <TESys/Property/Tester.hpp>

namespace TESysOperator {
    namespace Cmd {

        bool Verify::ChipID(int argc, const char** argv) {

            printf("<<Verify::ChipID>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "TESysShell verify chipid";


            if (boardID == TESys::Property::Tester::Board::GetExtraID()) {

                std::vector<int> vecBoardID = GetExtraBoardID();

                printf("Extra Board Count : %lld \n", vecBoardID.size());

                for (std::vector<int>::const_iterator it = vecBoardID.cbegin();
                    it != vecBoardID.cend();
                    it++) {

                    int bid = *it;

                    PRINTF("BoardID=%d [%s]\n", bid, linuxCmd);
                    App::Oper()->C_OHT_THO_RunLinuxCommand(bid, linuxCmd);
                }
            }
            else {
                App::Oper()->C_OHT_THO_RunLinuxCommand(boardID, linuxCmd);
                PRINTF("[%s]\n", linuxCmd);
            }

            return true;
        }


        bool Verify::Flash(int argc, const char** argv) {
        
            printf("<<Verify::Flash>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "TESysShell verify flash";
            App::Oper()->C_OHT_THO_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }

        bool Verify::PatternApp(int argc, const char** argv) {

            printf("<<Verify::PatternApp>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "TESysShell verify patternapp";
            App::Oper()->C_OHT_THO_RunLinuxCommand(boardID, linuxCmd);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }

        bool Verify::AdcRegulatorVREG1(int argc, const char** argv) {
        
            printf("<<Verify::AdcRegulatorVREG1>>\n");
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

        bool Verify::AdcStaticCurrent(int argc, const char** argv) {

            printf("<<Verify::AdcStaticCurrent>>\n");
            printf("\t VLIN1 <= 20 mA\n");
            printf("\t   VCI <= 3 mA\n");
            printf("\t VDDR  <= 90 mA\n");

            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "TESysShell verify adc_static_current";

            if (boardID == TESys::Property::Tester::Board::GetExtraID()) {

                std::vector<int> vecBoardID = GetExtraBoardID();

                printf("Extra Board Count : %lld \n", vecBoardID.size());

                for (std::vector<int>::const_iterator it = vecBoardID.cbegin();
                    it != vecBoardID.cend();
                    it++) {

                    int bid = *it;

                    PRINTF("BoardID=%d [%s]\n", bid, linuxCmd);
                    App::Oper()->C_OHT_THO_RunLinuxCommand(bid, linuxCmd);
                }
            }
            else {
                App::Oper()->C_OHT_THO_RunLinuxCommand(boardID, linuxCmd);
                PRINTF("[%s]\n", linuxCmd);
            }

            return true;
        }
    };
};


