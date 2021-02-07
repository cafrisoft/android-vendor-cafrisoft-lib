#include <TESys/Global/BuildOptions.h>
#include <TESys/Control/Tester.hpp>
#include <Comm/Shell/Main.hpp>


int main(int argc, char* argv[]) {

    std::shared_ptr<Comm::Shell::Main> shellMain = std::make_shared<Comm::Shell::Main>("ctrl");

    shellMain->Run();
    return 0;
}
