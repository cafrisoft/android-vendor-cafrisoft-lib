#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/TimerComm.hpp>


namespace Comm {
namespace OAL {

    TimerComm::TimerComm(Base::Object* pObject, TimerID timerID, int timerTick) : Timer(pObject, timerID, timerTick)
    , _IsServiceRun(false)
    {
        
    }

    TimerComm::~TimerComm() {
        this->Stop();
    }
        
    void TimerComm::Start() {
        if (_IsServiceRun == false) {
            _IsServiceRun = true;
            _Thread = Thread::CreateObject(TimerComm::ServiceStub, this);
        }
    }

    void TimerComm::Stop() {
        if (_IsServiceRun == true) {
            _IsServiceRun = false;
            _Thread.reset();
        }
    }

    void TimerComm::ServiceStub(void* arg) {
        TimerComm* pObj = (TimerComm*)arg;
        pObj->Service();
    }
    
    void TimerComm::Service() {
        while (_IsServiceRun) {
            _pObject->EventTimerCallback(_TimerID);
            Thread::Sleep(_TimerTick);
        }
    }

}; //end of namespace Net
}; //end of namespace Comm


