#include <Comm/OAL/System.hpp>
#include <Comm/Utils/StringTool.hpp>

namespace Comm {
    namespace OAL {

#if (CommOS==CommOS_WIN)
#define popen fopen
#define pclose fclose
#define PS_GRAP_CMD "ps | grep"

#elif (CommOS==CommOS_LINUX)
#define PS_GRAP_CMD "ps -A | grep"

#elif (CommOS==CommOS_ANDROID)
#define PS_GRAP_CMD "ps | grep"
#endif

        bool System::IsThisAppRun(std::string strAppName) {

            bool bIsRunThisApp = false;
            char cmd[128];
            FILE* fp;
            const int RES_BUF_BYTESIZE = 4096;
            char* resultBuf = new char[RES_BUF_BYTESIZE];
            assert(resultBuf);

            sprintf(cmd, "%s %s", PS_GRAP_CMD, strAppName.c_str());
            fp = popen(cmd, "r");
            if (fp) {

                char* s = fgets(resultBuf, RES_BUF_BYTESIZE, fp);
                if (s) {
                    char * b = strstr(s, strAppName.c_str());
                    if (b != NULL) {
                        bIsRunThisApp = true;
                    }
                }

                pclose(fp);
            }

            delete[] resultBuf;
            
            return bIsRunThisApp;
        }
        
        bool System::ExecutePython(std::string pyFileName, bool isBackground) {

            std::string strCmd;

            if (isBackground) {
                //sprintf(cmdBuf, "py %s", pyFileName.c_str());
                strCmd = Comm::Utils::StringFormat("py %s", pyFileName.c_str());
            }
            else {
                //sprintf(cmdBuf, "py %s &", pyFileName.c_str());
                strCmd = Comm::Utils::StringFormat("py %s &", pyFileName.c_str());
            }
            system(strCmd.c_str());

            //delete[] cmdBuf;
            return true;
        }

    }; //end of namespace OAL
}; //end of namespace Comm


