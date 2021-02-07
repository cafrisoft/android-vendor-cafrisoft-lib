#ifndef COMM_SOCKET_TCP_SERVERLINUX_HPP__
#define COMM_SOCKET_TCP_SERVERLINUX_HPP__

#include <Comm/Socket/TCP/TCPServer.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

namespace Comm {
    namespace Socket {
        namespace TCP {

            class ServerLinux : public Server {
            
            private:
                int _ListenSocket;// = INVALID_SOCKET;
                int _MaxFDCount;
                fd_set _NewFDSet;
                fd_set _OldFDSet;
                std::shared_ptr<Client> _ClientArray[FD_SETSIZE];
                unsigned char _ReceiveBuffer[4096];

            public:
                ServerLinux(struct CreateConfig cfg);
                virtual ~ServerLinux();

            public:
                virtual bool Open();
                virtual bool Close();

            public:
                virtual void Select();
            };

        }; //namespace TCP
    }; //namespace Socket {
}; // namespace Comm {

#endif //#if (CommOS==CommOS_WIN)
#endif //COMM_DATAEX_PRODUCER_HPP__