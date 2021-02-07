#include <TESys/Global/BuildOptions.h>
#include <TESys/Control/Tester.hpp>
#include <Comm/Shell/Main.hpp>
#include "CmdTesterMgr.hpp"


int main(int argc, char* argv[]) {

    std::shared_ptr<Comm::Shell::CmdTesterMgr> cmdTestMgr = std::make_shared<Comm::Shell::CmdTesterMgr>();
    std::shared_ptr<Comm::Shell::Main> shellMain = std::make_shared<Comm::Shell::Main>("ctrl");

    shellMain->AddSubSet(cmdTestMgr);
    shellMain->Run();
    return 0;
}
