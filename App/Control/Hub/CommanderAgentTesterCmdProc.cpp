#include "CommanderAgent.hpp"

namespace TESysControlHub {

    void CommanderAgent::Tester::CmdProc_TH_HT_RegisterBoardID(std::shared_ptr<Socket::TCP::Client> cliSock, std::shared_ptr<TESys::Net::PacketControl> reqPack) {
    
        bool bResult = false;
        int boardID = reqPack->GetInt(0);
        int boardOS = reqPack->GetInt(1);
        std::shared_ptr<TESys::Net::PacketControl> respPack = std::make_shared<TESys::Net::PacketControl>();
        assert(respPack);

        if(boardID < 0) {
            bResult = false;
        }
        else if (_TesterItemArray->GetTesterItemIndex(boardID) >= 0) {
            /* 
                boardID가 이중으로 등록됨
                bResult = false 로 설정해야 한다.
            
            */
            bResult = false;
        }
        else {
            bResult = _TesterItemArray->AddNewTester(boardID, boardOS, cliSock);
        }

        respPack->SetCommand(reqPack->GetCommand());
        respPack->SetInt(0, boardID);
        respPack->SetInt(1, boardOS);
        respPack->SetResult(bResult);
        respPack->GenCRC();
        cliSock->Send(respPack);
    }



};
