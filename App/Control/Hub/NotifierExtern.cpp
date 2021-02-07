#include "Notifier.hpp"

namespace TESysControlHub {
        
    bool Notifier::BoardCastToOperator(std::shared_ptr<TESys::Net::PacketControl> notifyPack) {
    
        return this->GetOperator()->BroadCast(notifyPack);
    }

#if 0
    //주어진 ID의 Tester가 접속되었음을 알린다.
    void Notifier::SendTesterConnect(int id) {
        std::shared_ptr<TESys::Net::PacketControl> sendPack = std::make_shared<TESys::Net::PacketControl>();
        sendPack->SetCommand(TESys::Net::Command::Control::Notify_TesterConnect);
        sendPack->SetInt(0, id);
        sendPack->GenCRC();
        this->GetOperator()->BroadCast(sendPack);
    }

    //주어진 ID의 Tester가 접속해제 되었음을 알린다.
    void Notifier::SendTesterDisconnect(int id) {
        std::shared_ptr<TESys::Net::PacketControl> sendPack = std::make_shared<TESys::Net::PacketControl>();
        sendPack->SetCommand(TESys::Net::Command::Control::Notify_TesterDisconnect);
        sendPack->SetInt(0, id);
        sendPack->GenCRC();
        this->GetOperator()->BroadCast(sendPack);
    }
#endif

#if 0
    void Notifier::SendTesterHubIDVector(std::vector<int> vecHubID) {
    
        int hubIDCount = (int)vecHubID.size();
        int packetHubMaxIDCount = TESys::Net::PacketControl::GetMaxHubIDCountInData();
        int remainhubIDCount = hubIDCount;
        int startIdx=0;
        int* hubIDArr = new int[packetHubMaxIDCount];
        assert(hubIDArr);

        CLOGD("hubIDCount=%d", hubIDCount);

        if (remainhubIDCount == 0) {
        
            std::shared_ptr<TESys::Net::PacketControl> sendPack = std::make_shared<TESys::Net::PacketControl>();
            sendPack->SetCommand(TESys::Net::Command::Control::Notify_GetConnectedTesterHubID);
            sendPack->SetInt(0, startIdx);
            sendPack->SetInt(1, remainhubIDCount);
            sendPack->GenCRC();
            this->GetOperator()->BroadCast(sendPack);
        }
        else {
            while (remainhubIDCount > 0) {

                int sendHubIDCount = remainhubIDCount;

                CLOGD("");

                if (sendHubIDCount > packetHubMaxIDCount) {
                    sendHubIDCount = packetHubMaxIDCount;
                }

                CLOGD("");

                for (int i = 0; i < sendHubIDCount; i++) {
                    hubIDArr[i] = vecHubID[startIdx + i];
                }

                std::shared_ptr<TESys::Net::PacketControl> sendPack = std::make_shared<TESys::Net::PacketControl>();
                sendPack->SetCommand(TESys::Net::Command::Control::Notify_GetConnectedTesterHubID);
                sendPack->SetInt(0, startIdx);
                sendPack->SetInt(1, sendHubIDCount);
                sendPack->SetData((const unsigned char*)hubIDArr, TESys::Net::PacketControl::GetTesterHubIDByteSize() * sendHubIDCount);
                sendPack->GenCRC();
                this->GetOperator()->BroadCast(sendPack);

                remainhubIDCount -= sendHubIDCount;
                startIdx += sendHubIDCount;
            }
        }

        delete[] hubIDArr;
    }
#endif

};
