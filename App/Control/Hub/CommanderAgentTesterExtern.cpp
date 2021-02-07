#include "CommanderAgent.hpp"
#include <TESys/Property/Hub.hpp>

namespace TESysControlHub {

    int CommanderAgent::Tester::GetConnectedTesterCount() {
    
        OAL::Lock lock(_CsExtern);

        return _TesterItemArray->GetTesterItemCount();
    }

    bool CommanderAgent::Tester::BroadCast(const unsigned char* data, int dataSize) {
    
        OAL::Lock lock(_CsExtern);

        return _SrvTcpSock->Broadcast(data, dataSize);
    }
};
