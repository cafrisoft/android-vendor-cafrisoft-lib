#include "Notifier.hpp"
#include <TESys/Property/Hub.hpp>
#include <TESys/Property/Net.hpp>

namespace TESysDataAcq {

    Notifier::TCPServer::TCPServer(Notifier* notifier) :
    
        _Notifier(notifier)
    {
        //Packet Queue¡íy¨ù¨¬
        _PacketQueue = std::make_shared<Comm::Utils::SyncQueue<std::shared_ptr<TESys::Net::PacketDataAcq>>>();
        assert(_PacketQueue);
        CLOGI("[Notifier::TCPServer] PacketQueue Create ... OK");

        /*
            TCPServer Notify TCP ¨ù¡©©öo ¨ùOAI ¡íy¨ù¨¬
        */
        struct Comm::Socket::TCP::Server::CreateConfig  createConfig = {
            TESys::Property::Net::GetDataAcqTcpPort(),
            TESys::Net::PacketDataAcq::GetFixedPacketByteSize(),
            TESys::Property::DataAcq::GetMaxSaverCount(),
            Notifier::TCPServer::CallbackAcceptStub,
            Notifier::TCPServer::CallbackReceiveStub,
            Notifier::TCPServer::CallbackCloseStub,
            this
        };

        _SrvTcpSock = Comm::Socket::TCP::Server::CreateObject(createConfig);
        assert(_SrvTcpSock);

        _SrvTcpSock->SelectLoop(true);
        CLOGI("[Notifier::TCPServer] TCPServerSocket Create ... OK (Port=%d)", _SrvTcpSock->GetPortNum());


        //ThreadService Start
        _ThreadService = std::make_shared<Comm::OAL::ThreadService>(this);
        assert(_ThreadService);
    }

    bool Notifier::TCPServer::BroadCast(std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack) {
    
        _PacketQueue->Push(notifyPack);
        return true;
    }


    void Notifier::TCPServer::CallbackAcceptStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> client) {
        Notifier::TCPServer* pObj = (Notifier::TCPServer*)arg;
        pObj->CallbackAccept(client);
    }

    void Notifier::TCPServer::CallbackReceiveStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> client, const unsigned char* data, int dataSize) {
        Notifier::TCPServer* pObj = (Notifier::TCPServer*)arg;
        pObj->CallbackReceive(client, data, dataSize);
    }

    void Notifier::TCPServer::CallbackCloseStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> client) {
        Notifier::TCPServer* pObj = (Notifier::TCPServer*)arg;
        pObj->CallbackClose(client);
    }

    void Notifier::TCPServer::CallbackAccept(std::shared_ptr<Comm::Socket::TCP::Client> client) {
    
        CLOGI("[Notifier::TCPServer] Accept from DataAcqTCPServer (ID-%d RcvBuf=%d SendBuf=%d)", client->GetID(), client->GetRcvSocketBufferByteSize(), client->GetSendSocketBufferByteSize());
    }

    void Notifier::TCPServer::CallbackReceive(std::shared_ptr<Comm::Socket::TCP::Client> client, const unsigned char* data, int dataSize) {
    
    }

    void Notifier::TCPServer::CallbackClose(std::shared_ptr<Comm::Socket::TCP::Client> client) {
    
    }

    void Notifier::TCPServer::Service() {
    
        std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack = _PacketQueue->Pop();
        if (notifyPack != NULL) {

            _SrvTcpSock->Broadcast(notifyPack);

#if 0
            switch (notifyPack->GetCommand()) {
            case TESys::Net::Command::Control::N_THO_TESTER_STATUS:
            {
#if 0
                int boardID = notifyPack->GetInt(0);
                CLOGD("[Notifier::TCPServer %s:%d]  N_THO_TESTER_STATUS  BoardID(%d)  DealyTime(%d)", 
                               OAL::DateTime::GetKstTimeString().c_str(), 
                               OAL::System::GetTickCount32()%1000, 
                                boardID,
                                (int)(Comm::OAL::DateTime::GetUtcTime() - notifyPack->GetUtcTime())
                              );
#endif
                break;
            }
            }
#endif

        }
    }

    void Notifier::TCPServer::WaitForNextService() {
    
    }

    bool Notifier::TCPServer::IsServiceRun() {
        return true;
    }

    
    
    
};
