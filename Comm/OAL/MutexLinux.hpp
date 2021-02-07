#ifndef COMM_OAL_MUTEX_LINUX_HPP
#define COMM_OAL_MUTEX_LINUX_HPP

#include <Comm/OAL/Mutex.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID )

namespace Comm {
    namespace OAL {

        class MutexLinux : public Mutex {

        private:
            pthread_mutexattr_t _MutexAttr;
            pthread_mutex_t _Mutex;

        public:
            MutexLinux(int key);
            virtual ~MutexLinux();

            virtual void Lock();
            virtual void Unlock();
            virtual void* Handle();
        };

    }; //end of namespace Net
}; //end of namespace Comm


#endif //#if (TESYSOS==TESYSOS_ANDROID)
#endif // #ifndef TESYSNETCLIENT_HPP

