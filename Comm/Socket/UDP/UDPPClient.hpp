#ifndef COMM_SOCKET_UDP_CLIENT_HPP__
#define COMM_SOCKET_UDP_CLIENT_HPP__

#include <Comm/Base/Object.hpp>

namespace Comm {
    namespace Socket {
        namespace UDP {
        
            class Client : public Base::Object {
                
            public:
                static std::shared_ptr<Client> CreateObject(const char* serverAddr, int portNum);

            private:
                char _ServerAddr[128];
                char _ServerAddrBuff[128];
                int _PortNum;
                int _ID;

            protected:
                Client(const char* serverAddr=NULL, int portNum=0, int id=-1);
                virtual ~Client();

            public:
                virtual bool Connect() = 0;
                virtual bool Disconnect() = 0;

                virtual bool Receive(/*out*/ unsigned char* data, int maxBufSize, int* dataSize) = 0;
                virtual bool Send(const unsigned char* data, int dataSize) = 0;

                int GetID();
                int GetPortNum();
                const char* GetServerAddr();
            };

        }; //namespace UDP
    }; //namespace Socket {
}; // namespace Comm {

#endif //COMM_DATAEX_PRODUCER_HPP__
