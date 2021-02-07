#include "Notifier.hpp"
#include <TESys/Property/Hub.hpp>
#include <TESys/Property/Net.hpp>

namespace TESysControlHub {
    

    

    Notifier::Operator::Operator(Notifier* notifier) :
    
        _Notifier(notifier)
        , _IsServiceRun(true)
    {
        //Packet Queue¡íy¨ù¨¬
        _PacketQueue = std::make_shared<Comm::Utils::SyncQueue<std::shared_ptr<TESys::Net::PacketControl>>>();
        assert(_PacketQueue);
        CLOGI("[Notifier::Operator] PacketQueue Create ... OK");

        /*
            Operator Notify TCP ¨ù¡©©öo ¨ùOAI ¡íy¨ù¨¬
        */
        struct Socket::TCP::Server::CreateConfig  createConfig = {
            TESys::Property::Net::GetHubNotifierOperatorTcpPort(),
            TESys::Net::PacketControl::GetFixedPacketByteSize(),
            TESys::Property::Hub::GetMaxOperatorCount(),
            Notifier::Operator::CallbackAcceptStub,
            Notifier::Operator::CallbackReceiveStub,
            Notifier::Operator::CallbackCloseStub,
            this
        };

        _SrvTcpSock = Socket::TCP::Server::CreateObject(createConfig);
        assert(_SrvTcpSock);

        _SrvTcpSock->SelectLoop(true);
        CLOGI("[Notifier::Operator] TCPServerSocket Create ... OK (Port=%d)", _SrvTcpSock->GetPortNum());


        //ThreadService Start
        _ThreadService = std::make_shared<OAL::ThreadService>(this);
        assert(_ThreadService);
    }

    Notifier::Operator::~Operator() {
    
        int portNum = _SrvTcpSock->GetPortNum();

        /*
          Exit Step.
            Step1.  ServiceRun Flag set FALSE
            Step2.  input dummy packet to Service PacketQueue
            Step3.  Service Thread Instance Destroy

            Step4.  TCP Server Socket Instance Destroy
        */

        _IsServiceRun = false;
        _PacketQueue->Push(NULL);
        _ThreadService.reset();
        CLOGI("[Notifier::Operator] ThreadService Destroy");

        _SrvTcpSock.reset();
        CLOGI("[Notifier::Operator] TCPServerSocket(port=%d) Destroy", portNum);

    }

    bool Notifier::Operator::BroadCast(std::shared_ptr<TESys::Net::PacketControl> notifyPack) {
    
        _PacketQueue->Push(notifyPack);
        return true;
    }


    void Notifier::Operator::CallbackAcceptStub(void* arg, std::shared_ptr<Socket::TCP::Client> client) {
        Notifier::Operator* pObj = (Notifier::Operator*)arg;
        pObj->CallbackAccept(client);
    }

    void Notifier::Operator::CallbackReceiveStub(void* arg, std::shared_ptr<Socket::TCP::Client> client, const unsigned char* data, int dataSize) {
        Notifier::Operator* pObj = (Notifier::Operator*)arg;
        pObj->CallbackReceive(client, data, dataSize);
    }

    void Notifier::Operator::CallbackCloseStub(void* arg, std::shared_ptr<Socket::TCP::Client> client) {
        Notifier::Operator* pObj = (Notifier::Operator*)arg;
        pObj->CallbackClose(client);
    }

    void Notifier::Operator::CallbackAccept(std::shared_ptr<Socket::TCP::Client> client) {
    
    }

    void Notifier::Operator::CallbackReceive(std::shared_ptr<Socket::TCP::Client> client, const unsigned char* data, int dataSize) {
    
    }

    void Notifier::Operator::CallbackClose(std::shared_ptr<Socket::TCP::Client> client) {
    
    }

    void Notifier::Operator::Service() {
    
        std::shared_ptr<TESys::Net::PacketControl> notifyPack = _PacketQueue->Pop();
        if (notifyPack != NULL) {

            _SrvTcpSock->Broadcast(notifyPack);

            switch (notifyPack->GetCommand()) {
            case TESys::Net::Command::Control::N_THO_TESTER_STATUS:
            {
#if 0
                int boardID = notifyPack->GetInt(0);
                CLOGD("[Notifier::Operator %s:%d]  N_THO_TESTER_STATUS  BoardID(%d)  DealyTime(%d)", 
                               OAL::DateTime::GetKstTimeString().c_str(), 
                               OAL::System::GetTickCount32()%1000, 
                                boardID,
                                (int)(Comm::OAL::DateTime::GetUtcTime() - notifyPack->GetUtcTime())
                              );
#endif
                break;
            }
            }

        }
    }

    void Notifier::Operator::WaitForNextService() {
    
    }

    bool Notifier::Operator::IsServiceRun() {
        return _IsServiceRun;
    }

    
    
    
};
