#include "App.hpp"
#include "Cmd.hpp"

namespace TESysOperator {
    namespace Cmd {


        bool Hub::DisplayStatus(int argc, const char** argv) {
        
            App::Inst()->HubStatus()->DisplayStatus();

            return true;
        }
        
        

    };
};


