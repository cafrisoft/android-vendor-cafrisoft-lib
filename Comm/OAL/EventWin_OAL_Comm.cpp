#include <Comm/OAL/EventWin.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
namespace OAL {

    EventWin::EventWin(bool bInitialState, bool bManualReset, const char* eventName) 
    {
        _Event = ::CreateEvent(NULL, bManualReset ? TRUE : FALSE, bInitialState ? TRUE : FALSE, eventName);
        assert(_Event);
    }

    EventWin::~EventWin() {
    
        if (_Event != NULL) {
            ::CloseHandle(_Event);
        }
    }

    bool EventWin::Wait() {
        ::WaitForSingleObject(_Event, INFINITE);
        return true;
    }

    bool EventWin::SetEvent() {
        ::SetEvent(_Event);
        return true;
    }

    bool EventWin::ResetEvent() {
        ::ResetEvent(_Event);
        return true;
    }



}; //end of namespace Net
}; //end of namespace Comm

#endif // #if (TESYSOS==TESYSOS_ANDROID)
