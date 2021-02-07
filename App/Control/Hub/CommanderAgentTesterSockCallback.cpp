#include "CommanderAgent.hpp"
#include <TESys/Property/Hub.hpp>

namespace TESysControlHub {
       
    
    void CommanderAgent::Tester::CallbackAcceptStub(void* arg, std::shared_ptr<Socket::TCP::Client> cliSock) {
        CommanderAgent::Tester* pObj = (CommanderAgent::Tester*)arg;
        pObj->CallbackAccept(cliSock);
    }

    void CommanderAgent::Tester::CallbackReceiveStub(void* arg, std::shared_ptr<Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize) {
        CommanderAgent::Tester* pObj = (CommanderAgent::Tester*)arg;
        pObj->CallbackReceive(cliSock, data, dataSize);
    }

    void CommanderAgent::Tester::CallbackCloseStub(void* arg, std::shared_ptr<Socket::TCP::Client> cliSock) {
        CommanderAgent::Tester* pObj = (CommanderAgent::Tester*)arg;
        pObj->CallbackClose(cliSock);
    }

    void CommanderAgent::Tester::CallbackAccept(std::shared_ptr<Socket::TCP::Client> cliSock) {

    }

    void CommanderAgent::Tester::CallbackReceive(std::shared_ptr<Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize) {

        std::shared_ptr<TESys::Net::PacketControl> pack = std::make_shared<TESys::Net::PacketControl>(data);
        switch (pack->GetCommand()) {
            case TESys::Net::Command::Control::C_TH_HT_RegisterBoardID:  
                CmdProc_TH_HT_RegisterBoardID(cliSock, pack); 
                break;

        }
    }

    void CommanderAgent::Tester::CallbackClose(std::shared_ptr<Socket::TCP::Client> cliSock) {

        _TesterItemArray->DeleteThisTester(cliSock);

    }

};
