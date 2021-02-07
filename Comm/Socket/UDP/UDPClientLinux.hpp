#ifndef COMM_SOCKET_UDP_CLIENTLINUX_HPP__
#define COMM_SOCKET_UDP_CLIENTLINUX_HPP__

#include <Comm/Socket/UDP/UDPClient.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

namespace Comm {
    namespace Socket {
        namespace UDP {
        
            class ClientLinux : public Client {
                
            private:
                int _SocketFD;

            public:
                ClientLinux(const char* serverAddr, int portNum);
                virtual ~ClientLinux();

            public:
                virtual bool Open();
                virtual bool Close();

                virtual bool Receive(/*out*/ unsigned char* data, int maxBufSize, int* dataSize);
                virtual bool Send(const unsigned char* data, int dataSize);
            };

        }; //namespace UDP
    }; //namespace Socket {
}; // namespace Comm {

#endif //#if (CommOS==CommOS_WIN)
#endif //COMM_DATAEX_PRODUCER_HPP__
