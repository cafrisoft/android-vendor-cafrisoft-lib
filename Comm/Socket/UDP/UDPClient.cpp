#include <Comm/Socket/UDP/UDPClient.hpp>
#include <Comm/Socket/UDP/UDPClientWin.hpp>
#include <Comm/Socket/UDP/UDPClientLinux.hpp>
#include <Comm/OAL/Lock.hpp>

namespace Comm {
    namespace Socket {
        namespace UDP {

            std::shared_ptr<Client> Client::CreateObject(std::string serverAddr, int portNum) {

                std::shared_ptr<Client> obj;
#if (CommOS==CommOS_WIN)
                obj = std::make_shared<ClientWin>(serverAddr.c_str(), portNum);
#elif (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)
                obj = std::make_shared<ClientLinux>(serverAddr.c_str(), portNum);
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


            Client::Client(const char* serverAddr, int portNum, int id) :
                _PortNum(portNum)
                ,_ID(id)
            {
                if (serverAddr != NULL) {
                    strcpy(_ServerAddr, serverAddr);
                }
                else {
                    strcpy(_ServerAddr, "0.0.0.0");
                }

                _CriticalSectionSendData = OAL::CriticalSection::CreateObject();
                assert(_CriticalSectionSendData);
            }
            
            Client::~Client() {

            }

            int Client::GetID() {
                return _ID;
            }

            int Client::GetPortNum() {
                return _PortNum;
            }

            const char* Client::GetServerAddr() {
            
                strcpy(_ServerAddrBuff, _ServerAddr);
                return (const char* )_ServerAddrBuff;
            }

            bool Client::Send(std::shared_ptr<NetPacket> pack) {
            
                OAL::Lock lock(_CriticalSectionSendData);

                bool bRet;
                int packByteSize = pack->GetBufByteSize();
                unsigned char* packData = new unsigned char[packByteSize];
                assert(packData);

                pack->GetNetPacketData(packData);
                bRet = this->Send(packData, packByteSize);

                delete[] packData;

                return bRet;
            }

        }; //namespace UDP
    }; //namespace Socket {
}; // namespace Comm {

