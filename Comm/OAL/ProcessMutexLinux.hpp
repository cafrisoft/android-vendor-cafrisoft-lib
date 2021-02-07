#ifndef COMM_OAL_PROCESS_MUTEX_LINUX_HPP
#define COMM_OAL_PROCESS_MUTEX_LINUX_HPP

#include <Comm/OAL/ProcessMutex.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

namespace Comm {
    namespace OAL {

        class ProcessMutexLinux : public ProcessMutex {

        private:
            int _SemID;

        public:
            ProcessMutexLinux(int key);
            virtual ~ProcessMutexLinux();

            virtual void Lock();
            virtual void Unlock();
        };

    }; //end of namespace Net
}; //end of namespace Comm


#endif //#if (TESYSOS==TESYSOS_ANDROID)
#endif // #ifndef TESYSNETCLIENT_HPP

