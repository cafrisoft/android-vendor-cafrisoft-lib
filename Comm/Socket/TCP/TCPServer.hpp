#ifndef COMM_SOCKET_TCP_SERVER_HPP__
#define COMM_SOCKET_TCP_SERVER_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/Socket/TCP/TCPClient.hpp>
#include <Comm/OAL/HeaderFiles.hpp>
#include <Comm/Utils/IntegerCount.hpp>


namespace Comm {
    namespace Socket {
        namespace TCP {

            typedef void (*TCPServerAcceptCallBackStub)(void* arg, std::shared_ptr<Client> client);
            typedef void (*TCPServerReceiveCallBackStub)(void* arg, std::shared_ptr<Client> client, const unsigned char* data, int dataSize);
            typedef void (*TCPServerCloseCallBackStub)(void* arg, std::shared_ptr<Client> client);

            class Server : public Base::Object {

            public:
                struct CreateConfig {
                    int _PortNum;
                    int _ReceiveBufSize;
                    int _MaxClientCount;
                    TCPServerAcceptCallBackStub _AcceptFunc;
                    TCPServerReceiveCallBackStub _ReceiveFunc;
                    TCPServerCloseCallBackStub _CloseFunc;
                    void* arg;
                };

                static const int _CliSockID_BroadCast = 0xFFFF;
                static const int _CliSockID_Invalid = -1;

            public:
                static std::shared_ptr<Server> CreateObject(struct CreateConfig cfg);
            
            private:
                std::shared_ptr<Comm::OAL::CriticalSection> _Cs_CliSock;


                struct CreateConfig _CreateConfig;
                long long _ServerStartTick;

                //Log
                std::shared_ptr<OAL::Timer> _LogTimer;
                Utils::IntegerCount _ReceivedDataCount;

                //
                bool _IsSelectThreadRun;
                std::shared_ptr<OAL::Thread> _SelectThread;

                std::vector<std::shared_ptr<Client>> _ClientVector;

            protected:
                Server(struct CreateConfig cfg);
                virtual ~Server();

            protected:
                void SelectAcceptCallback(std::shared_ptr<Client> client);
                void SelectReceiveCallback(std::shared_ptr<Client> client, const unsigned char* data, int dataSize);
                void SelectCloseCallback(std::shared_ptr<Client> client);

            public:
                virtual bool Open() = 0;
                virtual bool Close() = 0;

            public:
                virtual void Select() = 0;
                virtual void SelectLoop(bool isInternalThreadRun=false);

            private:
                static void SelectServiceStub(void* arg);
                void SelectService();

            public:
                void LogStart();
                void LogStop();
            protected:
                virtual void EventTimerCallbackLog();

            public:
                int GetPortNum();
                int GetReceiveBufByteSize();
                int GetMaxClientCount();
                int GetConnectedClientCount();
                std::vector<int> GetConnectedHubIDVector();

                virtual bool Broadcast(const unsigned char* data, int dataSize);
                virtual bool Broadcast(std::shared_ptr<NetPacket> pack);
                virtual bool Send(int cliSockID, const unsigned char* data, int dataSize);
                virtual bool Send(int cliSockID, std::shared_ptr<NetPacket> pack);
            };

        }; //namespace TCP
    }; //namespace Socket {
}; // namespace Comm {

#endif //COMM_DATAEX_PRODUCER_HPP__