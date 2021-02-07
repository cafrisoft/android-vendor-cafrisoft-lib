#include "Receiver.hpp"

int main(int argc, char* argv[]) {

    Comm::OAL::Log::SysLogOpen(SYSLOG_NAME);
    Comm::OAL::Log::EnableDebug();

    TESysDBRawData::Receiver::Init();

    while (true) {
        Comm::OAL::Thread::Sleep(1000);
    }

    Comm::OAL::Log::SysLogClose();

    return 0;
}




