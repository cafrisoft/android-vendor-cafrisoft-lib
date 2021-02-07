#include "RemotePython.hpp"
#include <TED/Api.h>

using namespace TESys::Net;

namespace RemotePython {

    bool DD::set_fb0_blank(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        int value;
        bool bRet = false;

        value = rcvPack->GetInt(0);

        bRet = TedDD_set_fb0_blank(value);
        
        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, value);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool DD::set_dsim_manual_ctrl(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        int value;
        bool bRet = false;

        value = rcvPack->GetInt(0);

        bRet = TedDD_set_dsim_manual_ctrl(value);
        
        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, value);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

};