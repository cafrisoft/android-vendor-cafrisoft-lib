#include "Notifier.hpp"
#include <TESys/Data/Status.hpp>
#include <TESys/Property/Hub.hpp>
#include <TESys/Net/PacketControl.hpp>

int main(int argc, char* argv[]) {

    Comm::OAL::Log::SysLogOpen(CLOG_TAG);
    Comm::OAL::Log::EnableDebug();

    //TESysDataAcq::AppGlobal::Init();

    /*
        Notifyer ����
          Mission1. Tester�� �۽��ϴ� NotifyPacket��  Operator�� ����
          Mission2. Hub�� �۽��ϴ� NotifyPacket�� Operator�� ����
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




