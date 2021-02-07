#include "Cmd.hpp"
#include <TESys/Property/Tester.hpp>
#include <TESys/Net/PacketControl.hpp>
#include <Comm/Utils/Queue.hpp>
#include <TESys/Property/FileSync.hpp>
#include <TESys/Property/Tester.hpp>
#include <Comm/Utils/Android.hpp>
#include <Comm/Property/Path.hpp>
#include <TESys/Property/PatternDraw.hpp>

namespace AppControlShell {
    namespace Cmd {


        bool Android::PrintCommandList(int argc, const char** argv) {

            int boardID = TESys::Property::Tester::Board::GetID();

            PRINTF("ADB Network Port Setting : \n");
            PRINTF("\t#setprop persist.adb.tcp.port 55555\n");
            PRINTF("\t#setprop service.adb.tcp.port 55555\n");

            PRINTF("Buid¸í·É \n");
            PRINTF("\tOTP: #./build.sh -m userdebug -o -- avl8895\n");
            
            return true;
        }
      
        bool Android::UpdatePackage(int argc, const char** argv) {
        
            int boardID = TESys::Property::Tester::Board::GetID();
            if (boardID < 0) {
                PRINTF("ERROR: BoardID is invalid \n");
                return false;
            }

            std::string strLocalFirmwarePathName = TESys::Property::FileSync::Ftp::LocalPathName(boardID, TESys::Property::FileSync::Ftp::DirID::Firmware);

            strLocalFirmwarePathName += Comm::Property::Path::GetFilePathDelimChar();
            strLocalFirmwarePathName += "full_target_package.zip";

            PRINTF("FW File : [%s]  \n", strLocalFirmwarePathName.c_str());

            Comm::Utils::Android::SetRecoveryCommand_UpdatePackage(strLocalFirmwarePathName);
            //Comm::Utils::Android::RebootForRecovery();

            return true;
        }

        bool Android::CheckPatternDrawApp(int argc, const char** argv) {
        
            bool isRun = Comm::Utils::Android::IsThisPackageActivityTop(TESys::Property::PatternDraw::GetPackageName());

            PRINTF("IsRun : %d  \n", isRun);
            if (!isRun) {
                Comm::Utils::Android::RunActivity(TESys::Property::PatternDraw::GetPackageName(), TESys::Property::PatternDraw::GetActivityName());
            }

            return true;
        }

        bool Android::DisplayInfo(int argc, const char** argv) {
        
            int w, h;
            bool bRet = Comm::Utils::Android::GetDisplayResolution(&w, &h, 1, 2);
            PRINTF("1st. Width=%d  Height=%d \n", w, h);

            bRet = Comm::Utils::Android::GetDisplayResolution(&w, &h, 1, 2);
            PRINTF("2nd. Width=%d  Height=%d \n", w, h);

            return true;
        }

        bool Android::GetPropInt(int argc, const char** argv) {
        
            const char* propName = "";
            int propValue;

            if (argc == 0) {
                PRINTF("ERROR : argument error, input 'propName' \n");
                PRINTF("\t ex1) aERROR : argument error, input 'propName' \n");
                return false;
            }
            else if (argc == 1) {
                propName = (const char*)argv[0];
            }
            else {
                PRINTF("ERROR : argument error, too many argument \n");
                return false;
            }

            propValue = Comm::Utils::Android::GetPropInt(propName);
            PRINTF("propName=[%s] \n", propName);
            PRINTF("propValue=[%d] \n", propValue);

            

            return true;
        }
    };
};


