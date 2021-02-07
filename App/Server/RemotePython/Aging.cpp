#include "RemotePython.hpp"
#include <TED/Api.h>

using namespace TESys::Net;

namespace RemotePython {

    bool Aging::MeasureADC(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        bool bRet = false;
        //char desc[128];
        struct MeasureADCResult adcResult;

        bRet = TedAgingMeasureADC(&adcResult);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, sizeof(adcResult));
        sendPack->SetData((const unsigned char*)&adcResult, sizeof(adcResult));
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }

  
    bool Aging::SetCurJobInfo(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        bool bRet = false;
        int jobID, scIdx, scCnt;
        int status;

        jobID = rcvPack->GetInt(0);
        status = rcvPack->GetInt(1);
        scIdx = rcvPack->GetInt(2);
        scCnt = rcvPack->GetInt(3);

        int descByteSize = rcvPack->GetInt(4);
        char* desc = new char[descByteSize + 16];
        assert(desc);
        rcvPack->GetData((unsigned char*)desc, descByteSize);
        desc[descByteSize] = '\0';

        bRet = TedAgingSetCurJobInfo(jobID, status, scIdx, scCnt, desc);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        delete[] desc;
#endif
        return true;
    }

    bool Aging::SetCurSCInfo(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        bool bRet = false;
        int scID, tcIdx, tcCnt;
        int status;

        scID = rcvPack->GetInt(0);
        status = rcvPack->GetInt(1);
        tcIdx = rcvPack->GetInt(2);
        tcCnt = rcvPack->GetInt(3);

        int descByteSize = rcvPack->GetInt(4);
        char* desc = new char[descByteSize + 16];
        assert(desc);
        rcvPack->GetData((unsigned char*)desc, descByteSize);
        desc[descByteSize] = '\0';

        bRet = TedAgingSetCurSCInfo(scID, status, tcIdx, tcCnt, desc);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        delete[] desc;

#endif
        return true;
    }

    bool Aging::SetCurTCInfo(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        bool bRet = false;
        int tcID, tcStepIdx, tcStepCnt;
        int status;

        tcID = rcvPack->GetInt(0);
        status = rcvPack->GetInt(1);
        tcStepIdx = rcvPack->GetInt(2);
        tcStepCnt = rcvPack->GetInt(3);

        int descByteSize = rcvPack->GetInt(4);
        char* desc = new char[descByteSize + 16];
        assert(desc);
        rcvPack->GetData((unsigned char*)desc, descByteSize);
        desc[descByteSize] = '\0';

        bRet = TedAgingSetCurTCInfo(tcID, status, tcStepIdx, tcStepCnt, desc);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        delete[] desc;
#endif
        return true;
    }

    bool Aging::SetCurTCStepInfo(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        bool bRet = false;
        int tcStepID;
        int status;

        tcStepID = rcvPack->GetInt(0);
        status = rcvPack->GetInt(1);

        int descByteSize = rcvPack->GetInt(2);
        char* desc = new char[descByteSize + 16];
        assert(desc);
        rcvPack->GetData((unsigned char*)desc, descByteSize);
        desc[descByteSize] = '\0';
        
        bRet = TedAgingSetCurTCStepInfo(tcStepID, status, desc);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        delete[] desc;
#endif
        return true;
    }


};