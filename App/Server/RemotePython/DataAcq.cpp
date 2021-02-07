#include "RemotePython.hpp"
#include <TED/Api.h>

using namespace TESys::Net;

namespace RemotePython {

    bool DataAcq::MeasureADC(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

        bool bRet = false;
        int jobID, scID, tcID, tcStep;
        char desc[128];
        struct MeasureResult adcResult;

        jobID = rcvPack->GetInt(0);
        scID = rcvPack->GetInt(1);
        tcID = rcvPack->GetInt(2);
        tcStep = rcvPack->GetInt(3);
        
        rcvPack->GetData((unsigned char*)desc, sizeof(desc));

        bRet = TedDataAcqMeasureADC(jobID, scID, tcID, tcStep, desc, &adcResult);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, sizeof(adcResult));
        sendPack->SetData((const unsigned char*)&adcResult, sizeof(adcResult));
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        return true;
    }

    

};