#ifndef COMM_OAL_LOCK_HPP
#define COMM_OAL_LOCK_HPP

#include <Comm/OAL/SyncObject.hpp>

namespace Comm {
namespace OAL {

    class Lock {

    private:
        std::shared_ptr<SyncObject> _SyncObject;

    public:
        Lock(std::shared_ptr<SyncObject> syncObject);
        ~Lock();
    };

};
};

#endif
