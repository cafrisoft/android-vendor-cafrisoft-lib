#include <Comm/Global/BuildOptions.h>
#define CLOG_TAG "SocketTossTcpServer"
#include <Comm/Socket/Toss/TcpServer.hpp>

namespace Comm {
    namespace Socket {
        namespace Toss {

            TcpServer::TcpServer(int tcpPort, int packByteSize, int maxCliSize) :
                _IsServiceRun(true)
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
                //CLOGI("[Commander/TcpServer TCPServerSocket Create ... OK (Port=%d)", _SrvTcpSock->GetPortNum());


                /*
                    PacketQueue Create
                */
                _BroadCastPacketQueue = std::make_shared<Comm::Utils::SyncQueue<PacketQueueData>>();
                assert(_BroadCastPacketQueue);

                /*
                    ThreadService Start
                */
                _ThreadService = std::make_shared<OAL::ThreadService>(this);
                assert(_ThreadService);
            }

            TcpServer::~TcpServer() {
            
                _IsServiceRun = false;

                PacketQueueData d(Comm::Socket::TCP::Server::_CliSockID_Invalid, NULL);
                _BroadCastPacketQueue->Push(d);
                _ThreadService.reset();

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

            bool TcpServer::IsServiceRun() {
                return _IsServiceRun;
            }

            void TcpServer::WaitForNextService() {

            }

            void TcpServer::Service() {

                PacketQueueData d = _BroadCastPacketQueue->Pop();

                if (d._CliSockID == Comm::Socket::TCP::Server::_CliSockID_BroadCast) {
                    if (d._NetPack) {
                        _SrvTcpSock->Broadcast(d._NetPack);
                    }
                }
                else if (d._CliSockID == Comm::Socket::TCP::Server::_CliSockID_Invalid) {
                    /*
                       Nothing to do
                    */
                }
                else {
                    if (d._NetPack) {
                        _SrvTcpSock->Send(d._CliSockID, d._NetPack);
                    }
                }

            }

            void TcpServer::BroadCast(std::shared_ptr<Comm::Socket::NetPacket> pack) {

                PacketQueueData d(Comm::Socket::TCP::Server::_CliSockID_BroadCast, pack);
                _BroadCastPacketQueue->Push(d);
            }

            void TcpServer::Post(int cliSockID, std::shared_ptr<Comm::Socket::NetPacket> pack) {
            
                PacketQueueData d(cliSockID, pack);
                _BroadCastPacketQueue->Push(d);
            }

            int TcpServer::GetConnectedClientCount() {
                return _SrvTcpSock->GetConnectedClientCount();
            }

        }; // namespace Toss  
    }; // namespace Socket
};// namespace Comm

