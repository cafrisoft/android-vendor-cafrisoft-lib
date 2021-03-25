#ifndef COMM_SOCKET_TOSS_MONITOR_HPP__
#define COMM_SOCKET_TOSS_MONITOR_HPP__

#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/Log.hpp>
#include <Comm/OAL/ThreadService.hpp>
#include <Comm/Socket/TCP/TCPClient.hpp>
#include <Comm/Utils/Queue.hpp>

namespace Comm {
    namespace Socket {
        namespace Toss {

            class Monitor : public Comm::OAL::IThreadService {

            private:
                std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;
                bool _IsServiceRun;
                
            public:
                Monitor(int secondaryQueueCount = 0);
                virtual ~Monitor();
                            
            private:
                virtual bool IsServiceRun();
                virtual void WaitForNextService();
                //virtual void Service();

            protected:
                void EnableService();
                void DisableService();
                bool IsEnableService();
            };

        }; // namespace Toss  
    }; // namespace Socket
};// namespace Comm

#endif
