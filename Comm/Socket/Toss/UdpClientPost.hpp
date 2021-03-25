#ifndef COMM_SOCKET_TOSS_UDPCLIENTPOST_HPP__
#define COMM_SOCKET_TOSS_UDPCLIENTPOST_HPP__

#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/Log.hpp>
#include <Comm/OAL/ThreadService.hpp>
#include <Comm/Socket/UDP/UDPClient.hpp>
#include <Comm/Utils/Queue.hpp>

namespace Comm {
    namespace Socket {
        namespace Toss {

            class UdpClientPost : public Comm::OAL::IThreadService {

            private:
                std::shared_ptr<Comm::Utils::SyncQueue<std::shared_ptr<Comm::Socket::NetPacket>>> _PacketQueue;
                std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;
                bool _IsServiceRun;

                std::shared_ptr<Comm::Socket::UDP::Client> _UdpCliSock;
                
            public:
                UdpClientPost(std::string serverIPAddr, int port);
                virtual ~UdpClientPost();
                            
            private:
                virtual bool IsServiceRun();
                virtual void WaitForNextService();
                virtual void Service();

            public:
                void PostPacket(std::shared_ptr<Comm::Socket::NetPacket> pack);
            };

        }; // namespace Toss  
    }; // namespace Socket
};// namespace Comm

#endif
