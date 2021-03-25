#include <Comm/Base/Object.hpp>
#include <Comm/OAL/System.hpp>
#include <Comm/OAL/DateTime.hpp>

namespace Comm {
namespace Base {

    
    Object::Object() {
    
        _InstStartTick = Comm::OAL::System::GetTickCount64();
        _InstBeforeTick = _InstStartTick;
        _InstCurTick = _InstStartTick;
        _InstStartTime = Comm::OAL::DateTime::GetUtcTime();
    }

    Object::~Object() {
    
    }

    time_t Object::GetInstStartTime() {

        return _InstStartTime;
    }

    long long Object::GetInstStartTick() {

        return _InstStartTick;
    }

    long long Object::GetInstRunningTick() {

        long long curTick = Comm::OAL::System::GetTickCount64();

        return curTick - _InstStartTick;
    }

    long long Object::GetInstRunningSecond() {
        
        return GetInstRunningTick() / 1000LL;
    }


    void Object::EventTimerCallback(TimerID id) {

        switch (id) {
            case  TimerID::Log:
                this->EventTimerCallbackLog();
                break;

            case  TimerID::Test0:
                this->EventTimerCallbackTest0();
                break;

            case  TimerID::Test1:
                this->EventTimerCallbackTest1();
                break;

            default:
                break;
        }

    }

    void Object::EventTimerCallbackLog() {
    
    }

    void Object::EventTimerCallbackTest0() {

    }

    void Object::EventTimerCallbackTest1() {

    }
    
}; // namespace Base 
}; // namespace Comm



