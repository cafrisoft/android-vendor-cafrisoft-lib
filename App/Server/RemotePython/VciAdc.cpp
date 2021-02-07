#include "RemotePython.hpp"

using namespace TESys::Net;

namespace RemotePython {

    bool VciAdc::SetSamples(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int value;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        value = rcvPack->GetInt(1);
        bRet = TedVciAdcSetSamples(dutIdx, value);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, value);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool VciAdc::SetInterval(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
      
#if 0
        int value;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        value = rcvPack->GetInt(1);
        bRet = TedVciAdcSetInterval(dutIdx, value);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, value);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool VciAdc::SetChannelOn(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
      
#if 0
        int chIdx;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        chIdx = rcvPack->GetInt(1);
        bRet = TedVciAdcSetChannelOn(dutIdx, chIdx);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, chIdx);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool VciAdc::SetChannelOff(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
      
#if 0
        int chIdx;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        chIdx = rcvPack->GetInt(1);
        bRet = TedVciAdcSetChannelOff(dutIdx, chIdx);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, chIdx);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool VciAdc::SetMode(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
      
#if 0
        int value;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        value = rcvPack->GetInt(1);
        bRet = TedVciAdcSetMode(dutIdx, value);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, value);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }


    bool VciAdc::GetVoltage(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
      
#if 0
        int chIdx;
        int voltage;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        chIdx = rcvPack->GetInt(1);
        bRet = TedVciAdcGetVoltage(dutIdx, chIdx, &voltage);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, chIdx);
        sendPack->SetInt(1, voltage);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool VciAdc::GetVoltageVCI(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int voltage;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        bRet = TedVciAdcGetVoltageVCI(dutIdx, &voltage);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, voltage);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool VciAdc::GetVoltageVDDR(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int voltage;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        bRet = TedVciAdcGetVoltageVDDR(dutIdx, &voltage);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, voltage);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool VciAdc::GetVoltageVDDI(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int voltage;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        bRet = TedVciAdcGetVoltageVDDI(dutIdx, &voltage);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, voltage);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool VciAdc::GetCurrent(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int chIdx;
        int current;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        chIdx = rcvPack->GetInt(1);
        bRet = TedVciAdcGetCurrent(dutIdx, chIdx, &current);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, chIdx);
        sendPack->SetInt(1, current);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool VciAdc::GetCurrentVCI(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int current;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        bRet = TedVciAdcGetCurrentVCI(dutIdx, &current);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, current);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool VciAdc::GetCurrentVDDR(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int current;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        bRet = TedVciAdcGetCurrentVDDR(dutIdx, &current);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, current);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool VciAdc::GetCurrentVDDI(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int current;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        bRet = TedVciAdcGetCurrentVDDI(dutIdx, &current);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, current);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

}

