#include <Comm/OAL/Timer.hpp>
#include <Comm/OAL/TimerComm.hpp>

namespace Comm {
namespace OAL {

    std::shared_ptr<Timer> Timer::CreateObject(Base::Object* pObject, TimerID timerID, int timerTick, bool isDefaultStart) {

        std::shared_ptr<Timer> obj;

#if (CommOS==CommOS_WIN)
        obj = std::make_shared<TimerComm>(pObject, timerID, timerTick);

#elif (CommOS==CommOS_LINUX)
        obj = std::make_shared<TimerComm>(pObject, timerID, timerTick);

#elif (CommOS==CommOS_ANDROID)
        obj = std::make_shared<TimerComm>(pObject, timerID, timerTick);

#else
#error "Select OS"
#endif
        assert(obj);

        if (isDefaultStart) {
            obj->Start();
        }

        return obj;
    }


    Timer::Timer(Base::Object* pObject, TimerID timerID, int timerTick) :
        _pObject(pObject)
        ,_TimerID(timerID)
        ,_TimerTick(timerTick)
    {
    
    }

    Timer::~Timer() {
    
    }

    void Timer::SetTick(int timerTick) {
        _TimerTick = timerTick;
    }

    int Timer::GetTick() {

        return _TimerTick;
    }


}; //end of namespace Net
}; //end of namespace Comm
