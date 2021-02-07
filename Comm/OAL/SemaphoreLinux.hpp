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

        virtual void Wait_Decrease();  //��������� 1 �����Ѵ�.  ���簪�� ZERO�̸� ��� 
        virtual void Increase();       //��������� 1 �����Ѵ�.
    };

}; //end of namespace Net
}; //end of namespace Comm


#endif //#if (TESYSOS==TESYSOS_ANDROID)
#endif // #ifndef TESYSNETCLIENT_HPP

