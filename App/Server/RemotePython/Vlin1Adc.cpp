#include "RemotePython.hpp"

using namespace TESys::Net;

namespace RemotePython {

    bool Vlin1Adc::SetSamples(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int value;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        value = rcvPack->GetInt(1);
        bRet = TedVlin1AdcSetSamples(dutIdx, value);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, value);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool Vlin1Adc::SetInterval(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
      
#if 0
        int value;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        value = rcvPack->GetInt(1);
        bRet = TedVlin1AdcSetInterval(dutIdx, value);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, value);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool Vlin1Adc::SetChannelOn(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int chIdx;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        chIdx = rcvPack->GetInt(1);
        bRet = TedVlin1AdcSetChannelOn(dutIdx, chIdx);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, chIdx);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool Vlin1Adc::SetChannelOff(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
      
#if 0
        int chIdx;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        chIdx = rcvPack->GetInt(1);
        bRet = TedVlin1AdcSetChannelOff(dutIdx, chIdx);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, chIdx);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool Vlin1Adc::SetMode(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
      
#if 0
        int value;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        value = rcvPack->GetInt(1);
        bRet = TedVlin1AdcSetMode(dutIdx, value);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, value);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }


    bool Vlin1Adc::GetVoltage(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
      
#if 0
        int chIdx;
        int voltage;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        chIdx = rcvPack->GetInt(1);
        bRet = TedVlin1AdcGetVoltage(dutIdx, chIdx, &voltage);

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

    bool Vlin1Adc::GetVoltageVLIN1(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int voltage;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        bRet = TedVlin1AdcGetVoltageVLIN1(dutIdx, &voltage);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, voltage);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif

        return true;
    }

    bool Vlin1Adc::GetVoltageVBAT(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int voltage;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        bRet = TedVlin1AdcGetVoltageVBAT(dutIdx, &voltage);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, voltage);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif

        return true;
    }

    bool Vlin1Adc::GetVoltageELVDD(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int voltage;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        bRet = TedVlin1AdcGetVoltageELVDD(dutIdx, &voltage);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, voltage);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif

        return true;
    }

    bool Vlin1Adc::GetCurrent(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int chIdx;
        int current;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        chIdx = rcvPack->GetInt(1);
        bRet = TedVlin1AdcGetCurrent(dutIdx, chIdx, &current);

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

    bool Vlin1Adc::GetCurrentVLIN1(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
      
#if 0
        int current;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        bRet = TedVlin1AdcGetCurrentVLIN1(dutIdx, &current);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, current);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif

        return true;
    }

    bool Vlin1Adc::GetCurrentVBAT(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int current;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        bRet = TedVlin1AdcGetCurrentVBAT(dutIdx, &current);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, current);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool Vlin1Adc::GetCurrentELVDD(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {
        
#if 0
        int current;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        bRet = TedVlin1AdcGetCurrentELVDD(dutIdx, &current);

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

