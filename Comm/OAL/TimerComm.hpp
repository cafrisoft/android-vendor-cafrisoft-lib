#ifndef COMM_OAL_TIMERCOMM_HPP
#define COMM_OAL_TIMERCOMM_HPP

#include <Comm/OAL/Timer.hpp>
#include <Comm/OAL/Thread.hpp>

namespace Comm {
namespace OAL {

    class TimerComm : public Timer {

    private:
        std::shared_ptr<Thread> _Thread;
        bool _IsServiceRun;

    public:
        TimerComm(Base::Object* pObject, TimerID timerID, int timerTick);
        virtual ~TimerComm();
                
    public:
        virtual void Start();
        virtual void Stop();

    private:
        static void ServiceStub(void* arg);
        void Service();
    };

}; //end of namespace OAL
}; //end of namespace Comm


#endif // #ifndef COMM_OAL_TIMERCOMM_HPP

