#include "RemotePython.hpp"

using namespace TESys::Net;

namespace RemotePython {

    
    bool RegAdc::SetInConfig(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        int chIdx;
        int value;
        bool bRet = false;

        int dutIdx = rcvPack->GetInt(0);
        chIdx = rcvPack->GetInt(1);
        value = rcvPack->GetInt(2);
        bRet = TedRegAdcSetInConfig(dutIdx, chIdx, value);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, chIdx);
        sendPack->SetInt(1, value);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

    bool RegAdc::GetChannelCount(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        int channelCount;

        int dutIdx = rcvPack->GetInt(0);
        channelCount = TedRegAdcGetChannelCount(dutIdx);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, channelCount);
        sendPack->SetResult(true);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif

        return true;
    }

    bool RegAdc::GetVoltage(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        int chIdx;
        int voltage;
        
        int dutIdx = rcvPack->GetInt(0);
        chIdx = rcvPack->GetInt(1);
        voltage = TedRegAdcGetVoltage(dutIdx, chIdx);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, chIdx);
        sendPack->SetInt(1, voltage);
        sendPack->SetResult(true);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif

        return true;
    }

    bool RegAdc::GetAllVoltage(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        int channelCount;// = TedRegAdcGetChannelCount();
        int* voltageArr;// = new int[channelCount];
        
        bool bRet = false;
        int dataByteSize;

        int dutIdx = rcvPack->GetInt(0);

        channelCount = TedRegAdcGetChannelCount(dutIdx);
        voltageArr = new int[channelCount];
        assert(voltageArr);


        bRet = TedRegAdcGetAllVoltage(dutIdx, voltageArr);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());

        dataByteSize = sizeof(int) * channelCount;
        sendPack->SetInt(0, channelCount);
        sendPack->SetInt(1, dataByteSize);
        sendPack->SetData((const unsigned char*)voltageArr, dataByteSize);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        delete[] voltageArr;
#endif
        return true;
    }

}

