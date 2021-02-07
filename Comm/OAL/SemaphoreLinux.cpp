#include <Comm/OAL/SemaphoreLinux.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

namespace Comm {
namespace OAL {

    SemaphoreLinux::SemaphoreLinux(int initialCount) {

        int ret;

        ret = sem_init(&_Semaphore, 0, initialCount);
        assert(ret == 0);

    }

    SemaphoreLinux::~SemaphoreLinux() {
    
        sem_destroy(&_Semaphore);
    }

    //세마포어값을 1 감소한다.  현재값이 ZERO이면 대기 
    void SemaphoreLinux::Wait_Decrease() {
        sem_wait(&_Semaphore);
    }
    
    //세마포어값을 1 증가한다.
    void SemaphoreLinux::Increase() {
        sem_post(&_Semaphore);
    }


}; //end of namespace Net
}; //end of namespace Comm

#endif // #if (TESYSOS==TESYSOS_ANDROID)
