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

        virtual void Wait_Decrease();  //��������� 1 �����Ѵ�.  ���簪�� ZERO�̸� ��� 
        virtual void Increase();       //��������� 1 �����Ѵ�.
    };

}; //end of namespace Net
}; //end of namespace Comm


#endif //#if (TESYSOS==TESYSOS_ANDROID)
#endif // #ifndef TESYSNETCLIENT_HPP

