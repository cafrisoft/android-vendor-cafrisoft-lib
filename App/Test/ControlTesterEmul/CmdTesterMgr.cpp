#include "CmdTesterMgr.hpp"
#include <TESys/Control/Tester.hpp>

#define THIS_COMMAND "tmgr"

std::shared_ptr<TESys::Control::Tester> s_Tester;

static bool TMgrCreateTester(int argc, char* argv[]) {

    bool bRet;
    printf("TMgrCreateTester \n");

    s_Tester = std::make_shared<TESys::Control::Tester>(100);
    bRet = s_Tester->Start();

    return true;
}

static bool TMgrDestroyTester(int argc, char* argv[]) {

    printf("TMgrDestroyTester \n");

    return true;
}

namespace Comm {
    namespace Shell {

        CmdTesterMgr::CmdTesterMgr() : CmdSet(THIS_COMMAND) {

            this->AddItem("new", "create new tester", TMgrCreateTester);
            this->AddItem("del", "delete tester", TMgrDestroyTester);

        }
  
        
    };
};
