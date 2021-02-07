#ifndef COMM_OAL_EVENT_HPP
#define COMM_OAL_EVENT_HPP

#include <Comm/OAL/SyncObject.hpp>

namespace Comm {
namespace OAL {

    class Event : public Base::Object {

    public:
        static std::shared_ptr<Event> CreateObject(bool bInitialState, bool bManualReset, const char* eventName=NULL);

    protected:
        Event();
        virtual ~Event();
    
    public:
        virtual bool Wait() = 0;
        virtual bool SetEvent() = 0;
        virtual bool ResetEvent() = 0;
    };

}; //end of namespace Net
}; //end of namespace Comm

#endif // #ifndef TESYSNETCLIENT_HPP

