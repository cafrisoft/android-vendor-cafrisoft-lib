#include <Comm/OAL/System.hpp>

#if (CommOS==CommOS_WIN)


namespace Comm {
    namespace OAL {

        bool System::SocketInit() {
        
            WSADATA wsaData;

            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
            {
                fprintf(stderr, "WSAStartup() failed");
                assert(1);
            }

            return true;
        }

        long long System::GetTickCount64() {
            return ::GetTickCount64();
        }

        unsigned int System::GetTickCount32() {
            return ::GetTickCount();
        }

        //���� �������� Process��  32bit���� �Ǵ�
        bool System::IsCurProcess32Bits() {
#ifdef _WIN64
            return false;
#else
            return true;
#endif
        }

        //���� �������� Process��  64bit���� �Ǵ� 
        bool System::IsCurProcess64Bits() {
            return !System::IsCurProcess32Bits();
        }

        bool System::ExecuteProcess(std::string command, bool isBackground) {
        
            return true;
        }
        
        
        bool System::RebootRecovery() {

            return true;
        }


    }; //end of namespace OAL
}; //end of namespace Comm

#endif //#if (CommOS==CommOS_LINUX)
