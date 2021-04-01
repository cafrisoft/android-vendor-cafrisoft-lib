#define CLOG_TAG "SocketTossSingleService"
#include <Comm/Socket/Toss/SingleService.hpp>
#include <Comm/OAL/System.hpp>

namespace Comm {
    namespace Socket {
        namespace Toss {

            SingleService::SingleService(bool isServiceRun) :
                _IsServiceRun(isServiceRun)
            {
                /*
                    ThreadService Start
                */
                _ThreadService = std::make_shared<OAL::ThreadService>(this);
                assert(_ThreadService);
            }

            SingleService::~SingleService() {

                _IsServiceRun = false;
                _ThreadService.reset();
            }
                        
            bool SingleService::IsServiceRun() {
                return _IsServiceRun;
            }

            void SingleService::EnableService() {
            
                _IsServiceRun = true;
            }

            void SingleService::DisableService() {
            
                _IsServiceRun = false;
            }

            bool SingleService::IsEnableService() {
            
                return _IsServiceRun;
            }

            void SingleService::WaitForNextService() {

                long long startTick = Comm::OAL::System::GetTickCount64();
                long long curTick;
                do {
                    Comm::OAL::Thread::Sleep(100);
                    curTick = Comm::OAL::System::GetTickCount64();
                } while ((curTick - startTick) < 1000LL);
            }

#if 0
            void SingleService::Service() {

            }
#endif

     

        }; // namespace Toss  
    }; // namespace Socket
};// namespace Comm

