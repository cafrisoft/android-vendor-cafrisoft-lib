#define CLOG_TAG "CommSocketUDPServerWin"
#include <Comm/Socket/UDP/UDPServerWin.hpp>
#include <Comm/Socket/UDP/UDPClientWin.hpp>

#if (CommOS==CommOS_WIN)

/*
Reference Code : 
https://makefile.tistory.com/entry/%EA%B0%84%EB%8B%A8%ED%95%9C-udp-%EC%84%9C%EB%B2%84-%EC%98%88%EC%A0%9C
*/

#include <ws2tcpip.h>

#define DEFAULT_BUFLEN  512

namespace Comm {
    namespace Socket {
        namespace UDP {


            ServerWin::ServerWin(struct CreateConfig cfg) : Server(cfg)
                , _ListenSocket(INVALID_SOCKET)
            {

            }

            ServerWin::~ServerWin() {

                this->Close();
            }

            bool ServerWin::Open() {

                WSADATA wsaData;
                int iResult;

                // Initialize Winsock
                iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
                if (iResult != 0) {
                    printf("WSAStartup failed with error: %d\n", iResult);
                    return false;
                }

                // Create a SOCKET for connecting to server
                _ListenSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
                if (_ListenSocket == INVALID_SOCKET) {
                    printf("socket failed with error: %ld\n", WSAGetLastError());
                    return false;
                }

                struct sockaddr_in servAddr;
                memset(&servAddr, 0, sizeof(servAddr));
                servAddr.sin_family = AF_INET;
                servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
                short portNum = (short)this->GetPortNum();
                servAddr.sin_port = htons(portNum);

                // Setup the UDP listening socket
                iResult = bind(_ListenSocket, (struct sockaddr*)&servAddr, sizeof(servAddr));
                if (iResult == SOCKET_ERROR) {
                    printf("bind failed with error: %d\n", WSAGetLastError());
                    return false;
                }

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

            bool ServerWin::ReceiveData(/*OUT*/unsigned char* data, int maxBufSize, /*OUT*/int* dataSize) {

                int rdsz;
                struct sockaddr_in echoClntAddr; /* Client address */
                int cliLen = sizeof(echoClntAddr);
                bool bRet = false;

                if (dataSize) *dataSize = 0;

                if ((rdsz = recvfrom(_ListenSocket, (char*)data, maxBufSize, 0, (struct sockaddr*)&echoClntAddr, &cliLen)) < 0) {
                    //DieWithError("recvfrom() failed");
                }
                else {
                    if (dataSize) *dataSize = rdsz;
                    bRet = true;
                }

                return bRet;
            }

            int ServerWin::GetRcvSocketBufferByteSize() {

                return 0;
            }

            int ServerWin::GetSendSocketBufferByteSize() {
            
                return 0;
            }
        

            void Server::CheckSocketBuffer() {

                CLOGI("Window UDPServer CheckSocketBuffer");
            }

        }; //namespace UDP
    }; //namespace Socket {
}; // namespace Comm {

#endif //#if (CommOS==CommOS_WIN)