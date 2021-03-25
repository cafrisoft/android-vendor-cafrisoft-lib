#ifndef COMM_SOCKET_UDP_CLIENT_HPP__
#define COMM_SOCKET_UDP_CLIENT_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/Socket/NetPacket.hpp>
#include <Comm/OAL/CriticalSection.hpp>

namespace Comm {
    namespace Socket {
        namespace UDP {
        
            class Client : public Base::Object {
                
            public:
                static std::shared_ptr<Client> CreateObject(std::string serverAddr, int portNum);

            private:
                char _ServerAddr[128];
                char _ServerAddrBuff[128];
                int _PortNum;
                int _ID;
                std::shared_ptr<OAL::CriticalSection> _CriticalSectionSendData;


            protected:
                Client(const char* serverAddr=NULL, int portNum=0, int id=-1);
                virtual ~Client();

                virtual bool Open() = 0;
                virtual bool Close() = 0;
            
            public:
                virtual bool Receive(/*out*/ unsigned char* data, int maxBufSize, int* dataSize) = 0;
                virtual bool Send(const unsigned char* data, int dataSize) = 0;
                bool Send(std::shared_ptr<NetPacket> pack);

                int GetID();
                int GetPortNum();
                const char* GetServerAddr();
            };

        }; //namespace UDP
    }; //namespace Socket {
}; // namespace Comm {

#endif //COMM_DATAEX_PRODUCER_HPP__
