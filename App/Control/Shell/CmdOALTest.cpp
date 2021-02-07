#include "Cmd.hpp"
#include <TESys/Property/Tester.hpp>
#include <TESys/Net/PacketControl.hpp>
#include <Comm/Utils/Queue.hpp>
#include <Comm/OAL/ProcessMutex.hpp>
#include <TESys/Property/Path.hpp>
#include <Comm/OAL/System.hpp>

namespace AppControlShell {
    namespace Cmd {

        #define PROCESS_MUTEX_KEY 12340000

        bool OALTest::ProcessMutexRead(int argc, const char** argv) {
        
            std::shared_ptr<Comm::OAL::ProcessMutex> procMutex = Comm::OAL::ProcessMutex::CreateObject(PROCESS_MUTEX_KEY);
            assert(procMutex);

            unsigned int startTick, curTick, beforeTick;
            std::string strPathFileName;
            strPathFileName += Comm::Property::Path::GetTmpRoot();
            strPathFileName += Comm::Property::Path::GetFilePathDelimChar();
            strPathFileName += "ProcessMutexTestFile";

            startTick = Comm::OAL::System::GetTickCount32();
            beforeTick = startTick;
            while (true) {
                int rdsz = -1;
                int writeSuccessCount = -1;

                curTick = Comm::OAL::System::GetTickCount32();

                procMutex->Lock();

                FILE* fp = fopen(strPathFileName.c_str(), "rb");
                if (fp) {
                    rdsz = (int)fread(&writeSuccessCount, 1, sizeof(int), fp);
                    fclose(fp);
                    procMutex->Unlock();

                    if (rdsz != sizeof(int)) {
                        printf("-------------------------------ERROR: rdsz is %d \n", rdsz);
                        break;
                    }
                }
                else {
                    procMutex->Unlock();
                    printf("-------------------------------ERROR: file Opend \n");
                    break;
                }

                if ((curTick - beforeTick) > 1000) {
                    printf("%d. Cur writeSuccessCount : %d \n", (curTick-startTick)/1000, writeSuccessCount);
                    beforeTick = curTick;
                }

            }


            return true;
        }
        
        bool OALTest::ProcessMutexWrite(int argc, const char** argv) {

            std::shared_ptr<Comm::OAL::ProcessMutex> procMutex = Comm::OAL::ProcessMutex::CreateObject(PROCESS_MUTEX_KEY);
            assert(procMutex);

            int writeSuccessCount = 0;
            std::string strPathFileName;
            strPathFileName += Comm::Property::Path::GetTmpRoot();
            strPathFileName += Comm::Property::Path::GetFilePathDelimChar();
            strPathFileName += "ProcessMutexTestFile";

            while (true) {
                int wrsz = -1;
                procMutex->Lock();

                FILE* fp = fopen(strPathFileName.c_str(), "wb");
                if (fp) {
                    wrsz = (int)fwrite(&writeSuccessCount, 1, sizeof(int), fp);
                    fclose(fp);
                    procMutex->Unlock();

                    if (wrsz != sizeof(int)) {
                        printf("-------------------------------ERROR: wrsz is %d \n", wrsz);
                        break;
                    }
                    else {
                        writeSuccessCount++;
                    }
                }
                else {
                    procMutex->Unlock();
                    printf("-------------------------------ERROR: file Opend \n");
                    break;
                }


            }

            return true;
        }

        bool OALTest::IsFileSyncRun(int argc, const char** argv) {

            bool bFileSyncRun = Comm::OAL::System::IsThisAppRun("TESysFileSync");
            PRINTF("FileSync %s \n", bFileSyncRun ? "Running" : "Stopped");
        
            return true;
        }
        
    };
};


