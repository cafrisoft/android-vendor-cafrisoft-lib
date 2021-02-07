#define CLOG_TAG SYSLOG_NAME
#include "Receiver.hpp"
#include <TESys/Property/Hub.hpp>
#include <TESys/Property/Net.hpp>

namespace TESysDBRawData {

    Receiver::RawDataSaver::RawDataSaver(Receiver* notifier) :
    
        _Receiver(notifier)
    {
        //Data Inst Create
        _DB = TESys::Data::DataAcqDB::CreateObject(TESys::Data::DataAcqDB::ID::Raw);
        assert(_DB);


        //Packet Queu Create
        _PacketQueue = std::make_shared<Comm::Utils::SyncQueue<std::shared_ptr<TESys::Net::PacketDataAcq>>>();
        assert(_PacketQueue);
        CLOGI("[Receiver::RawDataSaver] PacketQueue Create ... OK");
                

        //ThreadService Start
        _ThreadService = std::make_shared<Comm::OAL::ThreadService>(this);
        assert(_ThreadService);
    }

    bool Receiver::RawDataSaver::BroadCast(std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack) {
    
        _PacketQueue->Push(notifyPack);
        return true;
    }

    
    void Receiver::RawDataSaver::Service() {
    
        std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack = _PacketQueue->Pop();
        if (rcvPack != NULL) {

            int packByteSize = rcvPack->GetByteSize();
            rcvPack->GetNetPacketData(_PacketRawData);

            _DB->SaveBackupPacket(_PacketRawData, packByteSize);
        }
    }

    void Receiver::RawDataSaver::WaitForNextService() {
    
    }

    bool Receiver::RawDataSaver::IsServiceRun() {
        return true;
    }

    
    
    
};
