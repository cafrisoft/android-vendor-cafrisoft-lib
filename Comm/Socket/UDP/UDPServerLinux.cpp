#define CLOG_TAG "CommSocketUDPServerLinux"
#include <Comm/Socket/UDP/UDPServerLinux.hpp>
#include <Comm/Socket/UDP/UDPClientLinux.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)


namespace Comm {
    namespace Socket {
        namespace UDP {

            ServerLinux::ServerLinux(struct CreateConfig cfg) : Server(cfg)
                , _ListenSocket(-1)
            {

            }

            ServerLinux::~ServerLinux() {

                this->Close();
            }

            bool ServerLinux::Open() {
            
                struct sockaddr_in server_addr;// , client_addr;

                _ListenSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
                assert(_ListenSocket >= 0);
                   
#if 0
                int sendBufSize, rcvBufSize;
                socklen_t len = sizeof(int);
                getsockopt(_ListenSocket, SOL_SOCKET, SO_SNDBUF, &sendBufSize, &len);
                getsockopt(_ListenSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufSize, &len);
                CLOGI("[Linux UDPServerSocket] sendBufSize=%d  rcvBufSize=%d \n", sendBufSize, rcvBufSize);
#endif

                memset(&server_addr, 0x00, sizeof(server_addr));

                //setting server_addr
                server_addr.sin_family = AF_INET;
                server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
                server_addr.sin_port = htons((uint16_t)this->GetPortNum());

                //bind()
                if (bind(_ListenSocket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
                    printf("Server : Can't bind local address.\n");
                    assert(1);
                }

                return true;
            }

            bool ServerLinux::Close() {

                if (_ListenSocket != -1) {
                    ::close(_ListenSocket);
                    _ListenSocket = -1;
                }

                return false;
            }
            
            bool ServerLinux::ReceiveData(/*OUT*/unsigned char* data, int maxBufSize, /*OUT*/int* dataSize) {
            
                ssize_t rdsz;
                struct sockaddr_in echoClntAddr; /* Client address */
                socklen_t cliLen = sizeof(echoClntAddr);
                bool bRet = false;

                if (dataSize) *dataSize = 0;

                if ((rdsz = recvfrom(_ListenSocket, (char*)data, maxBufSize, 0, (struct sockaddr*)&echoClntAddr, &cliLen)) < 0) {
                    //DieWithError("recvfrom() failed");
                }
                else {
                    if (dataSize) *dataSize = (int)rdsz;
                    bRet = true;
                }

                return bRet;
            }

            int ServerLinux::GetRcvSocketBufferByteSize() {

                int bufSize = 0;
                socklen_t len = sizeof(int);

                getsockopt(_ListenSocket, SOL_SOCKET, SO_RCVBUF, &bufSize, &len);
                
                return bufSize;
            }

            int ServerLinux::GetSendSocketBufferByteSize() {

                int bufSize = 0;
                socklen_t len = sizeof(int);

                getsockopt(_ListenSocket, SOL_SOCKET, SO_SNDBUF, &bufSize, &len);

                return bufSize;
            }

            void Server::CheckSocketBuffer() {

                struct sockaddr_in server_addr;// , client_addr;

                int serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
                assert(serverSocket >= 0);

                memset(&server_addr, 0x00, sizeof(server_addr));

                //setting server_addr
                server_addr.sin_family = AF_INET;
                server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
                server_addr.sin_port = htons(55550);


                int sendBufSize, rcvBufSize;
                socklen_t len = sizeof(int);

                

                getsockopt(serverSocket, SOL_SOCKET, SO_SNDBUF, &sendBufSize, &len);
                getsockopt(serverSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufSize, &len);
                PRINTF("[Linux UDPServerSocket] Before: sendBufSize=%d  rcvBufSize=%d \n", sendBufSize, rcvBufSize, len);

                rcvBufSize *= 2;
                setsockopt(serverSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufSize, len);

                getsockopt(serverSocket, SOL_SOCKET, SO_SNDBUF, &sendBufSize, &len);
                getsockopt(serverSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufSize, &len);
                PRINTF("[Linux UDPServerSocket]  After :  sendBufSize=%d  rcvBufSize=%d \n", sendBufSize, rcvBufSize, len);


                close(serverSocket);
            }

        }; //namespace UDP
    }; //namespace Socket {
}; // namespace Comm {

#endif //#if (CommOS==CommOS_WIN)