#define CLOG_TAG "UDPClientLinux"
#include <Comm/Socket/UDP/UDPClientLinux.hpp>
#include <Comm/OAL/Log.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

namespace Comm {
    namespace Socket {
        namespace UDP {

            ClientLinux::ClientLinux(const char* serverAddr, int portNum) : Client(serverAddr, portNum)
                , _SocketFD(-1)
            {
            
            }

            
            ClientLinux::~ClientLinux() {

            }

            bool ClientLinux::Open() {

                bool bRet = false;
                int sock_fd;

                sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
                if (sock_fd < 0) {
                    //printf("client socket error\n");
                    CLOGD("FAIL: Udp Socket Open");
                }
                else {
                    _SocketFD = sock_fd;
                    bRet = true;

                    CLOGD("OK: Udp Socket Open  (Port=%d)", _SocketFD);
                }

                return bRet;
            }

            bool ClientLinux::Close() {

                if (_SocketFD >= 0) {
                    ::close(_SocketFD);
                    

                    CLOGD("Udp Socket Close  (Port=%d)", _SocketFD);
                    _SocketFD = -1;
                }

                return false;
            }

            bool ClientLinux::Receive(/*out*/ unsigned char* data, int maxBufSize, int* dataSize) {
            
                ssize_t rdsz;
                struct sockaddr_in echoClntAddr; /* Client address */
                socklen_t cliLen = sizeof(echoClntAddr);
                bool bRet = false;

                if (dataSize) *dataSize = 0;

                if ((rdsz = recvfrom(_SocketFD, (char*)data, maxBufSize, 0, (struct sockaddr*)&echoClntAddr, &cliLen)) < 0) {
                    //DieWithError("recvfrom() failed");
                }
                else {
                    if (dataSize) *dataSize = (int)rdsz;
                    bRet = true;
                }

                return bRet;
            }
            
            bool ClientLinux::Send(const unsigned char* data, int dataSize) {
            
                ssize_t iSendResult;
                bool bRet = false;

                struct sockaddr_in servAddr;

                memset(&servAddr, 0, sizeof(servAddr));
                servAddr.sin_family = AF_INET;
                inet_pton(AF_INET, this->GetServerAddr(), &servAddr.sin_addr);
                short portNum = (short)this->GetPortNum();
                servAddr.sin_port = htons(portNum);

                iSendResult = ::sendto(_SocketFD, (char*)data, dataSize, 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
                if (iSendResult > 0) {
                    bRet = true;
                }

                return bRet;

            }

        }; //namespace UDP
    }; //namespace Socket {
}; // namespace Comm {

#endif //#if (CommOS==CommOS_WIN)

