#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/CriticalSectionLinux.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

namespace Comm {
namespace OAL {

    CriticalSectionLinux::CriticalSectionLinux() {
    
        pthread_mutexattr_init(&_MutexAttr);
        pthread_mutexattr_setpshared(&_MutexAttr, PTHREAD_PROCESS_SHARED);

        if (pthread_mutex_init(&_Mutex, &_MutexAttr) != 0) {
            assert(false);
        }

    }

    CriticalSectionLinux::~CriticalSectionLinux() {
    
        if (pthread_mutex_destroy(&_Mutex) != 0) {
            assert(false);
        }

        pthread_mutexattr_destroy(&_MutexAttr);
    }


    void CriticalSectionLinux::Lock() {
        pthread_mutex_lock(&_Mutex);
    }

    void CriticalSectionLinux::Unlock() {
        pthread_mutex_unlock(&_Mutex);
    }

}; //end of namespace Net
}; //end of namespace Comm

#endif // #if (TESYSOS==TESYSOS_ANDROID)
