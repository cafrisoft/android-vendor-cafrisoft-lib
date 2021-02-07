#ifndef COMM_SOCKET_UDP_SERVER_HPP__
#define COMM_SOCKET_UDP_SERVER_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/Socket/UDP/UDPClient.hpp>
#include <Comm/OAL/HeaderFiles.hpp>
#include <Comm/Utils/IntegerCount.hpp>

namespace Comm {
    namespace Socket {
        namespace UDP {
            
            class Server : public Base::Object {

            public:
                struct CreateConfig {
                    int _PortNum;
                    int _ReceiveBufSize;
                    int _MaxClientCount;
                };

            public:
                static std::shared_ptr<Server> CreateObject(struct CreateConfig cfg);
            
            private:
                struct CreateConfig _CreateConfig;
                long long _ServerStartTick;

                //Log
                std::shared_ptr<OAL::Timer> _LogTimer;
                Utils::IntegerCount _ReceivedDataCount;

                //Service
                struct QueueDataHeader {
                    int dataSize;
                };
                std::shared_ptr<OAL::CriticalSection> _PacketQueueCS;
                TCircular_Queue<unsigned char*> _PacketQueue;
                bool _IsServiceThreadRun;
                std::shared_ptr<OAL::Thread> _ServiceThread;

            protected:
                Server(struct CreateConfig cfg);
                virtual ~Server();
            
            protected:
                virtual bool Open() = 0;
                virtual bool Close() = 0;

            public:
                virtual bool ReceiveData(/*OUT*/unsigned char* data, int maxBufSize, /*OUT*/int *dataSize) = 0;
            
            public:
                bool ServiceStart();
                bool ServiceStop();
                bool ServiceReadData(/*OUT*/unsigned char* data, int maxBufSize, /*OUT*/int* dataSize);
            private:
                void Service();
                static void ServiceStub(void* arg);


            public:
                void LogStart();
                void LogStop();
            protected:
                virtual void EventTimerCallbackLog();

            public:
                int GetPortNum();
                int GetReceiveBufByteSize();
                int GetMaxClientCount();
                virtual int GetRcvSocketBufferByteSize() = 0;
                virtual int GetSendSocketBufferByteSize() = 0;

            public:
                static void CheckSocketBuffer();
            };

        }; //namespace UDP
    }; //namespace Socket {
}; // namespace Comm {

#endif //COMM_DATAEX_PRODUCER_HPP__