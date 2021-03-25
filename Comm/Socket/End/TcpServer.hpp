#ifndef COMM_SOCKET_END_TCPSERVER_HPP__
#define COMM_SOCKET_END_TCPSERVER_HPP__

#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/Log.hpp>
#include <Comm/OAL/ThreadService.hpp>
#include <Comm/Socket/TCP/TCPServer.hpp>
#include <Comm/Utils/Queue.hpp>

namespace Comm {
    namespace Socket {
        namespace End {


            class TcpServer : public Comm::Base::Object {

            private:
                std::shared_ptr<Comm::Socket::TCP::Server> _SrvTcpSock;
                
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
                            
            public:
                int GetConnectedClientCount();
                void Broadcast(std::shared_ptr<Comm::Socket::NetPacket> pack);
            };

        }; // namespace End
    }; // namespace Socket
};// namespace Comm

#endif
