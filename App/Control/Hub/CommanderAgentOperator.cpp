#include "CommanderAgent.hpp"
#include <TESys/Property/Hub.hpp>
#include <TESys/Property/Net.hpp>

namespace TESysControlHub {
    

    CommanderAgent::Operator::Operator(CommanderAgent* notifier) :
    
        _CommanderAgent(notifier)
    {
        
        /*
            Operator Notify TCP 辑滚 家南 积己
        */
        struct Socket::TCP::Server::CreateConfig  createConfig = {
            TESys::Property::Net::GetHubCommanderAgentOperatorTcpPort(),
            TESys::Net::PacketControl::GetFixedPacketByteSize(),
            TESys::Property::Hub::GetMaxOperatorCount(),
            CommanderAgent::Operator::CallbackAcceptStub,
            CommanderAgent::Operator::CallbackReceiveStub,
            CommanderAgent::Operator::CallbackCloseStub,
            this
        };

        _SrvTcpSock = Socket::TCP::Server::CreateObject(createConfig);
        assert(_SrvTcpSock);

        _SrvTcpSock->SelectLoop(true);
        CLOGI("[CommanderAgent::Operator] TCPServerSocket Create ... OK (Port=%d)", _SrvTcpSock->GetPortNum());
    }

    CommanderAgent::Operator::~Operator() {
    
        int portNum = _SrvTcpSock->GetPortNum();

        _SrvTcpSock.reset();
        CLOGI("[CommanderAgent::Operator] TCPServerSocket Destroy (Port=%d)", portNum);
    }

    
    
};
