#define CLOG_TAG "SocketTossMonitor"
#include <Comm/Socket/Toss/Monitor.hpp>
#include <Comm/OAL/System.hpp>

namespace Comm {
    namespace Socket {
        namespace Toss {

            Monitor::Monitor(int secondaryQueueCount) :
                _IsServiceRun(false)
            {
                /*
                    ThreadService Start
                */
                _ThreadService = std::make_shared<OAL::ThreadService>(this);
                assert(_ThreadService);
            }

            Monitor::~Monitor() {

                _IsServiceRun = false;
                _ThreadService.reset();
            }
                        
            bool Monitor::IsServiceRun() {
                return _IsServiceRun;
            }

            void Monitor::EnableService() {
            
                _IsServiceRun = true;
            }

            void Monitor::DisableService() {
            
                _IsServiceRun = false;
            }

            bool Monitor::IsEnableService() {
            
                return _IsServiceRun;
            }

            void Monitor::WaitForNextService() {

                long long startTick = Comm::OAL::System::GetTickCount64();
                long long curTick;
                do {
                    Comm::OAL::Thread::Sleep(100);
                    curTick = Comm::OAL::System::GetTickCount64();
                } while ((curTick - startTick) < 1000LL);
            }

#if 0
            void Monitor::Service() {

            }
#endif

     

        }; // namespace Toss  
    }; // namespace Socket
};// namespace Comm

