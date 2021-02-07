#ifndef COMM_SOCKET_TCP_CLIENTLINUX_HPP__
#define COMM_SOCKET_TCP_CLIENTLINUX_HPP__

#include <Comm/Socket/TCP/TCPClient.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

namespace Comm {
    namespace Socket {
        namespace TCP {
        
            class ClientLinux : public Client {
                
            private:
                int _SocketFD;

            public:
                ClientLinux(const char* serverAddr, int portNum);
                ClientLinux(int sockFD);

                virtual ~ClientLinux();

            public:
                virtual bool Connect();
                virtual bool Disconnect();
                virtual bool IsConnect();

                virtual bool Receive(/*out*/ unsigned char* data, int maxBufSize, int* dataSize);
                virtual bool Send(const unsigned char* data, int dataSize);

                virtual int GetRcvSocketBufferByteSize();
                virtual int GetSendSocketBufferByteSize();
            };

        }; //namespace TCP
    }; //namespace Socket {
}; // namespace Comm {

#endif //#if (CommOS==CommOS_WIN)
#endif //COMM_DATAEX_PRODUCER_HPP__
