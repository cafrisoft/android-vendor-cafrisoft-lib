#ifndef COMM_OAL_SYSTEM_HPP__
#define COMM_OAL_SYSTEM_HPP__

#include <Comm/Base/Object.hpp>

namespace Comm {
    namespace OAL {

        class System : public Base::Object {
        
        public:
            static long long GetTickCount64();
            static unsigned int GetTickCount32();
            static bool ExecuteProcess(std::string command, bool isBackground);
            static bool ExecutePython(std::string command, bool isBackground);
            static bool RebootRecovery();

            static bool IsCurProcess32Bits();  //���� �������� Process��  32bit���� �Ǵ�
            static bool IsCurProcess64Bits();  //���� �������� Process��  64bit���� �Ǵ�

            static bool SocketInit();

            static bool IsThisAppRun(std::string strAppName);
        };


    }; //end of namespace Net
}; //end of namespace Comm

#endif // #ifndef TESYSNETCLIENT_HPP

