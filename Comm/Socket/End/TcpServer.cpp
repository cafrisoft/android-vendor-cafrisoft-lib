#include <Comm/Global/BuildOptions.h>
#define CLOG_TAG "SocketEndTcpServer"
#include <Comm/Socket/End/TcpServer.hpp>

namespace Comm {
    namespace Socket {
        namespace End {

            TcpServer::TcpServer(int tcpPort, int packByteSize, int maxCliSize) 
            {

                /*
                    Commander/TcpServer TCP Server  Socket
                */
                struct Comm::Socket::TCP::Server::CreateConfig  createConfig = {
                    tcpPort /* server port*/,
                    packByteSize /*packet byte size*/,
                    maxCliSize /*max client count*/,
                    CallbackAcceptFromCliSockStub,
                    CallbackReceiveFromCliSockStub,
                    CallbackCloseFromCliSockStub,
                    this
                };

                _SrvTcpSock = Comm::Socket::TCP::Server::CreateObject(createConfig);
                assert(_SrvTcpSock);
                _SrvTcpSock->SelectLoop(true);
                //CLOGI("[Commander/TcpServer TcpServerSocket Create ... OK (Port=%d)", _SrvTcpSock->GetPortNum());
            }

            TcpServer::~TcpServer() {
            
                //delete socket array
                _SrvTcpSock.reset();
            }


            void TcpServer::CallbackAcceptFromCliSockStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> cliSock) { ((TcpServer*)arg)->CallbackAcceptFromCliSock(cliSock); }
            void TcpServer::CallbackReceiveFromCliSockStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize) { ((TcpServer*)arg)->CallbackReceiveFromCliSock(cliSock, data, dataSize); }
            void TcpServer::CallbackCloseFromCliSockStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> cliSock) { ((TcpServer*)arg)->CallbackCloseFromCliSock(cliSock); }

            void TcpServer::CallbackAcceptFromCliSock(std::shared_ptr<Comm::Socket::TCP::Client> cliSock) {

            }

#if 0
            void TcpServer::CallbackReceiveFromCliSock(std::shared_ptr<Comm::Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize) {

                if (dataSize == Stock::Net::PacketCtrl::GetFixedPacketByteSize()) {
                    std::shared_ptr<Stock::Net::PacketCtrl> packCtrl = std::make_shared<Stock::Net::PacketCtrlNone>(data);
                    assert(packCtrl);
                    _Agent->GetProvider()->BroadCast(packCtrl);
                }
            }
#endif

            void TcpServer::CallbackCloseFromCliSock(std::shared_ptr<Comm::Socket::TCP::Client> cliSock) {

            }
            
            int TcpServer::GetConnectedClientCount() {
                
                return _SrvTcpSock->GetConnectedClientCount();
            }

            void TcpServer::Broadcast(std::shared_ptr<Comm::Socket::NetPacket> pack) {

                _SrvTcpSock->Broadcast(pack);
            }

        }; // namespace End
    }; // namespace Socket
};// namespace Comm

