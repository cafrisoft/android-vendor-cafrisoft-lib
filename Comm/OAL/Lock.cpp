#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/Lock.hpp>

namespace Comm {
namespace OAL {

    Lock::Lock(std::shared_ptr<SyncObject> syncObject) {
        _SyncObject = syncObject;
        _SyncObject->Lock();
    }

    Lock::~Lock() {
        _SyncObject->Unlock();
    }

};
};
