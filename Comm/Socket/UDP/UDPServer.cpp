#include <Comm/Global/BuildOptions.h>
#define CLOG_TAG "CommStockUDPServer"
#include <Comm/Socket/UDP/UDPServer.hpp>
#include <Comm/Socket/UDP/UDPServerWin.hpp>
#include <Comm/Socket/UDP/UDPServerLinux.hpp>

namespace Comm {
    namespace Socket {
        namespace UDP {

            std::shared_ptr<Server> Server::CreateObject(struct CreateConfig cfg) {
            
                std::shared_ptr<Server> obj;
#if (CommOS==CommOS_WIN)
                obj = std::make_shared<ServerWin>(cfg);
#elif (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)
                obj = std::make_shared<ServerLinux>(cfg);
#else
                #error "OS is not defined"
#endif
                assert(obj);

                if (!obj->Open()) {
                    obj->Close();
                    obj.reset();
                }

                return obj;
            }

            Server::Server(struct CreateConfig cfg) :
                _PacketQueue(1024*100)
            {
                memcpy(&_CreateConfig, &cfg, sizeof(cfg));
                _LogTimer = OAL::Timer::CreateObject(this, TimerID::Log, 1000/*tick*/, false/*defaultStart*/);

                _ServerStartTick = OAL::System::GetTickCount64();

                _PacketQueueCS = OAL::CriticalSection::CreateObject();
                assert(_PacketQueueCS);
            }

            Server::~Server() {

            }

            int Server::GetPortNum() {
                return _CreateConfig._PortNum;
            }

            int Server::GetReceiveBufByteSize() {
                return _CreateConfig._ReceiveBufSize;
            }

            int Server::GetMaxClientCount() {
                return _CreateConfig._MaxClientCount;
            }

            void Server::LogStart() {
                _LogTimer->Start();
            }

            void Server::LogStop() {
                _LogTimer->Stop();
            }

            void Server::EventTimerCallbackLog() {

                long long curTick = OAL::System::GetTickCount64();

                PRINTF("[UDPServer Log] %lld. RcvData=%d ",  (curTick-_ServerStartTick)/1000LL, _ReceivedDataCount.GetCount());
                _ReceivedDataCount.Reset();
            }

            bool Server::ServiceStart() {
            
                _IsServiceThreadRun = true;
                _ServiceThread = OAL::Thread::CreateObject(Server::ServiceStub, this);
                return true;
            }

            bool Server::ServiceStop() {
            
                _IsServiceThreadRun = false;
                _ServiceThread.reset();

                return true;
            }

            bool Server::ServiceReadData(/*OUT*/unsigned char* data, int maxBufSize, /*OUT*/int* dataSize) {
            
                unsigned char* queueData = NULL;
                bool bRet = false;

                if (dataSize) *dataSize = 0;

                _PacketQueueCS->Lock();
                if (!_PacketQueue.IsEmpty()) {
                    _PacketQueue.Delete(queueData);
                }
                _PacketQueueCS->Unlock();

                if (queueData) {
                    struct QueueDataHeader* pHdr = (struct QueueDataHeader*)queueData;
                    unsigned char* pPayload = &queueData[sizeof(struct QueueDataHeader)];

                    int copyByteSize = pHdr->dataSize;
                    if (copyByteSize > maxBufSize) {
                        copyByteSize = maxBufSize;
                    }

                    memcpy(data, pPayload, copyByteSize);
                    bRet = true;
                    delete[] queueData;

                    if (dataSize) *dataSize = copyByteSize;
                }

                return bRet;
            }

            void Server::ServiceStub(void* arg) {
                Server* pObj = (Server*)arg;
                pObj->Service();
            }

            void Server::Service() {
                
                int dataSize;
                int dataMaxSize = 1024 * 16;
                unsigned char* data = new unsigned char[dataMaxSize];
                assert(data);

                while (_IsServiceThreadRun) {
                    this->ReceiveData(data, dataMaxSize, &dataSize);
                    if (dataSize > 0) {
                        
                        int queueDataSize = dataSize + (int)sizeof(struct QueueDataHeader);
                        unsigned char* queueData = new unsigned char[queueDataSize];
                        assert(queueData);

                        struct QueueDataHeader* pHdr = (struct QueueDataHeader*)queueData;
                        unsigned char* pPayLoad = &queueData[sizeof(struct QueueDataHeader)];

                        pHdr->dataSize = dataSize;
                        memcpy(pPayLoad, data, dataSize);

                        _PacketQueueCS->Lock();
                        if (_PacketQueue.IsFull()) {
                            unsigned char* tmpQueueData;
                            _PacketQueue.Delete(tmpQueueData);
                            delete[] tmpQueueData;
                        }
                        _PacketQueue.Add(queueData);
                        _PacketQueueCS->Unlock();

                        _ReceivedDataCount += dataSize;
                    }
                    else {
                        OAL::Thread::Sleep(1);
                    }
                }

                delete[]data;
            }
            
        }; //namespace UDP
    }; //namespace Socket {
}; // namespace Comm {

