#ifndef COMM_OAL_EVENTWIN_HPP
#define COMM_OAL_EVENTWIN_HPP

#include <Comm/OAL/Event.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
namespace OAL {

    class EventWin : public Event {

    private:
        HANDLE _Event;

    public:
        EventWin(bool bInitialOwn, bool bManualReset, const char* eventName = NULL);
        virtual ~EventWin();
        
        virtual bool Wait();
        virtual bool SetEvent();
        virtual bool ResetEvent();
    };

}; //end of namespace Net
}; //end of namespace Comm


#endif //#if (TESYSOS==TESYSOS_ANDROID)
#endif // #ifndef TESYSNETCLIENT_HPP

