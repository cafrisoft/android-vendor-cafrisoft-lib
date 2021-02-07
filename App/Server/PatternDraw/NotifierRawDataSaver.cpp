#include "Notifier.hpp"
#include <TESys/Property/Hub.hpp>
#include <TESys/Property/Net.hpp>

namespace TESysDataAcq {

    Notifier::RawDataSaver::RawDataSaver(Notifier* notifier) :
    
        _Notifier(notifier)
    {
        //Data Inst Create
        _DB = TESys::Data::DataAcqDB::CreateObject(TESys::Data::DataAcqDB::ID::Raw);
        assert(_DB);

        //Packet Queue¡íy¨ù¨¬
        _PacketQueue = std::make_shared<Comm::Utils::SyncQueue<std::shared_ptr<TESys::Net::PacketDataAcq>>>();
        assert(_PacketQueue);
        CLOGI("[Notifier::RawDataSaver] PacketQueue Create ... OK");
                
        //ThreadService Start
        _ThreadService = std::make_shared<Comm::OAL::ThreadService>(this);
        assert(_ThreadService);
    }

    bool Notifier::RawDataSaver::BroadCast(std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack) {
    
        _PacketQueue->Push(notifyPack);
        return true;
    }

        
    void Notifier::RawDataSaver::Service() {
    
        std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack = _PacketQueue->Pop();
        if (notifyPack != NULL) {

            int packByteSize = notifyPack->GetByteSize();
            notifyPack->GetNetPacketData(_PacketRawData);

            _DB->SavePacket(_PacketRawData, packByteSize);
    
        }
    }

    void Notifier::RawDataSaver::WaitForNextService() {
    
    }

    bool Notifier::RawDataSaver::IsServiceRun() {
        return true;
    }

    
    
    
};
