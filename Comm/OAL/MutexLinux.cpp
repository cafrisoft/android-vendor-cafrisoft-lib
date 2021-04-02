#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/MutexLinux.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID )

#include <sys/file.h>

namespace Comm {
    namespace OAL {

        MutexLinux::MutexLinux(int  key) : Mutex(key) {

            pthread_mutexattr_init(&_MutexAttr);
            pthread_mutexattr_setpshared(&_MutexAttr, PTHREAD_PROCESS_SHARED);

            if (pthread_mutex_init(&_Mutex, &_MutexAttr) != 0) {
                assert(false);
            }
        }

        MutexLinux::~MutexLinux() {

            if (pthread_mutex_destroy(&_Mutex) != 0) {
                assert(false);
            }
            pthread_mutexattr_destroy(&_MutexAttr);
        }


        void MutexLinux::Lock() {

            pthread_mutex_lock(&_Mutex);
        }

        void MutexLinux::Unlock() {

            pthread_mutex_unlock(&_Mutex);

        }

        void* MutexLinux::Handle() {
            return (void*)&_Mutex;
        }

    }; //end of namespace Net
}; //end of namespace Comm

#endif // #if (TESYSOS==TESYSOS_ANDROID)
