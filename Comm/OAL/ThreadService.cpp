#include <Comm/OAL/ThreadService.hpp>

namespace Comm {
    namespace OAL {

        IThreadService::IThreadService() :
            _TotalReceivedPacketCount(0)
            , _ReceivedPacketCount(0)
        {

        }

        IThreadService::~IThreadService() 
        {
        
        }

        long long IThreadService::GetTotalReceivedPacketCount() {

            return _TotalReceivedPacketCount;
        }

        long long IThreadService::GetReceivedPacketCount() {

            return _ReceivedPacketCount;
        }

        void IThreadService::ResetReceivedPacketCount() {
            _ReceivedPacketCount = 0;
        }



        ThreadService::ThreadService(IThreadService* pService) :
            _IThreadService(pService)
            , _IsExit(false)
        {
            _Thread = Thread::CreateObject(ThreadService::ServiceStub, this);
            assert(_Thread);
        }

        ThreadService::~ThreadService() {
            
            _IsExit = true; //Therad Á¾·á 
            _Thread.reset();

        }

        void ThreadService::ServiceStub(void* param) {
            
            ThreadService* pThreadService = (ThreadService*)param;
            //ITheadService* iThreadService = pThreadService->_IThreadService;

            while (!pThreadService->_IsExit) {
                while (pThreadService->_IThreadService->IsServiceRun()) {
                    
                    pThreadService->_IThreadService->Service();
                    if (pThreadService->_IThreadService->IsServiceRun() == false) {
                        break;
                    }
                    pThreadService->_IThreadService->WaitForNextService();
                }
                Thread::Sleep(100);
            }
        }

        bool ThreadService::IsRun() {

            bool bRet = false;
            if (_Thread != NULL) {
                bRet = true;
            }
            return bRet;
        }

    }; //namespace OAL
}; //namespace Comm
