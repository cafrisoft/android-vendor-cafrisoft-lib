#include "Cmd.hpp"
#include <TESys/Property/FileSync.hpp>
#include <TESys/Property/Tester.hpp>

namespace AppControlShell {
    namespace Cmd {

        bool FileSync::DisplayInfo(int argc, const char** argv) {

            int boardID = TESys::Property::Tester::Board::GetID();

            if (boardID < 0) {
                PRINTF("ERROR: boardID is not defined!! \n");
                return false;
            }

            PRINTF("FileSync Display Info  BoardID=%d \n", boardID);
            
            PRINTF("LocalFullDirName : \n");
            for (int id = 0; id < (int)TESys::Property::FileSync::Ftp::DirID::MaxCount; id++) {

                PRINTF("\t[%s]\n", 
                        TESys::Property::FileSync::Ftp::LocalPathName(boardID, (TESys::Property::FileSync::Ftp::DirID)id).c_str());
            }
            PRINTF("\n\n");

            PRINTF("FtpFullDirName : \n");
            for (int id = 0; id < (int)TESys::Property::FileSync::Ftp::DirID::MaxCount; id++) {

                PRINTF("\t[%s]\n", 
                    TESys::Property::FileSync::Ftp::RemotePathName((TESys::Property::FileSync::Ftp::DirID)id).c_str());
            }
            PRINTF("\n\n");

            return true;
        }

        bool FileSync::CalCRC(int argc, const char** argv) {

            int boardID = TESys::Property::Tester::Board::GetID();

            PRINTF("CRC : %d \n", TESys::Property::FileSync::Ftp::CalCRC(boardID));

            return true;
        }
    };
};


