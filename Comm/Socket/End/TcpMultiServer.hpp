#ifndef COMM_SOCKET_END_TCPMULTISERVER_HPP__
#define COMM_SOCKET_END_TCPMULTISERVER_HPP__

#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/Log.hpp>
#include <Comm/OAL/ThreadService.hpp>
#include <Comm/Socket/TCP/TCPServer.hpp>
#include <Comm/Utils/Queue.hpp>

namespace Comm {
    namespace Socket {
        namespace End {


            class TcpMultiServer : public Comm::Base::Object {

            public:
                struct SocketProperty {
                    int _Idx;
                    int _TcpPort;
                    int _PacketByteSize;
                    int _MaxClientSize;
                };

            private:
                struct SockArg {
                    TcpMultiServer* _This;
                    int _SockIdx;
                    struct SocketProperty _SockProp;
                };

            private:
                int _SrvSockCount;
                std::shared_ptr<Comm::Socket::TCP::Server> *_SrvTcpSock;
                struct SockArg* _SockArg;
                
            private:
                static void CallbackAcceptFromCliSockStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> cliSock);
                static void CallbackReceiveFromCliSockStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize);
                static void CallbackCloseFromCliSockStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> cliSock);

            protected:
                virtual void CallbackAcceptFromCliSock(const struct SocketProperty* pSockProp, std::shared_ptr<Comm::Socket::TCP::Client> cliSock);
                virtual void CallbackReceiveFromCliSock(const struct SocketProperty* pSockProp, std::shared_ptr<Comm::Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize) = 0;
                virtual void CallbackCloseFromCliSock(const struct SocketProperty* pSockProp, std::shared_ptr<Comm::Socket::TCP::Client> cliSock);

            public:
                TcpMultiServer(int srvSockCount, struct SocketProperty* propArr);
                virtual ~TcpMultiServer();
                            
            public:
                int GetConnectedClientCount(int isock);
                void Broadcast(int isock, std::shared_ptr<Comm::Socket::NetPacket> pack);
            };

        }; // namespace End
    }; // namespace Socket
};// namespace Comm

#endif
