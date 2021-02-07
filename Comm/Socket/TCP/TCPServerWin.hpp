#ifndef COMM_SOCKET_TCP_SERVERWIN_HPP__
#define COMM_SOCKET_TCP_SERVERWIN_HPP__

#include <Comm/Socket/TCP/TCPServer.hpp>
#include <Comm/Utils/Vector.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
    namespace Socket {
        namespace TCP {

            class ClientWin;

            class ServerWin : public Server {
                
            private:
                SOCKET _ListenSocket;// = INVALID_SOCKET;
                fd_set _NewFDSet;
                fd_set _OldFDSet;
                unsigned char _ReceiveBuffer[4096];
                std::shared_ptr<ClientWin> *_ClientArray;

            public:
                ServerWin(struct CreateConfig cfg);
                virtual ~ServerWin();

            public:
                virtual bool Open();
                virtual bool Close();
                virtual void Select();
            };

        }; //namespace TCP
    }; //namespace Socket {
}; // namespace Comm {

#endif //#if (CommOS==CommOS_WIN)
#endif //COMM_DATAEX_PRODUCER_HPP__