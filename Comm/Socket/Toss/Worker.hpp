#ifndef COMM_SOCKET_TOSS_WORKER_HPP__
#define COMM_SOCKET_TOSS_WORKER_HPP__

#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/Log.hpp>
#include <Comm/OAL/ThreadService.hpp>
#include <Comm/Socket/TCP/TCPClient.hpp>
#include <Comm/Utils/Queue.hpp>

namespace Comm {
    namespace Socket {
        namespace Toss {

            class Worker : public Comm::OAL::IThreadService {

            private:
                std::shared_ptr<Comm::Utils::SyncQueue<std::shared_ptr<Comm::Socket::NetPacket>>> _PacketQueue;
                std::shared_ptr<Comm::Utils::SyncQueue<std::shared_ptr<Comm::Socket::NetPacket>>> _PacketQueueSecondary[16];
                std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;
                bool _IsServiceRun;
                int _SecondaryQueueCount;
                
            public:
                Worker(int secondaryQueueCount = 0);
                virtual ~Worker();
                            
            private:
                virtual bool IsServiceRun();
                virtual void WaitForNextService();
                virtual void Service();
            
            protected:
                virtual void CallbackReceiveFromOtherThread(std::shared_ptr<Comm::Socket::NetPacket> pack) = 0;

            public:
                void PostPacket(std::shared_ptr<Comm::Socket::NetPacket> pack);
                void PostPacketToSecondaryQueue(int queuIdx, std::shared_ptr<Comm::Socket::NetPacket> pack);
            protected:
                std::shared_ptr<Comm::Socket::NetPacket> ReceivePacketFromSecondaryQueue(int queuIdx);
            };

        }; // namespace Toss  
    }; // namespace Socket
};// namespace Comm

#endif
