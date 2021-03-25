#define CLOG_TAG "CommSocketTCPServerLinux"
#include <Comm/Socket/TCP/TCPServerLinux.hpp>
#include <Comm/Socket/TCP/TCPClientLinux.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)


namespace Comm {
    namespace Socket {
        namespace TCP {

            ServerLinux::ServerLinux(struct CreateConfig cfg) : Server(cfg)
                , _ListenSocket(-1)
            {

            }

            ServerLinux::~ServerLinux() {

                this->Close();
            }

            bool ServerLinux::Open() {
            
                struct sockaddr_in server_addr;// , client_addr;

                _ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                assert(_ListenSocket >= 0);
                    
                memset(&server_addr, 0x00, sizeof(server_addr));

                //setting server_addr
                server_addr.sin_family = AF_INET;
                server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
                server_addr.sin_port = htons((uint16_t)this->GetPortNum());

                //bind()
                if (bind(_ListenSocket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
                    printf("Server : Can't bind local address.\n");
                    assert(false);
                }

                //소켓을 수동 대기모드로 설정
                if (listen(_ListenSocket, this->GetMaxClientCount()) < 0) {
                    printf("Server : Can't listening connect.\n");
                    assert(false);
                }

                FD_ZERO(&_NewFDSet);
                FD_SET(_ListenSocket, &_NewFDSet);

                _MaxFDCount = _ListenSocket + 1;

                return true;
            }

            bool ServerLinux::Close() {

                for (int fd = 0; fd < FD_SETSIZE; fd++) {
                    if (_ClientArray[fd] != NULL) {
                        _ClientArray[fd].reset();
                    }
                }

                if (_ListenSocket != -1) {
                    ::close(_ListenSocket);
                    _ListenSocket = -1;
                }

                return true;
            }

            void ServerLinux::Select() {
            
                //unsigned int fdNum;
                socklen_t addr_len;
                struct sockaddr_in accept_addr;

                _OldFDSet = _NewFDSet;

#if 1
                ::select(_MaxFDCount, &_OldFDSet, NULL, NULL, NULL);
                //PRINTF("[%s] ln=%d  fdNum=%d  _MaxFDCount=%d ", __func__, __LINE__, fdNum, _MaxFDCount);
                if (FD_ISSET(_ListenSocket, &_OldFDSet))
                {
                    addr_len = sizeof(struct sockaddr_in);
                    int accept_fd = ::accept(_ListenSocket, (struct sockaddr*)&accept_addr, &addr_len);
                    //PRINTF("[%s] ln=%d", __func__, __LINE__, accept_fd);
                    if (accept_fd == -1)
                    {
                        //continue;
                    }
                    else {

#if 0
                        int sendBufSize, rcvBufSize;
                        socklen_t len = sizeof(int);
                        getsockopt(accept_fd, SOL_SOCKET, SO_SNDBUF, &sendBufSize, &len);
                        getsockopt(accept_fd, SOL_SOCKET, SO_RCVBUF, &rcvBufSize, &len);
                        CLOGI("[Linux TCPServer AcceptSocket] sendBufSize=%d  rcvBufSize=%d \n", sendBufSize, rcvBufSize);
#endif

                        //새로운 소켓이 접속했다. 
                        FD_SET(accept_fd, &_NewFDSet);
                        _ClientArray[accept_fd] = std::make_shared<ClientLinux>(accept_fd);
                        if (_MaxFDCount < (accept_fd + 1)) {
                            _MaxFDCount = accept_fd + 1;
                        }

                        this->SelectAcceptCallback(_ClientArray[accept_fd]);
                    }
                }
#endif

#if 1

                for (int i = 0; i < FD_SETSIZE; i++) {

                    if (_ClientArray[i].get() != NULL) {

                        int sock_fd = i;
                        if (FD_ISSET(sock_fd, &_OldFDSet))
                        {
                            //(*selectConfig._ReceiveFunc)(_ClientArray[i]);
                            memset(_ReceiveBuffer, 0x00, this->GetReceiveBufByteSize());
                            ssize_t readn = recv(sock_fd, (char*)_ReceiveBuffer, this->GetReceiveBufByteSize(), 0);
                            if (readn <= 0)
                            {
                                //  printf("socket close\n");
                                ::close(sock_fd);
                                FD_CLR(sock_fd, &_NewFDSet);
                                this->SelectCloseCallback(_ClientArray[sock_fd]);
                                _ClientArray[sock_fd].reset();
                                _ClientArray[sock_fd] = NULL;
                            }
                            else
                            {
                                //  send(sock_fd, buf, readn, 0);
                                this->SelectReceiveCallback(_ClientArray[sock_fd], (const unsigned char* )_ReceiveBuffer, (int)readn);
                            }

                        }
                    }
                }
#endif

            }

        }; //namespace TCP
    }; //namespace Socket {
}; // namespace Comm {

#endif //#if (CommOS==CommOS_WIN)