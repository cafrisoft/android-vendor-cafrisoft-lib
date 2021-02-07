#include <Comm/Socket/TCP/TCPServer.hpp>
#include <Comm/Socket/TCP/TCPServerWin.hpp>
#include <Comm/Socket/TCP/TCPServerLinux.hpp>

namespace Comm {
    namespace Socket {
        namespace TCP {

            std::shared_ptr<Server> Server::CreateObject(struct CreateConfig cfg) {
            
                std::shared_ptr<Server> obj;
#if (CommOS==CommOS_WIN)
                obj = std::make_shared<ServerWin>(cfg);
#elif (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)
                obj = std::make_shared<ServerLinux>(cfg);
#else
                #error "OS is not defined"
#endif
                assert(obj);

                if (!obj->Open()) {
                    obj->Close();
                    obj.reset();
                }

                return obj;
            }

            Server::Server(struct CreateConfig cfg) 
            {
                memcpy(&_CreateConfig, &cfg, sizeof(cfg));
                _LogTimer = OAL::Timer::CreateObject(this, TimerID::Log, 1000/*tick*/, false/*defaultStart*/);

                _ServerStartTick = OAL::System::GetTickCount64();
            }

            Server::~Server() {

                _IsSelectThreadRun = false;
            
            }

            int Server::GetPortNum() {
                return _CreateConfig._PortNum;
            }

            int Server::GetReceiveBufByteSize() {
                return _CreateConfig._ReceiveBufSize;
            }

            int Server::GetMaxClientCount() {
                return _CreateConfig._MaxClientCount;
            }

            int Server::GetConnectedClientCount() {
            
                return (int)_ClientVector.size();
            }

            std::vector<int> Server::GetConnectedHubIDVector() {
            
                std::vector<int> vecID;

                for (std::vector<std::shared_ptr<Client>>::const_iterator it = _ClientVector.cbegin(); it != _ClientVector.cend(); ++it) {
                    std::shared_ptr<Client> cli = *it;
                    vecID.push_back(cli->GetID());
                }

                return vecID;
            }

            void Server::SelectAcceptCallback(std::shared_ptr<Client> cliSock) {

                if (_CreateConfig._AcceptFunc) {
                    _CreateConfig._AcceptFunc(_CreateConfig.arg, cliSock);
                }

                _ClientVector.push_back(cliSock);
            }


            void Server::SelectReceiveCallback(std::shared_ptr<Client> cliSock, const unsigned char* data, int dataSize) {

                if (_CreateConfig._ReceiveFunc) {
                    _CreateConfig._ReceiveFunc(_CreateConfig.arg, cliSock, data, dataSize);
                }
                //_ReceivedDataCount.Increase(dataSize, false);
                _ReceivedDataCount += dataSize;
            }   


            void Server::SelectCloseCallback(std::shared_ptr<Client> cliSock) {

                if (_CreateConfig._CloseFunc) {
                    _CreateConfig._CloseFunc(_CreateConfig.arg, cliSock);
                }


                for (std::vector<std::shared_ptr<Client>>::iterator it = _ClientVector.begin(); it != _ClientVector.end(); ++it) {
                    std::shared_ptr<Client> cli = *it;
                    if (cli->GetID() == cliSock->GetID()) {
                        _ClientVector.erase(it);
                        break;
                    }
                }
            }

            void Server::SelectLoop(bool isInternalThreadRun) {

                if (isInternalThreadRun) {
                
                    _IsSelectThreadRun = true;
                    _SelectThread = OAL::Thread::CreateObject(Server::SelectServiceStub, this);
                }
                else {
                    while (true) {
                        this->Select();
                    }
                }
            }

            void Server::SelectServiceStub(void* arg) {
                Server* pObj = (Server*)arg;
                pObj->SelectService();
            }

            void Server::SelectService() {
                while (_IsSelectThreadRun) {
                    this->Select();
                }
            }

            void Server::LogStart() {
                _LogTimer->Start();
            }

            void Server::LogStop() {
                _LogTimer->Stop();
            }

            void Server::EventTimerCallbackLog() {

                long long curTick = OAL::System::GetTickCount64();

                PRINTF("[TCPServer Log] %lld. RcvData=%d ",  (curTick-_ServerStartTick)/1000LL, _ReceivedDataCount.GetCount());
                _ReceivedDataCount.Reset();
            }

            bool Server::Broadcast(const unsigned char* data, int dataSize) {
            
                for (std::vector<std::shared_ptr<Client>>::const_iterator it = _ClientVector.cbegin(); it != _ClientVector.cend(); ++it) {
                    std::shared_ptr<Client> cli = *it;
                    cli->Send(data, dataSize);
                }

                return true;
            }

            bool Server::Broadcast(std::shared_ptr<NetPacket> pack) {
            
                bool bRet;
                int packByteSize = pack->GetByteSize();
                unsigned char* packData = new unsigned char[packByteSize];
                assert(packData);

                pack->GetNetPacketData(packData);
                bRet = this->Broadcast(packData, packByteSize);

                delete[] packData;

                return bRet;
            }
            
        }; //namespace TCP
    }; //namespace Socket {
}; // namespace Comm {

