#include "Cmd.hpp"
#include <TESys/Property/Tester.hpp>
#include <TESys/Property/Path.hpp>
#include <TESys/Property/FileSync.hpp>
#include <Comm/Utils/Android.hpp>

namespace AppControlShell {
    namespace Cmd {

        const char* Tester::CMD_TESTER = "tester";
        const char* Tester::CMD_GEN_FACTORY_DATA = "gen_factory_data";
      
         bool Tester::GetBoardID(int argc, const char** argv) {
        
             PRINTF("ConfigFile=%s \n", TESys::Property::Path::GetTesterFactoryDataRoot_BoardID().c_str());
             PRINTF("BoardID=%d \n", TESys::Property::Tester::Board::GetID());

             return true;
         }

         bool Tester::GenFactoryData(int argc, const char** argv) {

             if (argc != 1) {
                 PRINTF("ERROR : you have to input BoardID \n");
                 PRINTF("\t Ex)tester %s \n", Tester::CMD_GEN_FACTORY_DATA);
                 return false;
             }

             int boardID = atoi(argv[0]);

             
             PRINTF("-------------- Current Value ----------------------- \n");
             PRINTF("Current BoardID=%d \n", TESys::Property::Tester::Board::GetID());
             PRINTF("User-Input BoardID=%d \n", boardID);

             TESys::Property::Tester::Board::GenFactoryData(boardID);

             PRINTF("-------------- Check BoardID ----------------------- \n");
             PRINTF("New BoardID=%d \n", TESys::Property::Tester::Board::GetID());
             if (TESys::Property::Tester::Board::GetID() == boardID) {
                 PRINTF("BoardID Change OK \n");
             }
             else {
                 PRINTF("BoardID Change FAIL!! \n");
             }

             return true;
         }

         bool Tester::DisplayBoardInfo(int argc, const char** argv) {
         
             int boardID = TESys::Property::Tester::Board::GetID();

             std::string strIP = Comm::Utils::Android::GetIpAddrString("eth0");
             unsigned int ipI32 = Comm::Utils::Android::GetIpAddrI32("eth0");
             PRINTF("eth0-IP : %s  0x%08X\n", strIP.c_str(), ipI32);

             long long boardErrFlag = TESys::Property::Tester::ErrorClass::GetCurSysFlag(boardID);
             PRINTF("BoardErrFlag : 0x%016llX \n", boardErrFlag);

             TESys::Property::Tester::ErrorClass::FlashWriter flashWriterErr = TESys::Property::Tester::ErrorClass::GetFlashWriterError(boardID);
             PRINTF("System FlashWriter Error :  %s(%d)\n", TESys::Property::Tester::ErrorClass::FlashWriterToString(flashWriterErr).c_str(), (int)flashWriterErr);

             unsigned short patternAppErrFlag  = TESys::Property::Tester::ErrorClass::GetPatternDrawAppError(boardID);
             PRINTF("patternAppErrFlag :  0x%08x (%s)\n", patternAppErrFlag, TESys::Property::Tester::ErrorClass::PatternDrawAppToString(patternAppErrFlag).c_str());

             return true;
         }


        #define PS_GREP_PY "ps | grep py"
#if (CommOS == CommOS_WIN)

         static FILE* popen(const char* cmd, const char* mode) {
         
             FILE* fp = NULL;
             const char* fileName = "";

             if (strcmp(cmd, PS_GREP_PY) == 0) {
                 fileName = "C:\\Temp\\TESys\\Property\\ANDROID_CMD_ps_grep_py.txt";

                 fp = fopen(fileName, "w");
                 assert(fp);
                 fprintf(fp, "root      3788  1     30868  19756 hrtimer_na 721df37c48 S py");
                 fclose(fp);
             }

             fp = fopen(fileName, mode);
             return fp;
         }

         static void pclose(FILE* fp) {
             fclose(fp);
         }

#endif

         bool Tester::KillPython(int argc, const char** argv) {

#if 1
             char szCmd[32];
             int pid = TESys::Property::Tester::Board::GetPyPID();
             
             if (pid != -1) {
                 sprintf(szCmd, "kill %d", pid);
                 system(szCmd);
                 PRINTF("Kill Py-PID=%d \n", pid);
             }
             else {
                 PRINTF("Py-PID=%d \n", pid);
             }

#else
             FILE* fp = popen(PS_GREP_PY, "r");
             if (fp) {

                 char buf[256];
                 int pid = -1;
                 char szPy[32]="";

                 while (true) {
                     char* p = fgets(buf, 256, fp);
                     if (p == NULL) {
                         break;
                     }

                     //char* a, * b;

                     /*
                        다음 Format의 문자열이 나와야 한다.
                        "root      3788  1     30868  19756 hrtimer_na 721df37c48 S py"
                     */

                     //py 라는 글자가 

                     //a = p;
                     //b = strstr(a, "root");
                     //if (b) {
                     //    a = b + strlen("root");
                     //}

                     char szRoot[8];
                     
                     int res1, res2, res3;
                     char szStat[64];
                     char szNum[64];
                     char szRes1[32];
                     
                     sscanf(p, "%s %d %d %d %d %s %s %s %s",
                         szRoot,
                         &pid, &res1, &res2, &res3,
                         szStat, szNum, szRes1, szPy);
                 }
             
                 pclose(fp);

                 char szCmd[32];

                 PRINTF("PyName(%s)-PID=%d \n", szPy, pid);
                 if (pid != -1) {
                     sprintf(szCmd, "kill %d", pid);
                     system(szCmd);
                 }
             }
             else {
                 PRINTF("FAIL:  popen(%s..) \n", PS_GREP_PY);
             }
#endif

             return true;
         }

         bool Tester::PythonPID(int argc, const char** argv) {

             int pid = TESys::Property::Tester::Board::GetPyPID();
             PRINTF("Py-PID=%d \n", pid);

             return true;
         }

         bool Tester::FWUpgrade(int argc, const char** argv) {
             
             char cResp;
             int boardID = TESys::Property::Tester::Board::GetID();

             printf("Do you want to upgrade Android Firmware? (y/n) : ");
             cResp = getc(stdin);
             if (cResp == 'y' || cResp == 'Y') {
                
             }
             else {
                 printf("Cancel command\n");
                 return false;
             }

             std::string fwUpgradeFileName = TESys::Property::FileSync::Ftp::LocalPathFileName(boardID,
                TESys::Property::FileSync::Ftp::DirID::Firmware,
                TESys::Property::Tester::Board::GetFWUpgradeFileName());

             if (Comm::OAL::FileSys::IsThisFileExist(fwUpgradeFileName)) {

                int err = 0;
                FILE* fp_cmd;
                const char* RECOVERY_COMMAND_FILENAME = "/cache/recovery/command";
                const int COMMAND_BUF_SIZE = 8192;
                char* recoveryCommand = new char[COMMAND_BUF_SIZE];
                assert(recoveryCommand);
                char* verifyCommand = new char[COMMAND_BUF_SIZE];
                assert(verifyCommand);

                sprintf(recoveryCommand, "--update_package=%s", fwUpgradeFileName.c_str());

                printf("FileName=[%s] \n", RECOVERY_COMMAND_FILENAME);
                printf("Cmd=[%s] \n", recoveryCommand);

                //Write Recover Command
                fp_cmd = fopen(RECOVERY_COMMAND_FILENAME, "w");
                if (fp_cmd) {
                    fprintf(fp_cmd, "%s", recoveryCommand);
                    fclose(fp_cmd);
                    //printf("FileWrite Done");
                }
                else {
                    printf("ERROR: Can't open for write [%s]\n", RECOVERY_COMMAND_FILENAME);
                    err++;
                }

                //Verify Recovery Command 
                fp_cmd = fopen(RECOVERY_COMMAND_FILENAME, "r");
                if (fp_cmd) {
                    fgets(verifyCommand, COMMAND_BUF_SIZE, fp_cmd);
                    fclose(fp_cmd);

                    Comm::Utils::StringTool::RemoveCharInStringFromBack(verifyCommand);
                    Comm::Utils::StringTool::RemoveCharInStringFromBack(recoveryCommand);

                    //CLOGI("[Tester::CommandReceiver::CmdProc::C_OHT_RunFWUpgrade]  verifyCommand=[%s]", verifyCommand);

                    if (strcmp(verifyCommand, recoveryCommand) == 0) {
                        printf("Verify OK\n");
                    }
                    else {
                        printf("Verify FAIL\n");
                        err++;
                    }
                }
                else {
                    printf("Can't find recovery cmd files [%s]\n", RECOVERY_COMMAND_FILENAME);
                    err++;
                }

                if (err == 0) {
                    Comm::OAL::Thread::Sleep(1000);

                    printf("reboot recovery FW[%s]\n", fwUpgradeFileName.c_str());
                    OAL::System::RebootRecovery();

                    Comm::OAL::Thread::Sleep(2000);
                    printf("FAIL :  run 'reboot recovery'\n");
                }

                delete[] recoveryCommand;
                delete[] verifyCommand;
             }
             else {
                printf("FAIL : cannot find FWUpgrade File\n");
             }

             return true;
         }
    };
};


