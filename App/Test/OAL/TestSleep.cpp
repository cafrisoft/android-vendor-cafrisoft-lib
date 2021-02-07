
#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/HeaderFiles.hpp>

using namespace Comm;

void TestSleep() {

    while (true) {
        PRINTF("SleepTest : %d ", OAL::System::GetTickCount32()/1000 );
        OAL::Thread::Sleep(1000);
    }

}