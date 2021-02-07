#include <Comm/Socket/TCP/TCPClientWin.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
    namespace Socket {
        namespace TCP {

            ClientWin::ClientWin(const char* serverAddr, int portNum, int id) : Client(serverAddr, portNum, id) 
                , _Socket(INVALID_SOCKET)
            {
            
            }

            ClientWin::ClientWin(SOCKET sock, int id) : Client(NULL, 0, id)
                , _Socket(sock)
            {
            
            }
            
            ClientWin::~ClientWin() {

            }

            SOCKET ClientWin::Get_SOCKET() {
                return _Socket;
            }

            bool ClientWin::Connect() {
            
                WSADATA wsaData;
                int iResult;
                bool bRet = false;
                
                iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
                if (iResult != 0) {
                    printf("WSAStartup failed with error: %d\n", iResult);
                    return false;
                }

                _Socket = socket(AF_INET, SOCK_STREAM, 0);
                if (_Socket == INVALID_SOCKET) {
                    //printf("client socket error\n");
                }
                else {
                    struct sockaddr_in serv_addr;

                    memset(&serv_addr, 0, sizeof(serv_addr));
                    serv_addr.sin_family = AF_INET;
                    //serv_addr.sin_addr.s_addr = inet_addr(this->GetServerAddr());
                    inet_pton(AF_INET, this->GetServerAddr(), &serv_addr.sin_addr);
                    serv_addr.sin_port = htons((short)this->GetPortNum());

                    if (connect(_Socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
                        printf("client socket error 2\n");
                        ::closesocket(_Socket);
                        _Socket = INVALID_SOCKET;
                    }
                    else {
                        bRet = true;
                    }
                }

                return bRet;
            }
            
            bool ClientWin::Disconnect() {
            
                if (_Socket != INVALID_SOCKET) {
                    ::closesocket(_Socket);
                    _Socket = INVALID_SOCKET;
                }
                WSACleanup();

                return true;
            }

            bool ClientWin::IsConnect() {
            
                bool bRet = false;
                if (_Socket != INVALID_SOCKET) {
                    bRet = true;
                }
                return bRet;
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
            
            bool ClientWin::Send(const unsigned char* data, int dataByteSize) {
            
                int iSendResult;
                bool bRet = false;

                iSendResult = send(_Socket, (char*)data, dataByteSize, 0);
                if (iSendResult == SOCKET_ERROR) {
                    //printf("send failed with error: %d\n", WSAGetLastError());
                    //closesocket(ClientSocket);
                    //WSACleanup();
                    //return 1;
                    //bRet = true;
                }
                else if(iSendResult== dataByteSize){
                    bRet = true;
                }
                //printf("Bytes sent: %d\n", iSendResult

                return bRet;
            }

            int ClientWin::GetRcvSocketBufferByteSize() {

                return 0;
            }

            int ClientWin::GetSendSocketBufferByteSize() {

                return 0;
            }


        }; //namespace TCP
    }; //namespace Socket {
}; // namespace Comm {

#endif //#if (CommOS==CommOS_WIN)

