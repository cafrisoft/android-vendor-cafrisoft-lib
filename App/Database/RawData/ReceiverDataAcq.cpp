#define CLOG_TAG SYSLOG_NAME
#include "Receiver.hpp"
#include <TESys/Property/DataAcq.hpp>
#include <TESys/Property/Net.hpp>
#include <Comm/Utils/Android.hpp>

namespace TESysDBRawData {

    Receiver::DataAcq::DataAcq(Receiver* notifier) :
    
        _Receiver(notifier)
        , _StartMonitorTick(Comm::OAL::System::GetTickCount32())
        , _BeforeMonitorTick(Comm::OAL::System::GetTickCount32())
        , _RcvPacketByteSizePerSec(0)
    {
    
        unsigned int intIP = Comm::Utils::Android::GetIpAddrI32("eth0");


        if (intIP == 0x78A2EFCD)  //205.239.162.120
        {
            _CliSock = Comm::Socket::TCP::Client::CreateObject("127.0.0.1", TESys::Property::Net::GetDataAcqTcpPort());
        }
        else {
            _CliSock = Comm::Socket::TCP::Client::CreateObject(TESys::Property::Net::GetLinuxServerMachGlobalIPAddr().c_str(), TESys::Property::Net::GetDataAcqTcpPort());
        }
        assert(_CliSock);

        _ThreadService = std::make_shared<Comm::OAL::ThreadService>(this);
        assert(_ThreadService);
    }

    void Receiver::DataAcq::Service() {
    
        bool bRet;

        CLOGI("Connecting.. %s:%d", _CliSock->GetServerAddr(), _CliSock->GetPortNum());
        bRet = _CliSock->Connect();
        if (bRet) {
            CLOGI("OK : connect %s:%d  RcvBuf=%d SendBuf=%d", _CliSock->GetServerAddr(), _CliSock->GetPortNum(), _CliSock->GetRcvSocketBufferByteSize(), _CliSock->GetSendSocketBufferByteSize());
            while (bRet) {

                std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack = std::make_shared<TESys::Net::PacketDataAcq>();
                assert(rcvPack);

                bool bRet = _CliSock->ReceiveSync(_RcvRawData, rcvPack->GetByteSize());
                if (bRet) {
                    bRet = rcvPack->SetNetPacketData(_RcvRawData, rcvPack->GetByteSize());
                }
                
                if (!bRet) {
                    CLOGI("Socket Abort (%s:%d)", _CliSock->GetServerAddr(), _CliSock->GetPortNum());
                    break;
                }
                else {
                    _Receiver->GetRawDataSaver()->BroadCast(rcvPack);
                    _Receiver->GetExportCSV()->BroadCast(rcvPack);
                }

            } //end of while (bRet) {
            _CliSock->Disconnect();
        }
        
        
    }

    void Receiver::DataAcq::WaitForNextService() {
    
        Comm::OAL::Thread::Sleep(3000);
    }

    bool Receiver::DataAcq::IsServiceRun() {

        return true;
    }
    
    
    
};
