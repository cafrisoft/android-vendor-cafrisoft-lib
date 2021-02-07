#include "App.hpp"
#include "Cmd.hpp"

namespace TESysOperator {
    namespace Cmd {
        
        bool FileSync::RunHubCalCRC(int argc, const char** argv) {

            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            App::Oper()->C_OH_RunHubCalCRC();

            return true;
        }

        bool FileSync::RunFileSync(int argc, const char** argv) {
        
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            App::Oper()->C_OHT_RunFileSync(TESys::Property::Tester::Board::GetGeneralID());

            return true;
        }

        bool FileSync::CalRemoteStorageCRC(int argc, const char** argv) {
        
            return true;
        }

        bool FileSync::DirAgingPythonFile(int argc, const char** argv) {
        
            
            App::Oper()->FileSyncRun();

            for (int i = 0; i < 10; i++) {
                if (App::Oper()->FileSyncIsDone()) {
                    break;
                }
                Comm::OAL::Thread::Sleep(100);
            }

            if (App::Oper()->FileSyncIsDone()) {

                int jobCnt = App::Oper()->FileSyncGetJobCount();
                int scCnt = App::Oper()->FileSyncGetScCount();
                int tcCnt = App::Oper()->FileSyncGetTcCount();

                int allocByteSize = jobCnt * 32 + scCnt * 32 + tcCnt + 32;
                char* szMsg = new char[allocByteSize];
                assert(szMsg);

                strcpy(szMsg, "");
                for (int i = 0; i < jobCnt; i++) {
                    int id = App::Oper()->FileSyncGetJobID(i);
                    char szTmp[32];
                    sprintf(szTmp, "JOB_%04d.py, ", id);
                    strcat(szMsg, szTmp);
                }
                PRINTF("%s \n", szMsg);

                strcpy(szMsg, "");
                for (int i = 0; i < scCnt; i++) {
                    int id = App::Oper()->FileSyncGetScID(i);
                    char szTmp[32];
                    sprintf(szTmp, "SC_%04d.py, ", id);
                    strcat(szMsg, szTmp);
                }
                PRINTF("%s \n", szMsg);

                strcpy(szMsg, "");
                for (int i = 0; i < tcCnt; i++) {
                    int id = App::Oper()->FileSyncGetTcID(i);
                    char szTmp[32];
                    sprintf(szTmp, "TC_%04d.py, ", id);
                    strcat(szMsg, szTmp);
                }
                PRINTF("%s \n", szMsg);

                delete[] szMsg;
            }
            else {
                PRINTF("ERROR: FileSyncIsDone \n");
            }

            return true;
        }

    };
};


