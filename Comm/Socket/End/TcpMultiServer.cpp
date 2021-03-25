#define CLOG_TAG "SocketTossTcpMultiServer"
#include <Comm/Socket/End/TcpMultiServer.hpp>

namespace Comm {
    namespace Socket {
        namespace End {

            TcpMultiServer::TcpMultiServer(int srvSockCount, struct SocketProperty* propArr) :
                _SrvSockCount(srvSockCount)
            {

                _SockArg = new struct SockArg[_SrvSockCount];
                assert(_SockArg);
                for (int isock = 0; isock < _SrvSockCount; isock++) {

                    struct SocketProperty* pSockProp = &propArr[isock];

                    assert(pSockProp->_Idx == isock);

                    _SockArg[isock]._This = this;
                    _SockArg[isock]._SockIdx = pSockProp->_Idx;
                    memcpy(&_SockArg[isock]._SockProp, pSockProp, sizeof(struct SocketProperty));
                }


                _SrvTcpSock = new std::shared_ptr<Comm::Socket::TCP::Server>[_SrvSockCount];
                assert(_SrvTcpSock);
                for (int isock = 0; isock < _SrvSockCount; isock++) {


                    /*
                        Commander/TcpMultiServer TCP Server  Socket
                    */
                    struct Comm::Socket::TCP::Server::CreateConfig  createConfig = {
                        propArr[isock]._TcpPort /* server port*/,
                        propArr[isock]._PacketByteSize /*packet byte size*/,
                        propArr[isock]._MaxClientSize /*max client count*/,
                        CallbackAcceptFromCliSockStub,
                        CallbackReceiveFromCliSockStub,
                        CallbackCloseFromCliSockStub,
                        & _SockArg[isock]
                    };

                    _SrvTcpSock[isock] = Comm::Socket::TCP::Server::CreateObject(createConfig);
                    assert(_SrvTcpSock[isock]);
                    _SrvTcpSock[isock]->SelectLoop(true);
                    //CLOGI("[Commander/TcpMultiServer TcpMultiServerSocket Create ... OK (Port=%d)", _SrvTcpSock->GetPortNum());

                }
                
            }

            TcpMultiServer::~TcpMultiServer() {
            
                //delete socket array
                for (int isock = 0; isock < _SrvSockCount; isock++) {
                    _SrvTcpSock[isock].reset();
                }
                delete[] _SrvTcpSock;

                //delete sock arg array
                delete[] _SockArg;

            }


            void TcpMultiServer::CallbackAcceptFromCliSockStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> cliSock) { ((struct SockArg*)arg)->_This->CallbackAcceptFromCliSock(&((struct SockArg*)arg)->_SockProp, cliSock); }
            void TcpMultiServer::CallbackReceiveFromCliSockStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize) { ((struct SockArg*)arg)->_This->CallbackReceiveFromCliSock(&((struct SockArg*)arg)->_SockProp, cliSock, data, dataSize); }
            void TcpMultiServer::CallbackCloseFromCliSockStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> cliSock) { ((struct SockArg*)arg)->_This->CallbackCloseFromCliSock(&((struct SockArg*)arg)->_SockProp, cliSock); }

            void TcpMultiServer::CallbackAcceptFromCliSock(const struct SocketProperty* pSockProp, std::shared_ptr<Comm::Socket::TCP::Client> cliSock) {

            }

#if 0
            void TcpMultiServer::CallbackReceiveFromCliSock(std::shared_ptr<Comm::Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize) {

                if (dataSize == Stock::Net::PacketCtrl::GetFixedPacketByteSize()) {
                    std::shared_ptr<Stock::Net::PacketCtrl> packCtrl = std::make_shared<Stock::Net::PacketCtrlNone>(data);
                    assert(packCtrl);
                    _Agent->GetProvider()->BroadCast(packCtrl);
                }
            }
#endif

            void TcpMultiServer::CallbackCloseFromCliSock(const struct SocketProperty* pSockProp, std::shared_ptr<Comm::Socket::TCP::Client> cliSock) {

            }
            
            int TcpMultiServer::GetConnectedClientCount(int isock) {
                
                assert((isock >= 0) && (isock < _SrvSockCount));
                return _SrvTcpSock[isock]->GetConnectedClientCount();
            }

            void TcpMultiServer::Broadcast(int isock, std::shared_ptr<Comm::Socket::NetPacket> pack) {

                assert((isock >= 0) && (isock < _SrvSockCount));
                _SrvTcpSock[isock]->Broadcast(pack);
            }

        }; // namespace End
    }; // namespace Socket
};// namespace Comm

