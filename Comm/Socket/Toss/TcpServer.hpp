#ifndef COMM_SOCKET_TOSS_TCPSERVER_HPP__
#define COMM_SOCKET_TOSS_TCPSERVER_HPP__

#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/Log.hpp>
#include <Comm/OAL/ThreadService.hpp>
#include <Comm/Socket/TCP/TCPServer.hpp>
#include <Comm/Utils/Queue.hpp>

namespace Comm {
    namespace Socket {
        namespace Toss {


            class TcpServer : public Comm::OAL::IThreadService {

            private:
                class PacketQueueData {
                public:
                    int _CliSockID;
                    std::shared_ptr<Comm::Socket::NetPacket> _NetPack;

                public:
                    PacketQueueData() :
                        _CliSockID(Comm::Socket::TCP::Server::_CliSockID_Invalid), _NetPack(NULL) {

                    }

                    PacketQueueData(int cliSockID, std::shared_ptr<Comm::Socket::NetPacket> pack) :
                        _CliSockID(cliSockID), _NetPack(pack) {
                    
                    }
                };

            private:
                std::shared_ptr<Comm::Socket::TCP::Server> _SrvTcpSock;
                std::shared_ptr<Comm::Utils::SyncQueue<PacketQueueData>> _BroadCastPacketQueue;
                std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;
                bool _IsServiceRun;

            private:
                static void CallbackAcceptFromCliSockStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> cliSock);
                static void CallbackReceiveFromCliSockStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize);
                static void CallbackCloseFromCliSockStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> cliSock);

            protected:
                virtual void CallbackAcceptFromCliSock(std::shared_ptr<Comm::Socket::TCP::Client> cliSock);
                virtual void CallbackReceiveFromCliSock(std::shared_ptr<Comm::Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize) = 0;
                virtual void CallbackCloseFromCliSock(std::shared_ptr<Comm::Socket::TCP::Client> cliSock);

            public:
                TcpServer(int tcpPort, int packByteSize, int maxCliSize);
                virtual ~TcpServer();

            private:
                virtual bool IsServiceRun();
                virtual void WaitForNextService();
                virtual void Service();

            public:
                void BroadCast(std::shared_ptr<Comm::Socket::NetPacket> pack);
                void Post(int cliSockID, std::shared_ptr<Comm::Socket::NetPacket> pack);
                int GetConnectedClientCount();
            };

        }; // namespace Toss  
    }; // namespace Socket
};// namespace Comm

#endif
