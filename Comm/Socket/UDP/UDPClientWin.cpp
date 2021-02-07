#include <Comm/Socket/UDP/UDPClientWin.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
    namespace Socket {
        namespace UDP {

            ClientWin::ClientWin(const char* serverAddr, int portNum, int id) : Client(serverAddr, portNum, id) 
                , _Socket(INVALID_SOCKET)
            {
            
            }

            
            ClientWin::~ClientWin() {

                this->Close();
            }

            bool ClientWin::Open() {
            
                WSADATA wsaData;
                
                if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
                {
                    fprintf(stderr, "WSAStartup() failed");
                    assert(1);
                }

                if ((_Socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
                {
                    fprintf(stderr, "socket() failed");
                    WSACleanup();
                    assert(1);
                }

                return true;
            }

            bool ClientWin::Close() {
            
                if (_Socket != INVALID_SOCKET) {
                    closesocket(_Socket);
                    _Socket = INVALID_SOCKET;
                }
                WSACleanup();

                return true;
            }


            bool ClientWin::Receive(/*out*/ unsigned char* data, int maxBufSize, int* dataSize) {
            
                int iResult;
                bool bRet = false;

                if (dataSize) *dataSize = 0;

                iResult = recv(_Socket, (char*)data, maxBufSize, 0);
                if (iResult > 0) {
                    //printf("Bytes received: %d\n", iResult);
                    if (dataSize) *dataSize = iResult;
                    bRet = true;
                }

                return bRet;
            }
            
            bool ClientWin::Send(const unsigned char* data, int dataSize) {
            
                int iSendResult;
                bool bRet = false;

                struct sockaddr_in servAddr;

                memset(&servAddr, 0, sizeof(servAddr));
                servAddr.sin_family = AF_INET;
                inet_pton(AF_INET, this->GetServerAddr(), &servAddr.sin_addr);
                servAddr.sin_port = htons(this->GetPortNum());

                iSendResult = ::sendto(_Socket, (char*)data, dataSize, 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
                if (iSendResult > 0) {
                    bRet = true;
                }

                return bRet;
            }

        }; //namespace UDP
    }; //namespace Socket {
}; // namespace Comm {

#endif //#if (CommOS==CommOS_WIN)

