#ifndef COMM_OAL_MUTEX_HPP
#define COMM_OAL_MUTEX_HPP

#include <Comm/OAL/SyncObject.hpp>

namespace Comm {
namespace OAL {

    class Mutex : public SyncObject {

    public:
        static std::shared_ptr<Mutex> CreateObject(int key=9829);

    protected:
        int _Key;

    protected:
        Mutex(int key);
        virtual ~Mutex();

    public:
        virtual void* Handle() = 0;
    };

}; //end of namespace Net
}; //end of namespace Comm

#endif // #ifndef TESYSNETCLIENT_HPP

