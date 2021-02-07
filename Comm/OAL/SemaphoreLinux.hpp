#ifndef COMM_OAL_SEMAPHORE_LINUX_HPP__
#define COMM_OAL_SEMAPHORE_LINUX_HPP__

#include <Comm/OAL/Semaphore.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

namespace Comm {
namespace OAL {

    class SemaphoreLinux : public Semaphore {

    private:
        sem_t _Semaphore;

    public:
        SemaphoreLinux(int initialCount);
        virtual ~SemaphoreLinux();

        virtual void Wait_Decrease();  //세마포어값을 1 감소한다.  현재값이 ZERO이면 대기 
        virtual void Increase();       //세마포어값을 1 증가한다.
    };

}; //end of namespace Net
}; //end of namespace Comm


#endif //#if (TESYSOS==TESYSOS_ANDROID)
#endif // #ifndef TESYSNETCLIENT_HPP

