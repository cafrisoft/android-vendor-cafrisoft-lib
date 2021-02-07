#ifndef COMM_OAL_SEMAPHORE_WIN_HPP__
#define COMM_OAL_SEMAPHORE_WIN_HPP__

#include <Comm/OAL/Semaphore.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
namespace OAL {

    class SemaphoreWin : public Semaphore {

    private:
        HANDLE _hSema;

    public:
        SemaphoreWin(int initialCount);
        virtual ~SemaphoreWin();

        virtual void Wait_Decrease();  //세마포어값을 1 감소한다.  현재값이 ZERO이면 대기 
        virtual void Increase();       //세마포어값을 1 증가한다.
    };

}; //end of namespace Net
}; //end of namespace Comm


#endif //#if (TESYSOS==TESYSOS_ANDROID)
#endif // #ifndef TESYSNETCLIENT_HPP

