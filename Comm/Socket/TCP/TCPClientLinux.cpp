#include <Comm/Socket/TCP/TCPClientLinux.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

namespace Comm {
    namespace Socket {
        namespace TCP {

            ClientLinux::ClientLinux(const char* serverAddr, int portNum) : Client(serverAddr, portNum)
                , _SocketFD(-1)
            {
            
            }

            ClientLinux::ClientLinux(int sockFD) : Client( "127.0.0.1", 0 /*portNum*/, sockFD /*ID*/)
               ,_SocketFD(sockFD)
            {

            }
            
            ClientLinux::~ClientLinux() {

                this->Disconnect();
            }

            bool ClientLinux::Connect() {

                bool bRet = false;
                int sock_fd;

                sock_fd = socket(PF_INET, SOCK_STREAM, 0);
                if (sock_fd < 0) {
                    //printf("client socket error\n");
                }
                else {
                    struct sockaddr_in serv_addr;

                    memset(&serv_addr, 0, sizeof(serv_addr));
                    serv_addr.sin_family = AF_INET;
                    serv_addr.sin_addr.s_addr = inet_addr(this->GetServerAddr());
                    serv_addr.sin_port = htons((short)this->GetPortNum());

                    if (connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
                        printf("client socket error 2\n");
                        ::close(sock_fd);
                        sock_fd = -1;
                    }
                    else {
                        bRet = true;
                        _SocketFD = sock_fd;
                    }
                }

                return bRet;
            }

            bool ClientLinux::Disconnect() {

                if (_SocketFD >= 0) {
                    ::close(_SocketFD);
                    _SocketFD = -1;
                }

                return false;
            }

            bool ClientLinux::IsConnect() {

                bool bRet = false;

                if (_SocketFD >= 0) {
                    bRet = true;
                }

                return bRet;
            }

            bool ClientLinux::Receive(/*out*/ unsigned char* data, int maxBufSize, int* dataSize) {
            
                bool bRet = false;
                if (*dataSize) *dataSize = 0;

                ssize_t rdsz = ::read(_SocketFD, data, ((ssize_t)maxBufSize)&0xFFFF);
                if (rdsz > 0) {
                    if (dataSize) *dataSize = (int)rdsz;
                    bRet = true;
                }

                return bRet;
            }
            
            bool ClientLinux::Send(const unsigned char* data, int dataSize) {
            
                write(_SocketFD, data, dataSize);
                
                return true;
            }

            int ClientLinux::GetRcvSocketBufferByteSize() {

                int bufSize = 0;
                socklen_t len = sizeof(int);

                getsockopt(_SocketFD, SOL_SOCKET, SO_RCVBUF, &bufSize, &len);

                return bufSize;
            }

            int ClientLinux::GetSendSocketBufferByteSize() {

                int bufSize = 0;
                socklen_t len = sizeof(int);

                getsockopt(_SocketFD, SOL_SOCKET, SO_SNDBUF, &bufSize, &len);

                return bufSize;
            }


        }; //namespace TCP
    }; //namespace Socket {
}; // namespace Comm {

#endif //#if (CommOS==CommOS_WIN)

