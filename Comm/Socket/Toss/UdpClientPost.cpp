#define CLOG_TAG "SocketTossUdpClientPost"
#include <Comm/Socket/Toss/UdpClientPost.hpp>

namespace Comm {
    namespace Socket {
        namespace Toss {

            UdpClientPost::UdpClientPost(std::string serverIPAddr, int port) :
                _IsServiceRun(true)
            {
                _PacketQueue = std::make_shared<Comm::Utils::SyncQueue<std::shared_ptr<Socket::NetPacket>>>();
                assert(_PacketQueue);
                
                /* UdsClient Sock */
                _UdpCliSock = Comm::Socket::UDP::Client::CreateObject(serverIPAddr, port);
                assert(_UdpCliSock);

                /*
                    ThreadService Start
                */
                _ThreadService = std::make_shared<OAL::ThreadService>(this);
                assert(_ThreadService);
            }

            UdpClientPost::~UdpClientPost() {

                _IsServiceRun = false;
                _PacketQueue->Push(NULL);
                _ThreadService.reset();

            }
                        
            bool UdpClientPost::IsServiceRun() {
                return _IsServiceRun;
            }

            void UdpClientPost::WaitForNextService() {

            }

            void UdpClientPost::Service() {

                std::shared_ptr<Comm::Socket::NetPacket> pack = _PacketQueue->Pop();
                if (pack) {
                    _UdpCliSock->Send(pack);
                    _TotalReceivedPacketCount++;
                    _ReceivedPacketCount++;
                }
            }

            void UdpClientPost::PostPacket(std::shared_ptr<Comm::Socket::NetPacket> pack) {
            
                _PacketQueue->Push(pack);
            }
            
            

        }; // namespace Toss  
    }; // namespace Socket
};// namespace Comm

