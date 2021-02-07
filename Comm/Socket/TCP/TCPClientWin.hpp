#ifndef COMM_SOCKET_TCP_CLIENTWIN_HPP__
#define COMM_SOCKET_TCP_CLIENTWIN_HPP__

#include <Comm/Socket/TCP/TCPClient.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
    namespace Socket {
        namespace TCP {
        
            class ClientWin : public Client {
                
            private:
                SOCKET _Socket;

            public:
                ClientWin(const char* serverAddr, int portNum, int id=-1);
                ClientWin(SOCKET sock,  int id);

                virtual ~ClientWin();

            public:
                virtual bool Connect();
                virtual bool Disconnect();
                virtual bool IsConnect();

                virtual bool Receive(/*out*/ unsigned char* data, int maxBufSize, int* dataSize);
                virtual bool Send(const unsigned char* data, int dataSize);

                SOCKET Get_SOCKET();

                virtual int GetRcvSocketBufferByteSize();
                virtual int GetSendSocketBufferByteSize();
            };

        }; //namespace TCP
    }; //namespace Socket {
}; // namespace Comm {

#endif //#if (CommOS==CommOS_WIN)
#endif //COMM_DATAEX_PRODUCER_HPP__
