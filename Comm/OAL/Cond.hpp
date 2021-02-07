#ifndef COMM_OAL_COND_HPP
#define COMM_OAL_COND_HPP

#include <Comm/OAL/Mutex.hpp>

namespace Comm {
namespace OAL {

    class Cond : public Base::Object {

    public:
        static std::shared_ptr<Cond> CreateObject();
    
    protected:
        Cond();
        virtual ~Cond();

    public:
        virtual void Signal() = 0;
        virtual void Wait(std::shared_ptr<Mutex> mutex) = 0;
    };

}; //end of namespace Net
}; //end of namespace Comm

#endif // #ifndef TESYSNETCLIENT_HPP

