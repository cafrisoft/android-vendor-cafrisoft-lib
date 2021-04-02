#include <Comm/Global/BuildOptions.h>
#include <Comm/Socket/TCP/TCPServerWin.hpp>
#include <Comm/Socket/TCP/TCPClientWin.hpp>

#if (CommOS==CommOS_WIN)

/*
Reference Code : 
https://docs.microsoft.com/en-us/windows/win32/winsock/complete-server-code
*/

#include <ws2tcpip.h>

#define DEFAULT_BUFLEN  512

namespace Comm {
    namespace Socket {
        namespace TCP {

            
            ServerWin::ServerWin(struct CreateConfig cfg) : Server(cfg)
            , _ListenSocket(INVALID_SOCKET)
            {
                _ClientArray = new std::shared_ptr<ClientWin>[this->GetMaxClientCount()];
                assert(_ClientArray);
            }

            ServerWin::~ServerWin() {

                this->Close();
                delete[] _ClientArray;
            }

            bool ServerWin::Open() {
            
                WSADATA wsaData;
                int iResult;

                //SOCKET ListenSocket = INVALID_SOCKET;
                //SOCKET ClientSocket = INVALID_SOCKET;

                struct addrinfo* result = NULL;
                struct addrinfo hints;

                //int iSendResult;
                //char recvbuf[DEFAULT_BUFLEN];
                int recvbuflen = DEFAULT_BUFLEN;

                // Initialize Winsock
                iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
                if (iResult != 0) {
                    printf("WSAStartup failed with error: %d\n", iResult);
                    return false;
                }

                ZeroMemory(&hints, sizeof(hints));
                hints.ai_family = AF_INET;
                hints.ai_socktype = SOCK_STREAM;
                hints.ai_protocol = IPPROTO_TCP;
                hints.ai_flags = AI_PASSIVE;

                // Resolve the server address and port
                char szPort[32];
                sprintf(szPort, "%d", this->GetPortNum());
                iResult = getaddrinfo(NULL, szPort, &hints, &result);
                if (iResult != 0) {
                    printf("getaddrinfo failed with error: %d\n", iResult);
                    //WSACleanup();
                    return false;
                }

                // Create a SOCKET for connecting to server
                _ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
                if (_ListenSocket == INVALID_SOCKET) {
                    printf("socket failed with error: %ld\n", WSAGetLastError());
                    freeaddrinfo(result);
                    //WSACleanup();
                    return false;
                }

                // Setup the TCP listening socket
                iResult = bind(_ListenSocket, result->ai_addr, (int)result->ai_addrlen);
                if (iResult == SOCKET_ERROR) {
                    printf("bind failed with error: %d\n", WSAGetLastError());
                    freeaddrinfo(result);
                    //closesocket(_ListenSocket);
                    //WSACleanup();
                    return false;
                }

                freeaddrinfo(result);

                iResult = listen(_ListenSocket, SOMAXCONN);
                if (iResult == SOCKET_ERROR) {
                    printf("listen failed with error: %d\n", WSAGetLastError());
                    //closesocket(_ListenSocket);
                    //WSACleanup();
                    return false;
                }

                FD_ZERO(&_NewFDSet);
                FD_SET(_ListenSocket, &_NewFDSet);

                return true;
            }

            bool ServerWin::Close() {

                if (_ListenSocket != INVALID_SOCKET) {
                    closesocket(_ListenSocket);
                    _ListenSocket = INVALID_SOCKET;
                }
                WSACleanup();

                return true;
            }

#if 0
            std::shared_ptr<Client> ServerWin::Accept() {
                SOCKET clientSocket = INVALID_SOCKET;
                std::shared_ptr<Client> clientObj;

                // Accept a client socket
                clientSocket = accept(_ListenSocket, NULL, NULL);
                if (clientSocket == INVALID_SOCKET) {
                    printf("accept failed with error: %d\n", WSAGetLastError());
                    //closesocket(ListenSocket);
                    //WSACleanup();
                    return NULL;
                }

                clientObj = std::make_shared <ClientWin>(clientSocket);

                return clientObj;
            }
#endif
                        
            void ServerWin::Select() {
            
                unsigned int fdNum;
                int addr_len;
                struct sockaddr_in accept_addr;
                
                _OldFDSet = _NewFDSet;

#if 1
                fdNum = ::select(0, &_OldFDSet, NULL, NULL, NULL);
                if (FD_ISSET(_ListenSocket, &_OldFDSet))
                {
                    addr_len = sizeof(struct sockaddr_in);
                    SOCKET accept_fd = ::accept(_ListenSocket, (struct sockaddr*)&accept_addr, &addr_len);
                    if (accept_fd == INVALID_SOCKET)
                    {
                        //continue;
                    }
                    else {
                        //새로운 소켓이 접속했다. 등록을 한다..

                        int sockIdx = -1;

                        //배열에서 빈자리를 찾는다.
                        for (int icli = 0; icli < this->GetMaxClientCount(); icli++) {
                            if (_ClientArray[icli] == NULL) {
                                sockIdx = icli;
                                break;
                            }
                        }
                        
                        if (sockIdx >= 0) {
                            FD_SET(accept_fd, &_NewFDSet);
                            std::shared_ptr<ClientWin> cliWin = std::make_shared<ClientWin>(accept_fd, sockIdx);
                            assert(cliWin);
                            _ClientArray[sockIdx] = cliWin;
                            this->SelectAcceptCallback(cliWin);
                        }

                    }
                }
#endif

#if 1
                for (u_int iFD = 1; iFD <= _NewFDSet.fd_count; iFD++)
                {
                    SOCKET sock_fd = _NewFDSet.fd_array[iFD];
                    if (FD_ISSET(sock_fd, &_OldFDSet))
                    {
                        memset(_ReceiveBuffer, 0x00, this->GetReceiveBufByteSize());
                        int readn = recv(sock_fd, (char*)_ReceiveBuffer, this->GetReceiveBufByteSize(), 0);
                        if (readn <= 0)
                        {
                          //  printf("socket close\n");
                            closesocket(sock_fd);
                            FD_CLR(sock_fd, &_NewFDSet);

                            //배열에서 sock_fd가 같은 index를 찾아서 Close처리를 한다. 
                            for (int icli = 0; icli < this->GetMaxClientCount(); icli++) {
                                std::shared_ptr<ClientWin> cliWin = _ClientArray[icli];
                                if (cliWin != NULL) {
                                    if (cliWin->Get_SOCKET() == sock_fd) {
                                        this->SelectCloseCallback(cliWin);
                                        _ClientArray[icli].reset();
                                        break;
                                    }
                                }
                            }
                        }
                        else
                        {
                            //배열에서 sock_fd가 같은 index를 찾아서 Close처리를 한다. 
                            for (int icli = 0; icli < this->GetMaxClientCount(); icli++) {

                                std::shared_ptr<ClientWin> cliWin = _ClientArray[icli];
                                if (cliWin != NULL) {
                                    if (cliWin->Get_SOCKET() == sock_fd) {
                                        this->SelectReceiveCallback(_ClientArray[icli], _ReceiveBuffer, readn);
                                        break;
                                    }
                                }
                            }
                        }
                        
                        if (--fdNum <= 0) break;
                    }

                }
#endif

            }

        }; //namespace TCP
    }; //namespace Socket {
}; // namespace Comm {

#endif //#if (CommOS==CommOS_WIN)