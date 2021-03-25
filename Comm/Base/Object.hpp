#ifndef COMM_BASE_OBJECT_HPP
#define COMM_BASE_OBJECT_HPP

#include <Comm/Global/BuildOptions.h>

namespace Comm {

    enum class TimerID {
        Log = 100,
        Test0,
        Test1
    };


namespace Base {

    class Object {

    protected:
        time_t _InstStartTime;
        long long _InstStartTick;
        long long _InstBeforeTick;
        long long _InstCurTick;

    public:
        Object();
        virtual ~Object();

        time_t GetInstStartTime();
        long long GetInstStartTick();
        long long GetInstRunningTick();
        long long GetInstRunningSecond();

        /*
            �ٸ� ��ü���� �ڽ��� CallBack ȣ���Ű�� ���� Callback �Լ� 

            void OtherClass::Func() {
                 Me->EventCallback(arg);
            }
        */
        virtual void EventTimerCallback(TimerID id);
        virtual void EventTimerCallbackLog();
        virtual void EventTimerCallbackTest0();
        virtual void EventTimerCallbackTest1();
    };

}; // namespace Base 
}; // namespace Comm

#endif

