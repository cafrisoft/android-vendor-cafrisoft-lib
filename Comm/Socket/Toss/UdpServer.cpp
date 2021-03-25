#define CLOG_TAG "SocketTossUdpServer"
#include <Comm/Socket/Toss/UdpServer.hpp>

namespace Comm {
    namespace Socket {
        namespace Toss {

            UdpServer::UdpServer(int udpPort, int packByteSize, int maxCliSize) :
                _IsServiceRun(true)
                , _PacketByteSize(packByteSize)
            {

                _RcvRawData = new unsigned char[_PacketByteSize];
                assert(_RcvRawData);

                /*
                    create udp server socket
                */
                struct Comm::Socket::UDP::Server::CreateConfig  createConfig = {
                    udpPort,
                    packByteSize,
                    maxCliSize
                };
                _SrvUdpSock = Socket::UDP::Server::CreateObject(createConfig);
                assert(_SrvUdpSock);
                
                /*
                    ThreadService Start
                */
                _ThreadService = std::make_shared<OAL::ThreadService>(this);
                assert(_ThreadService);
            }

            UdpServer::~UdpServer() {
            
                _IsServiceRun = false;
                _SrvUdpSock.reset();
                _ThreadService.reset();

                delete[] _RcvRawData;
            }
                        
            bool UdpServer::IsServiceRun() {
                return _IsServiceRun;
            }

            void UdpServer::WaitForNextService() {

            }

            void UdpServer::Service() {

                int rdsz;
                _SrvUdpSock->ReceiveData(_RcvRawData, _PacketByteSize, &rdsz);
                if (rdsz == _PacketByteSize) {
                    this->CallbackReceiveFromCliSock(_RcvRawData, _PacketByteSize);
                    _TotalReceivedPacketCount++;
                    _ReceivedPacketCount++;
                }
            }

        }; // namespace Toss  
    }; // namespace Socket
};// namespace Comm

