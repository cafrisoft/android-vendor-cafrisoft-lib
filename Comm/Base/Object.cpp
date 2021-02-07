#include <Comm/Base/Object.hpp>

namespace Comm {
namespace Base {

    
    Object::Object() {
    
    }

    Object::~Object() {
    
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



