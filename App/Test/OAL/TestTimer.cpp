
#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/HeaderFiles.hpp>

using namespace Comm;

class MyTest : public Base::Object {

private:
    std::shared_ptr<OAL::Timer> _Timer;

public:
    MyTest();
    ~MyTest();

private:
    //virtual void EventTimerCallback(TimerID id);
    virtual void EventTimerCallbackTest0();
};

MyTest::MyTest() {
    _Timer = OAL::Timer::CreateObject(this, TimerID::Test0, 1000, true);
}

MyTest::~MyTest() {
    
}

#if 0
void MyTest::EventTimerCallback(TimerID id) {

    switch (id) {

        case TimerID::Test0:
            PRINTF("[MyTest::EventTimerCallback] Timer : %d ", OAL::System::GetTickCount32() / 1000);
            break;

        default:
            break;
    }

}
#endif

void MyTest::EventTimerCallbackTest0() {
    PRINTF("[MyTest::EventTimerCallback] Timer : %d ", OAL::System::GetTickCount32() / 1000);
}


void TestTimer() {

    MyTest mytest;

    PRINTF("Press 'x' to stop Program");

    while (true) {

#if 1
        char c = (char)getchar();
        if (c == 'x') {
            break;
        }

#else
        char readbuffer[128];
        fgets(readbuffer, 128, stdin);
        if (strcmp(readbuffer, "exit")==0) {
            break;
        }
#endif
    }

}