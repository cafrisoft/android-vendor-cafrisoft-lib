#ifndef COMM_OAL_TIMER__HPP
#define COMM_OAL_TIMER__HPP

#include <Comm/Base/Object.hpp>

namespace Comm {
namespace OAL {

    class Timer : public Base::Object {

    public:
        static std::shared_ptr<Timer> CreateObject(Base::Object* pObject, TimerID timerID, int timerTick, bool isDefaultStart);

    protected:
        Base::Object* _pObject;
        TimerID _TimerID;
        int _TimerTick;
        
    protected:
        Timer(Base::Object* pObject, TimerID timerID, int timerTick);
        virtual ~Timer();

    public:
        virtual void SetTick(int timerTick);
        virtual int GetTick();

        virtual void Start() = 0;
        virtual void Stop() = 0;
    };

    
}; //end of namespace Net
}; //end of namespace Comm

#endif // #ifndef TESYSNETCLIENT_HPP

