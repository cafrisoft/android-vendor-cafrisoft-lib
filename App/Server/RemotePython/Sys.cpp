#include "RemotePython.hpp"
#include <TED/Api.h>

using namespace TESys::Net;

namespace RemotePython {

    bool Sys::Delay(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

        int delayMileSec;
        bool bRet = false;

        delayMileSec = rcvPack->GetInt(0);
        
        bRet = true; 
        CLOGI("DELAY=%d\t%s", delayMileSec, Debug::FuncNameStack().c_str());
        Debug::ExecelTxtPrint("DELAY=%d", delayMileSec);
        
        OAL::Thread::Sleep(delayMileSec);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, delayMileSec);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        return true;
    }

    bool Sys::SetBoardID(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

        int boardID;
        bool bRet = false;

        boardID = rcvPack->GetInt(0);

        bRet = TedSysSetBoardID(boardID);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, boardID);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        return true;
    }

    bool Sys::NotifyPyStart(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if  0
        bool bRet = false;

        
        bRet = TedSysNotifyPyStart();

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        return true;
#else

        return false;
#endif
    }

    bool Sys::NotifyPyStop(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        bool bRet = false;


        bRet = TedSysNotifyPyStop();

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        return true;
#else

        return false;
#endif
    }
};