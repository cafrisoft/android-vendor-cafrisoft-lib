#define CLOG_TAG "SocketTossTcpClient"
#include <Comm/Socket/Toss/TcpClient.hpp>

namespace Comm {
    namespace Socket {
        namespace Toss {

            TcpClient::TcpClient(std::string strServerIPAddr, int tcpPort, int packetByteSize) :
                _IsServiceRun(true)
                , _PacketByteSize(packetByteSize)
            {
                _CsSendPacket = Comm::OAL::CriticalSection::CreateObject();
                assert(_CsSendPacket);

                _RcvRawData = new unsigned char[_PacketByteSize];
                assert(_RcvRawData);
                
                _TcpCliSock = Comm::Socket::TCP::Client::CreateObject(strServerIPAddr.c_str(), tcpPort);
                assert(_TcpCliSock);


                /*
                    ThreadService Start
                */
                _ThreadService = std::make_shared<OAL::ThreadService>(this);
                assert(_ThreadService);
            }

            TcpClient::~TcpClient() {
            
                _IsServiceRun = false;
                if (_TcpCliSock->IsConnect()) {
                    _TcpCliSock->Disconnect();
                }

                _ThreadService.reset();
                
                _TcpCliSock.reset();
                delete[] _RcvRawData;
            }

            bool TcpClient::IsServiceRun() {
                return _IsServiceRun;
            }

            void TcpClient::WaitForNextService() {
                Comm::OAL::Thread::Sleep(3000);
            }

            void TcpClient::Service() {

                bool bRet;

                bRet = _TcpCliSock->Connect();
                if (bRet) {
                    CLOGI("Socket Connect OK, Server(%s:%d) SockBufSize=[%d %d] ", _TcpCliSock->GetServerAddr(), _TcpCliSock->GetPortNum(), _TcpCliSock->GetRcvSocketBufferByteSize(), _TcpCliSock->GetSendSocketBufferByteSize() );

                    while (true) {
                        bRet = _TcpCliSock->ReceiveSync(_RcvRawData, _PacketByteSize);
                        if (bRet) {
                            this->CallbackReceiveFromSrvSock(_RcvRawData, _PacketByteSize);
                        }
                        else {
                            CLOGI("Socket Abort (%s:%d)", _TcpCliSock->GetServerAddr(), _TcpCliSock->GetPortNum());
                            break;
                        }
                    }
                    _TcpCliSock->Disconnect();
                }
                else {
                    CLOGI("Socket Connect FAIL (%s:%d)", _TcpCliSock->GetServerAddr(), _TcpCliSock->GetPortNum());
                }

            }

            void TcpClient::SendPacket(std::shared_ptr<Comm::Socket::NetPacket> pack) {
            
                Comm::OAL::Lock lock(_CsSendPacket);

                if (_TcpCliSock->IsConnect()) {
                    _TcpCliSock->Send(pack);
                }
            }

        }; // namespace Toss  
    }; // namespace Socket
};// namespace Comm

