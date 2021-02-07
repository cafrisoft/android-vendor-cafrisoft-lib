#ifndef COMM_SOCKET_UDP_SERVERWIN_HPP__
#define COMM_SOCKET_UDP_SERVERWIN_HPP__

#include <Comm/Socket/UDP/UDPServer.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
    namespace Socket {
        namespace UDP {

            class ServerWin : public Server {
                
            private:
                SOCKET _ListenSocket;// = INVALID_SOCKET;
                std::shared_ptr<Client> _ClientArray[FD_SETSIZE];
                unsigned char _ReceiveBuffer[4096];

            public:
                ServerWin(struct CreateConfig cfg);
                virtual ~ServerWin();

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