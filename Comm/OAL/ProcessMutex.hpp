#ifndef COMM_OAL_PROCESS_MUTEX_HPP
#define COMM_OAL_PROCESS_MUTEX_HPP

#include <Comm/OAL/SyncObject.hpp>

namespace Comm {
namespace OAL {

    class ProcessMutex : public SyncObject {

    public:
        static std::shared_ptr<ProcessMutex> CreateObject(int key);

    protected:
        int _Key;

    protected:
        ProcessMutex(int key);
        virtual ~ProcessMutex();

    };

}; //end of namespace Net
}; //end of namespace Comm

#endif // #ifndef TESYSNETCLIENT_HPP

