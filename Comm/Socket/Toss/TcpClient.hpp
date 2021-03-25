#ifndef COMM_SOCKET_TOSS_TCPCLIENT_HPP__
#define COMM_SOCKET_TOSS_TCPCLIENT_HPP__

#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/Log.hpp>
#include <Comm/OAL/ThreadService.hpp>
#include <Comm/Socket/TCP/TCPClient.hpp>
#include <Comm/Utils/Queue.hpp>

namespace Comm {
    namespace Socket {
        namespace Toss {


            class TcpClient : public Comm::OAL::IThreadService {

            private:
                std::shared_ptr<Comm::OAL::CriticalSection> _CsSendPacket;
                std::shared_ptr<Comm::Socket::TCP::Client> _TcpCliSock;
                std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;
                bool _IsServiceRun;
                unsigned char * _RcvRawData;
                int _PacketByteSize;

            public:
                TcpClient(std::string strServerIPAddr, int tcpPort, int packetByteSize);
                virtual ~TcpClient();

            private:
                virtual bool IsServiceRun();
                virtual void WaitForNextService();
                virtual void Service();

            protected:
                virtual void CallbackReceiveFromSrvSock(unsigned char* data, int dataByteSize) = 0;

            public:
                void SendPacket(std::shared_ptr<Comm::Socket::NetPacket> pack);
            };

        }; // namespace Toss  
    }; // namespace Socket
};// namespace Comm

#endif
