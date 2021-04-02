#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/Event.hpp>
#include <Comm/OAL/EventWin.hpp>
//#include <Comm/OAL/EventLinux.hpp>

namespace Comm {
    namespace OAL {

        std::shared_ptr<Event> Event::CreateObject(bool bInitialState, bool bManualReset, const char* eventName) {

            std::shared_ptr<Event> obj;

#if (CommOS==CommOS_WIN)
            obj = std::make_shared<EventWin>(bInitialState, bManualReset, eventName);

#else
#error "Select OS"
#endif
            assert(obj);

            return obj;
        }


        Event::Event() {

        }

        Event::~Event() {

        }


    }; //end of namespace Net
}; //end of namespace Comm
