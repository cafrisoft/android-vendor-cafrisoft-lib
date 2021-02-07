#ifndef COMM_OAL_SEMAPHORE_HPP__
#define COMM_OAL_SEMAPHORE_HPP__

#include <Comm/OAL/SyncObject.hpp>

namespace Comm {
namespace OAL {

    class Semaphore : public Base::Object {

    public:
        static std::shared_ptr<Semaphore> CreateObject(int initialCount);

    protected:
        Semaphore();
        virtual ~Semaphore();

    public:
        virtual void Wait_Decrease() = 0;  //��������� 1 �����Ѵ�.  ���簪�� ZERO�̸� ��� 
        virtual void Increase() = 0;       //��������� 1 �����Ѵ�.
    };

}; //end of namespace Net
}; //end of namespace Comm

#endif // #ifndef TESYSNETCLIENT_HPP

