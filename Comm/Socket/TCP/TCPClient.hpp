#ifndef COMM_SOCKET_TCP_CLIENT_HPP__
#define COMM_SOCKET_TCP_CLIENT_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/Socket/NetPacket.hpp>
#include <Comm/OAL/CriticalSection.hpp>

namespace Comm {
    namespace Socket {
        namespace TCP {
        
            class Client : public Base::Object {
                
            public:
                static std::shared_ptr<Client> CreateObject(const char* serverAddr, int portNum);

            private:
                char _ServerAddr[128];
                char _ServerAddrBuff[128];
                int _PortNum;
                int _ID;

                std::shared_ptr<Comm::OAL::CriticalSection> _CsRcvPackSync;
                enum {
                    _RcvPackQueueBufByteSize = 4096
                };
                unsigned char _RcvPackQueuBuf[_RcvPackQueueBufByteSize];
                int _RcvPackQueueFront;
                int _RcvPackQueueRear;

            protected:
                Client(const char* serverAddr=NULL, int portNum=0, int id=-1);
                virtual ~Client();

            public:
                
                virtual bool Connect() = 0;
                virtual bool Disconnect() = 0;
                virtual bool IsConnect() = 0;

                virtual bool Receive(/*out*/ unsigned char* data, int maxBufSize, int* dataSize) = 0;
                bool Receive(std::shared_ptr<NetPacket> pack);

                bool ReceiveSync(/*out*/ unsigned char* data, int reqPackByteSize);  //요청하는 크기만큼 받아오는 것을 보증한다. 
                
                virtual bool Send(const unsigned char* data, int dataSize) = 0;
                bool Send(std::shared_ptr<NetPacket> pack);

                int GetID();
                int GetPortNum();
                const char* GetServerAddr();
                bool SetServerAddr(const char* serverIPAddr);

                virtual int GetRcvSocketBufferByteSize() = 0;
                virtual int GetSendSocketBufferByteSize() = 0;
            };

        }; //namespace TCP
    }; //namespace Socket {
}; // namespace Comm {

#endif //COMM_DATAEX_PRODUCER_HPP__
