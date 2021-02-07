#ifndef COMM_SOCKET_UDP_SERVERLINUX_HPP__
#define COMM_SOCKET_UDP_SERVERLINUX_HPP__

#include <Comm/Socket/UDP/UDPServer.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

namespace Comm {
    namespace Socket {
        namespace UDP {

            class ServerLinux : public Server {
            
            private:
                int _ListenSocket;// = INVALID_SOCKET;
                std::shared_ptr<Client> _ClientArray[FD_SETSIZE];
                unsigned char _ReceiveBuffer[4096];

            public:
                ServerLinux(struct CreateConfig cfg);
                virtual ~ServerLinux();

            public:
                virtual bool Open();
                virtual bool Close();
                virtual bool ReceiveData(/*OUT*/unsigned char* data, int maxBufSize, /*OUT*/int* dataSize);

                virtual int GetRcvSocketBufferByteSize();
                virtual int GetSendSocketBufferByteSize();

            };

        }; //namespace UDP
    }; //namespace Socket {
}; // namespace Comm {

#endif //#if (CommOS==CommOS_WIN)
#endif //COMM_DATAEX_PRODUCER_HPP__