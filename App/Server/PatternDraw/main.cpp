#include "PatternDraw.hpp"
#include <TESys/Data/Status.hpp>
#include <TESys/Property/Hub.hpp>
#include <TESys/Net/PacketControl.hpp>

static bool s_IsAppRun = true;

void sig_handler(int signo) {
    CLOGI("Received Kill Signal");
    s_IsAppRun = false;
}

int main(int argc, char* argv[]) {

#if (CommOS == CommOS_LINUX)
    signal(SIGINT, sig_handler);
#endif

    Comm::OAL::Log::SysLogOpen(CLOG_TAG);
    Comm::OAL::Log::EnableDebug();

    //TESysDataAcq::AppGlobal::Init();

    /*
        Notifyer ����
          Mission1. Tester�� �۽��ϴ� NotifyPacket��  Operator�� ����
          Mission2. Hub�� �۽��ϴ� NotifyPacket�� Operator�� ����
    */
    PatternDraw::Init();

    while (s_IsAppRun) {
        //Notify Status
        //NotifyStatus();
        Comm::OAL::Thread::Sleep(1000);
    }

    Comm::OAL::Log::SysLogClose();

    return 0;
}




