#include "CommanderAgent.hpp"
#include <TESys/Property/Hub.hpp>

namespace TESysControlHub {
    


    void CommanderAgent::Operator::CallbackAcceptStub(void* arg, std::shared_ptr<Socket::TCP::Client> cliSock) {
        CommanderAgent::Operator* pObj = (CommanderAgent::Operator*)arg;
        pObj->CallbackAccept(cliSock);
    }

    void CommanderAgent::Operator::CallbackReceiveStub(void* arg, std::shared_ptr<Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize) {
        CommanderAgent::Operator* pObj = (CommanderAgent::Operator*)arg;
        pObj->CallbackReceive(cliSock, data, dataSize);
    }

    void CommanderAgent::Operator::CallbackCloseStub(void* arg, std::shared_ptr<Socket::TCP::Client> cliSock) {
        CommanderAgent::Operator* pObj = (CommanderAgent::Operator*)arg;
        pObj->CallbackClose(cliSock);
    }

    void CommanderAgent::Operator::CallbackAccept(std::shared_ptr<Socket::TCP::Client> cliSock) {
    
    }

    void CommanderAgent::Operator::CallbackReceive(std::shared_ptr<Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize) {
    
        std::shared_ptr<TESys::Net::PacketControl> pack = std::make_shared<TESys::Net::PacketControl>(data);
        int command = (int)pack->GetCommand();

        if( (command > (int)TESys::Net::Command::Control::C_OHT_BEGIN)
            && (command < (int)TESys::Net::Command::Control::C_OHT_END)
            )
        {
            //CLOGI("[Hun::CommanderAgent::C_OHT] Cmd=%s", TESys::Net::Command::CmdToString(command).c_str());
            _CommanderAgent->GetTester()->BroadCast(data, dataSize);
        }
        else if ((command > (int)TESys::Net::Command::Control::C_OHT_THO_BEGIN)
            && (command < (int)TESys::Net::Command::Control::C_OHT_THO_END)
            )
        {
            //CLOGI("[Hun::CommanderAgent::C_OHT] Cmd=%s", TESys::Net::Command::CmdToString(command).c_str());
            _CommanderAgent->GetTester()->BroadCast(data, dataSize);
        }
        else if ((command > (int)TESys::Net::Command::Control::C_OH_BEGIN)
            && (command < (int)TESys::Net::Command::Control::C_OH_END)
            )
        {
            switch (pack->GetCommand()) {

                case TESys::Net::Command::Control::C_OH_RunHubCalCRC:
                    CmdProc_C_OH_RunHubCalCRC(cliSock, pack);
                    break;
            }
        }
        else {
            switch (pack->GetCommand()) {

                case TESys::Net::Command::Control::C_OH_HO_GetConnectedTesterCount:
                    CmdProc_C_OH_HO_GetConnectedTesterCount(cliSock, pack);
                    break;

#if 0
                case TESys::Net::Command::Control::C_OH_HO_GetFileCRC :
                    CmdProc_C_OH_HO_GetFileCRC(cliSock, pack);
                    break;
#endif
            }
        }
    }

    void CommanderAgent::Operator::CallbackClose(std::shared_ptr<Socket::TCP::Client> cliSock) {
    
    }

    
    
    
    
};
