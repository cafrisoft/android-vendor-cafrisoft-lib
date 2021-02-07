#ifndef TESYSDBRAWDATA_RECEIVER_HPP__
#define TESYSDBRAWDATA_RECEIVER_HPP__

#include "AppDefine.h"
#include <TESys/Data/Aging/PyCollection.hpp>

namespace TESysDBRawData {

    class Receiver {
    
        CLASS_SINGLETON_PATTERN_DECLARE(Receiver);

    private:
        class RawDataSaver : public Comm::OAL::IThreadService {

        private:    
            Receiver* _Receiver;
            std::shared_ptr<TESys::Data::DataAcqDB> _DB;
            std::shared_ptr<Comm::Utils::SyncQueue<std::shared_ptr<TESys::Net::PacketDataAcq>>> _PacketQueue;
            std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;
            unsigned char _PacketRawData[4096];

        public:
            RawDataSaver(Receiver* notifier);

        
        private:
            virtual void Service();
            virtual void WaitForNextService();
            virtual bool IsServiceRun();

        public:
            bool BroadCast(std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack);
        };

        class ExportCSV : public Comm::OAL::IThreadService {

        private:
            Receiver* _Receiver;
            std::shared_ptr<Comm::Utils::SyncQueue<std::shared_ptr<TESys::Net::PacketDataAcq>>> _PacketQueue;
            std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;
            std::shared_ptr<TESys::Data::Aging::PyCollection> _PyColl;

        public:
            ExportCSV(Receiver* notifier);

        private:
            virtual void Service();
            virtual void WaitForNextService();
            virtual bool IsServiceRun();

        public:
            bool BroadCast(std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack);
        };

        class DataAcq : public Comm::OAL::IThreadService {
        private:
            Receiver* _Receiver;
            std::shared_ptr<Comm::Socket::TCP::Client> _CliSock;
            unsigned char _RcvRawData[4096];
            std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;
            
            unsigned int _StartMonitorTick;
            unsigned int _BeforeMonitorTick;
            int _RcvPacketByteSizePerSec;

        public:
            DataAcq(Receiver* notifier);

        private:
            virtual void Service();
            virtual void WaitForNextService();
            virtual bool IsServiceRun();
        };

    private:
        std::shared_ptr<RawDataSaver> _RawDataSaver;
        std::shared_ptr<ExportCSV> _ExportCSV;
        std::shared_ptr<DataAcq> _DataAcq;

    public:
        Receiver();

    private:
        std::shared_ptr<RawDataSaver> GetRawDataSaver();
        std::shared_ptr<ExportCSV> GetExportCSV();
        std::shared_ptr<DataAcq> GetDataAcq();

    public:
        //bool BoardCastToRawDataSaver(std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack);
    };

};

#endif

