#ifndef COMM_SOCKET_TOSS_UDPSERVER_HPP__
#define COMM_SOCKET_TOSS_UDPSERVER_HPP__

#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/Log.hpp>
#include <Comm/OAL/ThreadService.hpp>
#include <Comm/Socket/UDP/UDPServer.hpp>
#include <Comm/Utils/Queue.hpp>

namespace Comm {
    namespace Socket {
        namespace Toss {


            class UdpServer : public Comm::OAL::IThreadService {

            private:
                std::shared_ptr<Comm::Socket::UDP::Server> _SrvUdpSock;
                std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;
                bool _IsServiceRun;
                int _PacketByteSize;
                unsigned char* _RcvRawData;

            public:
                UdpServer(int udpPort, int packByteSize, int maxCliSize);
                virtual ~UdpServer();

            private:
                virtual bool IsServiceRun();
                virtual void WaitForNextService();
                virtual void Service();

            protected:
                virtual void CallbackReceiveFromCliSock(const unsigned char* data, int dataSize) = 0;
            };

        }; // namespace Toss  
    }; // namespace Socket
};// namespace Comm

#endif
