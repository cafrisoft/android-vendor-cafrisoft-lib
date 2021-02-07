#include "Notifier.hpp"
#include <TESys/Property/Tester.hpp>
#include <TESys/Property/Net.hpp>

namespace TESysControlHub {

    Notifier::Tester::Tester(Notifier* notifier) :
    
        _Notifier(notifier)
        , _IsServiceRun(true)
        , _StartMonitorTick(Comm::OAL::System::GetTickCount32())
        , _BeforeMonitorTick(Comm::OAL::System::GetTickCount32())
        , _RcvPacketByteSizePerSec(0)
        , _N_THO_BroadCast_PacketByteSizePerSec(0)
    {
    
        /*
            Tester Notify UDP ¨ù¡©©öo ¨ùOAI ¡íy¨ù¨¬
        */
        struct Socket::UDP::Server::CreateConfig  crateConfig = {
            TESys::Property::Net::GetHubNotifierTesterUdpPort(),
            TESys::Net::PacketControl::GetFixedPacketByteSize(),
            TESys::Property::Tester::Board::GetAvailMaxCount()
        };

        _SrvUdpSock = Socket::UDP::Server::CreateObject(crateConfig);
        assert(_SrvUdpSock);
        //_SrvUdpSock->ServiceStart();

        CLOGI("[Notifier::Tetser] UDPServerSocket Create ... OK (Port=%d)", _SrvUdpSock->GetPortNum());

        //ThreadService Start
        _ThreadService = std::make_shared<OAL::ThreadService>(this);
        assert(_ThreadService);
    }

    Notifier::Tester::~Tester() {

        int udpServerPortNum = _SrvUdpSock->GetPortNum();
        /*
          Exit Step.
            Step1.  ServiceRun Flag set FALSE
            Step2.  UDP Server Socket Instance Destroy
            Step3.  Service Thread Instance Destroy
        */
        _IsServiceRun = false;

        _SrvUdpSock.reset();
        CLOGI("[Notifier::Tetser] UDPServerSocket(port=%d) Destroy", udpServerPortNum);

        _ThreadService.reset();
        CLOGI("[Notifier::Tetser] ThreadService Destroy");
    }

    void Notifier::Tester::Service() {
    
        int command;
        int rdsz = -1;
        
        //_SrvUdpSock->ServiceReadData(_RcvRawData, TESys::Net::PacketControl::GetFixedPacketByteSize(), &rdsz);
        _SrvUdpSock->ReceiveData(_RcvRawData, TESys::Net::PacketControl::GetFixedPacketByteSize(), &rdsz);
        if (rdsz == TESys::Net::PacketControl::GetFixedPacketByteSize()) {

            unsigned int curTick = Comm::OAL::System::GetTickCount32();
            std::shared_ptr<TESys::Net::PacketControl> notifyPack = std::make_shared<TESys::Net::PacketControl>(_RcvRawData);
            command = (int)notifyPack->GetCommand();

            if ((command > (int)TESys::Net::Command::Control::N_THO_BEGIN) 
                && (command < (int)TESys::Net::Command::Control::N_THO_END)) {
            
                _Notifier->GetOperator()->BroadCast(notifyPack);

                _N_THO_BroadCast_PacketByteSizePerSec += notifyPack->GetByteSize();
                                
#if 0
                CLOGD("[Notifier::Tester %s:%d]  N_THO_TESTER_STATUS  BoardID(%d)  DealyTime(%d)",
                    OAL::DateTime::GetKstTimeString().c_str(),
                    OAL::System::GetTickCount32() % 1000,
                    notifyPack->GetInt(0),
                    (int)(Comm::OAL::DateTime::GetUtcTime() - notifyPack->GetUtcTime()));
#endif
            }
            else if ((command > (int)TESys::Net::Command::Control::C_OHT_THO_BEGIN)
                && (command < (int)TESys::Net::Command::Control::C_OHT_THO_END)) {

                _Notifier->GetOperator()->BroadCast(notifyPack);
                _N_THO_BroadCast_PacketByteSizePerSec += notifyPack->GetByteSize();
            }

            _RcvPacketByteSizePerSec += rdsz;
            if ((curTick - _BeforeMonitorTick) > 1000) {
                CLOGI("[Notifier::Tester] Total:%d N_THO_BCast:%d", _RcvPacketByteSizePerSec, _N_THO_BroadCast_PacketByteSizePerSec);
                
                _BeforeMonitorTick = curTick;
                _RcvPacketByteSizePerSec = 0;
                _N_THO_BroadCast_PacketByteSizePerSec = 0;
            }
            
        }
        
    }

    void Notifier::Tester::WaitForNextService() {
    
    }

    bool Notifier::Tester::IsServiceRun() {

        return _IsServiceRun;
    }
    
    
    
};
