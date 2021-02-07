#ifndef CONTROLHUB_NOTIFIER_HPP__
#define CONTROLHUB_NOTIFIER_HPP__

#include "AppDefine.h"

namespace TESysControlHub {

    class Notifier {
    
        CLASS_SINGLETON_PATTERN_DECLARE(Notifier);

    private:
        class Operator : public Comm::OAL::IThreadService {
        private:    
            Notifier* _Notifier;
            std::shared_ptr<Socket::TCP::Server> _SrvTcpSock;
            std::shared_ptr<Comm::Utils::SyncQueue<std::shared_ptr<TESys::Net::PacketControl>>> _PacketQueue;
            std::shared_ptr<OAL::ThreadService> _ThreadService;
            bool _IsServiceRun;

        public:
            Operator(Notifier* notifier);
            virtual ~Operator();

        private:
            static void CallbackAcceptStub(void* arg, std::shared_ptr<Socket::TCP::Client> client);
            static void CallbackReceiveStub(void* arg, std::shared_ptr<Socket::TCP::Client> client, const unsigned char* data, int dataSize);
            static void CallbackCloseStub(void* arg, std::shared_ptr<Socket::TCP::Client> client);

            void CallbackAccept(std::shared_ptr<Socket::TCP::Client> client);
            void CallbackReceive(std::shared_ptr<Socket::TCP::Client> client, const unsigned char* data, int dataSize);
            void CallbackClose(std::shared_ptr<Socket::TCP::Client> client);

        private:
            virtual void Service();
            virtual void WaitForNextService();
            virtual bool IsServiceRun();

        public:
            bool BroadCast(std::shared_ptr<TESys::Net::PacketControl> notifyPack);
        };

        class Tester : public Comm::OAL::IThreadService {
        private:
            Notifier* _Notifier;
            std::shared_ptr<Socket::UDP::Server> _SrvUdpSock;
            unsigned char _RcvRawData[4096];
            std::shared_ptr<OAL::ThreadService> _ThreadService;
            bool _IsServiceRun;
            
            unsigned int _StartMonitorTick;
            unsigned int _BeforeMonitorTick;
            int _RcvPacketByteSizePerSec;
            int _N_THO_BroadCast_PacketByteSizePerSec;

        public:
            Tester(Notifier* notifier);
            virtual ~Tester();

        private:
            virtual void Service();
            virtual void WaitForNextService();
            virtual bool IsServiceRun();
        };

    private:
        std::shared_ptr<Operator> _Operator;
        std::shared_ptr<Tester> _Tester;

    public:
        Notifier();

    private:
        std::shared_ptr<Operator> GetOperator();
        std::shared_ptr<Tester> GetTester();

    public:
        //void SendTesterConnect(int id); //주어진 ID의 Tester가 접속되었음을 알린다.
        //void SendTesterDisconnect(int id);
        //void SendTesterHubIDVector(std::vector<int> vecHubID);

        bool BoardCastToOperator(std::shared_ptr<TESys::Net::PacketControl> notifyPack);
    };

};

#endif

