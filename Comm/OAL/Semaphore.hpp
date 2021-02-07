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
        virtual void Wait_Decrease() = 0;  //세마포어값을 1 감소한다.  현재값이 ZERO이면 대기 
        virtual void Increase() = 0;       //세마포어값을 1 증가한다.
    };

}; //end of namespace Net
}; //end of namespace Comm

#endif // #ifndef TESYSNETCLIENT_HPP

