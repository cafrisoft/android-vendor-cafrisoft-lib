#define CLOG_TAG SYSLOG_NAME
#include "Receiver.hpp"
#include <TESys/Property/Hub.hpp>
#include <TESys/Property/Net.hpp>

namespace TESysDBRawData {

    Receiver::ExportCSV::ExportCSV(Receiver* notifier) :
    
        _Receiver(notifier)
    {
        //alloc PyCollection
        _PyColl = std::make_shared<TESys::Data::Aging::PyCollection>();
        assert(_PyColl);

        //Packet Queu Create
        _PacketQueue = std::make_shared<Comm::Utils::SyncQueue<std::shared_ptr<TESys::Net::PacketDataAcq>>>();
        assert(_PacketQueue);
        CLOGI("[Receiver::ExportCSV] PacketQueue Create ... OK");
                

        //ThreadService Start
        _ThreadService = std::make_shared<Comm::OAL::ThreadService>(this);
        assert(_ThreadService);
    }

    bool Receiver::ExportCSV::BroadCast(std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack) {
    
        _PacketQueue->Push(notifyPack);
        return true;
    }
        
    void Receiver::ExportCSV::Service() {
    
        std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack = _PacketQueue->Pop();
        if (rcvPack != NULL) {
           
            TESys::Net::Command::Aging  cmd = rcvPack->GetCommand();
            PRINTF("cmd=%d %s \n", cmd, TESys::Net::Command::CmdToString((int)cmd).c_str());

            _PyColl->LoadPacket(rcvPack, true /*isDbgExport*/);
        }
    }

    void Receiver::ExportCSV::WaitForNextService() {
    
    }

    bool Receiver::ExportCSV::IsServiceRun() {
        return true;
    }

    
    
};
