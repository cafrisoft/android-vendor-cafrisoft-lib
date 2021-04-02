#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/System.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)


namespace Comm {
    namespace OAL {

        bool System::SocketInit() {

            return true;
        }


        long long System::GetTickCount64() {
        
            struct timespec now;
            clock_gettime(CLOCK_MONOTONIC, &now);
            return now.tv_sec * 1000LL + now.tv_nsec / 1000000LL;
        }

        unsigned int System::GetTickCount32() {
        
            struct timespec now;
            clock_gettime(CLOCK_MONOTONIC, &now);
            return (unsigned int)(now.tv_sec * 1000LL + now.tv_nsec / 1000000LL);
        }
               
        bool System::ExecuteProcess(std::string command, bool isBackground) {

            int sz = (int)command.size() + 1024;
            char* cmdBuf = new char[sz];
            assert(cmdBuf);

            if (isBackground) {
                sprintf(cmdBuf, "%s%c", command.c_str(), '&');
            }
            else {
                strcpy(cmdBuf, command.c_str());
            }
            system(cmdBuf);

            delete[] cmdBuf;
            return true;
        }
                

#if (CommOS==CommOS_ANDROID)
        
        bool System::RebootRecovery() {

            system("reboot recovery");

            return true;
        }

#else
        bool System::RebootRecovery() {

            return true;
        }


#endif


    }; //end of namespace OAL
}; //end of namespace Comm

#endif //#if (CommOS==CommOS_LINUX)
