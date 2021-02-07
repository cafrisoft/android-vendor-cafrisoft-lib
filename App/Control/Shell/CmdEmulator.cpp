#include "Cmd.hpp"
#include <TESys/Property/Tester.hpp>
#include <TESys/Property/Path.hpp>
#include <TED/Api.h>
#include <TESys/TED/PowerSource.hpp>

namespace AppControlShell {
    namespace Cmd {

        bool Emulator::DisplayCommand(int argc, const char** argv) {
        
            /*
                Linux :
              
                Mipi Err :  #echo 102 > /opt/TESys/tmp/Property/Emulator/[BoardID]/TedMipiErr
                T2M Err :  #echo 102 > /opt/TESys/tmp/Property/Emulator/[BoardID]/TedT2MErr
                ESD Err :  #echo 102 > /opt/TESys/tmp/Property/Emulator/[BoardID]/TedESDErr
                      
            */
            int boardID = -1;

            if (argc != 1) {
                PRINTF("ERR : argument  \n");
                PRINTF("\t  usage) #emul disp [boardID]  \n");
                return false;
            }

            boardID = Comm::Utils::StringTool::ConvertNumberStringToInt(argv[0]);


            PRINTF("TedMipiErr ByteOffset0 Prop Path :  %s  0x%08X\n", 
                TESys::Property::Tester::ErrorClass::TedMipi_Emulator_Path_ByteOffset0(boardID).c_str(),
                TESys::Property::Tester::ErrorClass::TedMipi_Emulator_GetValue_ByteOffset0(boardID)&0xFF
            );
            PRINTF("TedMipiErr ByteOffset1 Prop Path :  %s 0x%08X\n", 
                TESys::Property::Tester::ErrorClass::TedMipi_Emulator_Path_ByteOffset1(boardID).c_str(),
                TESys::Property::Tester::ErrorClass::TedMipi_Emulator_GetValue_ByteOffset1(boardID) & 0xFF
            );

            PRINTF("TedT2MErr ByteOffset0 Prop Path :  %s 0x%08X\n", 
                TESys::Property::Tester::ErrorClass::TedT2M_Emulator_Path_ByteOffset0(boardID).c_str(),
                TESys::Property::Tester::ErrorClass::TedT2M_Emulator_GetValue_ByteOffset0(boardID) & 0xFF
            );
            PRINTF("TedT2MErr ByteOffset1 Prop Path :  %s 0x%08X\n", 
                TESys::Property::Tester::ErrorClass::TedT2M_Emulator_Path_ByteOffset1(boardID).c_str(),
                TESys::Property::Tester::ErrorClass::TedT2M_Emulator_GetValue_ByteOffset1(boardID) & 0xFF
            );

            PRINTF("TedESDErr ByteOffset0 Prop Path:  %s 0x%08X\n", 
                TESys::Property::Tester::ErrorClass::TedESD_Emulator_Path_ByteOffset0(boardID).c_str(),
                TESys::Property::Tester::ErrorClass::TedESD_Emulator_GetValue_ByteOffset0(boardID) & 0xFF
            );
            PRINTF("TedESDErr ByteOffset1 Prop Path:  %s 0x%08X\n", 
                TESys::Property::Tester::ErrorClass::TedESD_Emulator_Path_ByteOffset1(boardID).c_str(),
                TESys::Property::Tester::ErrorClass::TedESD_Emulator_GetValue_ByteOffset1(boardID) & 0xFF
            );

            return true;
        }

        bool Emulator::TedMipiErrSet(int argc, const char** argv) {
        
            unsigned char buf0;
            unsigned char buf1;
            int boardID = 1;

            if (argc != 3) {
                PRINTF("ERR : argument  \n");
                PRINTF("\t  usage) #emul mipierr [boardID] [buf0] [buf1]  \n");
                return false;
            }

            boardID = Comm::Utils::StringTool::ConvertNumberStringToInt(argv[0]);
            buf0 = Comm::Utils::StringTool::ConvertNumberStringToInt(argv[1]);
            buf1 = Comm::Utils::StringTool::ConvertNumberStringToInt(argv[2]);

            PRINTF("BoardID=%d \n", boardID);
            PRINTF("Buf0=0x%08x(%d)  \n", buf0&0xFF, buf0 & 0xFF);
            PRINTF("Buf1=0x%08x(%d) \n", buf1&0xFF, buf1 & 0xFF);

            TESys::Property::Tester::ErrorClass::TedMipi_Emulator_SetValue_ByteOffset0(boardID, buf0);
            TESys::Property::Tester::ErrorClass::TedMipi_Emulator_SetValue_ByteOffset1(boardID, buf1);

            return true;
        }

        bool Emulator::TedT2MErrSet(int argc, const char** argv) {
        
            unsigned char buf0;
            unsigned char buf1;
            int boardID = 1;

            if (argc != 3) {
                PRINTF("ERR : argument  \n");
                PRINTF("\t  usage) #emul t2merr [boardID] [buf0] [buf1]  \n");
                return false;
            }

            boardID = Comm::Utils::StringTool::ConvertNumberStringToInt(argv[0]);
            buf0 = Comm::Utils::StringTool::ConvertNumberStringToInt(argv[1]);
            buf1 = Comm::Utils::StringTool::ConvertNumberStringToInt(argv[2]);

            PRINTF("BoardID=%d \n", boardID);
            PRINTF("Buf0=0x%08x(%d)  \n", buf0 & 0xFF, buf0 & 0xFF);
            PRINTF("Buf1=0x%08x(%d) \n", buf1 & 0xFF, buf1 & 0xFF);

            TESys::Property::Tester::ErrorClass::TedT2M_Emulator_SetValue_ByteOffset0(boardID, buf0);
            TESys::Property::Tester::ErrorClass::TedT2M_Emulator_SetValue_ByteOffset1(boardID, buf1);


            return true;
        }

        bool Emulator::TedESDErrSet(int argc, const char** argv) {
        
            unsigned char buf0;
            unsigned char buf1;
            int boardID = 1;

            if (argc != 3) {
                PRINTF("ERR : argument  \n");
                PRINTF("\t  usage) #emul esderr [boardID] [buf0] [buf1]  \n");
                return false;
            }

            boardID = Comm::Utils::StringTool::ConvertNumberStringToInt(argv[0]);
            buf0 = Comm::Utils::StringTool::ConvertNumberStringToInt(argv[1]);
            buf1 = Comm::Utils::StringTool::ConvertNumberStringToInt(argv[2]);

            PRINTF("BoardID=%d \n", boardID);
            PRINTF("Buf0=0x%08x(%d)  \n", buf0 & 0xFF, buf0 & 0xFF);
            PRINTF("Buf1=0x%08x(%d) \n", buf1 & 0xFF, buf1 & 0xFF);

            TESys::Property::Tester::ErrorClass::TedESD_Emulator_SetValue_ByteOffset0(boardID, buf0);
            TESys::Property::Tester::ErrorClass::TedESD_Emulator_SetValue_ByteOffset1(boardID, buf1);


            return true;
        }

    };
};


