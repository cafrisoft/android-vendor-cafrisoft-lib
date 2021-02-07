#include "Notifier.hpp"
#include <TESys/Property/Tester.hpp>
#include <TESys/Property/Net.hpp>

namespace TESysDataAcq {

    Notifier::Tester::Tester(Notifier* notifier) :
    
        _Notifier(notifier)
        , _StartMonitorTick(Comm::OAL::System::GetTickCount32())
        , _BeforeMonitorTick(Comm::OAL::System::GetTickCount32())
        , _RcvPacketByteSizePerSec(0)
    {
    
        /*
            Tester Notify UDP Socket Create
        */
        struct Comm::Socket::UDP::Server::CreateConfig  crateConfig = {
            TESys::Property::Net::GetDataAcqUdpPort(),
            TESys::Net::PacketDataAcq::GetFixedPacketByteSize(),
            TESys::Property::Tester::Board::GetAvailMaxCount()
        };

        _SrvUdpSock = Comm::Socket::UDP::Server::CreateObject(crateConfig);
        assert(_SrvUdpSock);
        //_SrvUdpSock->ServiceStart();

        CLOGI("[Notifier::Tetser] UDPServerSocket Create ... OK (Port=%d  RcvBuf=%d SendBuf=%d)", _SrvUdpSock->GetPortNum(), _SrvUdpSock->GetRcvSocketBufferByteSize(), _SrvUdpSock->GetSendSocketBufferByteSize());

        //ThreadService Start
        _ThreadService = std::make_shared<Comm::OAL::ThreadService>(this);
        assert(_ThreadService);
    }

    void Notifier::Tester::Service() {
    
        int command;
        int rdsz;
        
        //_SrvUdpSock->ServiceReadData(_RcvRawData, TESys::Net::PacketDataAcq::GetFixedPacketByteSize(), &rdsz);
        _SrvUdpSock->ReceiveData(_RcvRawData, TESys::Net::PacketDataAcq::GetFixedPacketByteSize(), &rdsz);
        if (rdsz == TESys::Net::PacketDataAcq::GetFixedPacketByteSize()) {

            unsigned int curTick = Comm::OAL::System::GetTickCount32();
            std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack = std::make_shared<TESys::Net::PacketDataAcq>(_RcvRawData);
            command = (int)notifyPack->GetCommand();

            _Notifier->GetTCPServer()->BroadCast(notifyPack);
            _Notifier->GetRawDataSaver()->BroadCast(notifyPack);
            _Notifier->GetAgingMonitor()->BroadCast(notifyPack);
            

            _RcvPacketByteSizePerSec += rdsz;
            if ((curTick - _BeforeMonitorTick) > 1000) {
                CLOGI("[Notifier::Tester] Total:%d ", _RcvPacketByteSizePerSec );
                
                _BeforeMonitorTick = curTick;
                _RcvPacketByteSizePerSec = 0;
            }
            
        }
        
    }

    void Notifier::Tester::WaitForNextService() {
    
    }

    bool Notifier::Tester::IsServiceRun() {

        return true;
    }
    
    
    
};
