#ifndef COMM_SOCKET_UDP_CLIENTWIN_HPP__
#define COMM_SOCKET_UDP_CLIENTWIN_HPP__

#include <Comm/Socket/UDP/UDPClient.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
    namespace Socket {
        namespace UDP {
        
            class ClientWin : public Client {
                
            private:
                SOCKET _Socket;

            public:
                ClientWin(const char* serverAddr, int portNum, int id=-1);

                virtual ~ClientWin();

                virtual bool Open();
                virtual bool Close();

            public:
                virtual bool Receive(/*out*/ unsigned char* data, int maxBufSize, int* dataSize);
                virtual bool Send(const unsigned char* data, int dataSize);
            };

        }; //namespace UDP
    }; //namespace Socket {
}; // namespace Comm {

#endif //#if (CommOS==CommOS_WIN)
#endif //COMM_DATAEX_PRODUCER_HPP__
