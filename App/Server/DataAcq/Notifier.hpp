#ifndef DATAACQ_NOTIFIER_HPP__
#define DATAACQ_NOTIFIER_HPP__

#include "AppDefine.h"

namespace TESysDataAcq {

    class Notifier {
    
        CLASS_SINGLETON_PATTERN_DECLARE(Notifier);

    private:
        class Exporter : public Comm::OAL::IThreadService {

        private:
            Notifier* _Notifier;
            std::shared_ptr<TESys::Data::DataAcqDB> _DB;
            std::shared_ptr<Comm::Utils::SyncQueue<std::shared_ptr<TESys::Net::PacketDataAcq>>> _PacketQueue;
            std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;
            unsigned char _PacketRawData[4096];

        public:
            Exporter(Notifier* notifier);

        private:
            virtual void Service();
            virtual void WaitForNextService();
            virtual bool IsServiceRun();

        public:
            bool BroadCast(std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack);
        };

        class RawDataSaver : public Comm::OAL::IThreadService {

        private:    
            Notifier* _Notifier;
            std::shared_ptr<TESys::Data::DataAcqDB> _DB;
            std::shared_ptr<Comm::Utils::SyncQueue<std::shared_ptr<TESys::Net::PacketDataAcq>>> _PacketQueue;
            std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;
            unsigned char _PacketRawData[4096];

        public:
            RawDataSaver(Notifier* notifier);
        
        private:
            virtual void Service();
            virtual void WaitForNextService();
            virtual bool IsServiceRun();

        public:
            bool BroadCast(std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack);
        };

        class TCPServer : public Comm::OAL::IThreadService {

        private:
            Notifier* _Notifier;
            std::shared_ptr<Comm::Socket::TCP::Server> _SrvTcpSock;
            std::shared_ptr<Comm::Utils::SyncQueue<std::shared_ptr<TESys::Net::PacketDataAcq>>> _PacketQueue;
            std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;

        public:
            TCPServer(Notifier* notifier);

        private:
            static void CallbackAcceptStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> client);
            static void CallbackReceiveStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> client, const unsigned char* data, int dataSize);
            static void CallbackCloseStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> client);

            void CallbackAccept(std::shared_ptr<Comm::Socket::TCP::Client> client);
            void CallbackReceive(std::shared_ptr<Comm::Socket::TCP::Client> client, const unsigned char* data, int dataSize);
            void CallbackClose(std::shared_ptr<Comm::Socket::TCP::Client> client);

        private:
            virtual void Service();
            virtual void WaitForNextService();
            virtual bool IsServiceRun();

        public:
            bool BroadCast(std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack);
        };
        class Tester : public Comm::OAL::IThreadService {
        private:
            Notifier* _Notifier;
            std::shared_ptr<Comm::Socket::UDP::Server> _SrvUdpSock;
            unsigned char _RcvRawData[4096];
            std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;
            
            unsigned int _StartMonitorTick;
            unsigned int _BeforeMonitorTick;
            int _RcvPacketByteSizePerSec;

        public:
            Tester(Notifier* notifier);

        private:
            virtual void Service();
            virtual void WaitForNextService();
            virtual bool IsServiceRun();
        };

    private:
        std::shared_ptr<TESys::Control::AgingMonitor> _AgingMonitor;
        std::shared_ptr<Exporter> _Exporter;
        std::shared_ptr<RawDataSaver> _RawDataSaver;
        std::shared_ptr<Tester> _Tester;
        std::shared_ptr<TCPServer> _TCPServer;

    public:
        Notifier();

    private:
        std::shared_ptr<TESys::Control::AgingMonitor> GetAgingMonitor();
        std::shared_ptr<Exporter> GetExporter();
        std::shared_ptr<RawDataSaver> GetRawDataSaver();
        std::shared_ptr<Tester> GetTester();
        std::shared_ptr<TCPServer> GetTCPServer();

    //public:
      //  bool BoardCastToRawDataSaver(std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack);
    };

};

#endif

