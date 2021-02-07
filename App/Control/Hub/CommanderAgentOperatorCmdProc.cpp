#include "CommanderAgent.hpp"
#include <TESys/Property/FileSync.hpp>
#include <TESys/Net/PacketControl.hpp>
#

namespace TESysControlHub {

    bool CommanderAgent::Operator::CmdProc_C_OH_HO_GetConnectedTesterCount(std::shared_ptr<Socket::TCP::Client> cliSock, std::shared_ptr<TESys::Net::PacketControl> reqPack) {

        bool bRet = false;
            
        std::shared_ptr<TESys::Net::PacketControl> respPack = std::make_shared<TESys::Net::PacketControl>();
        respPack->SetCommand(reqPack->GetCommand());
        respPack->SetInt(0, _CommanderAgent->GetTester()->GetConnectedTesterCount());
        respPack->SetResult(true);
        respPack->GenCRC();

        cliSock->Send(respPack);

        return true;
    }

    bool CommanderAgent::Operator::CmdProc_C_OH_RunHubCalCRC(std::shared_ptr<Socket::TCP::Client> cliSock, std::shared_ptr<TESys::Net::PacketControl> reqPack) {

        std::string cmd = TESys::Property::Hub::FtpServer::GetHubCalCRCRunCommand();

        CLOGD("[Hub::CommanderAgent::Operator::CmdProc_C_OH_RunHubCalCRC] cmd=%s", cmd.c_str());
        OAL::System::ExecuteProcess(cmd, true);

        return true;
    }

#if 0
    bool CommanderAgent::Operator::CmdProc_C_OH_HO_GetFileCRC(std::shared_ptr<Socket::TCP::Client> cliSock, std::shared_ptr<TESys::Net::PacketControl> reqPack) {
    
        bool bRet = false;

        TESys::Property::FileSync::Ftp::DirID dirID = (TESys::Property::FileSync::Ftp::DirID)reqPack->GetInt(0);
        int fileNameByteSize = reqPack->GetInt(1);
        std::string strFileName = reqPack->GetString(fileNameByteSize);

        //TESys::Property::FileSync::Ftp
        
        std::shared_ptr<TESys::Net::PacketControl> respPack = std::make_shared<TESys::Net::PacketControl>();
        respPack->SetCommand(reqPack->GetCommand());

        respPack->SetInt(0, _CommanderAgent->GetTester()->GetConnectedTesterCount());
        respPack->SetResult(true);
        respPack->GenCRC();

        cliSock->Send(respPack);

        return true;
    }
#endif

    
};