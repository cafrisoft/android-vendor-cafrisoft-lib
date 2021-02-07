#include "Notifier.hpp"
#include <TESys/Data/Status.hpp>
#include <TESys/Property/Hub.hpp>
#include <TESys/Net/PacketControl.hpp>

int main(int argc, char* argv[]) {

    Comm::OAL::Log::SysLogOpen(CLOG_TAG);
    Comm::OAL::Log::EnableDebug();

    //TESysDataAcq::AppGlobal::Init();

    /*
        Notifyer 생성
          Mission1. Tester가 송신하는 NotifyPacket을  Operator로 전달
          Mission2. Hub가 송신하는 NotifyPacket을 Operator로 전달
    */
    TESysDataAcq::Notifier::Init();

    while (true) {
        //Notify Status
        //NotifyStatus();
        Comm::OAL::Thread::Sleep(1000);
    }

    Comm::OAL::Log::SysLogClose();

    return 0;
}




