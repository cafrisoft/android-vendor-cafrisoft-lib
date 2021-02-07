//#include "AppGlobal.hpp"
#include "CommanderAgent.hpp"
#include "Notifier.hpp"
#include <TESys/Data/Status.hpp>
#include <TESys/Property/Hub.hpp>
#include <TESys/Net/PacketControl.hpp>

static bool s_IsAppRun = true;

static void NotifyStatus() {

    TESys::Data::Status::Hub st;
    
    st.NotifyUtcTime = Comm::OAL::DateTime::GetUtcTime();
    
    st.CalCRCApp.AppStatus = (int)TESys::Property::Hub::FtpServer::GetHubCalCRCAppStatus();
    //printf("st.CalCRCApp.AppStatus=%d %s \n", st.CalCRCApp.AppStatus, TESys::Property::Hub::FtpServer::GetHubCalCRCAppStatusString((TESys::Property::Hub::FtpServer::HubCalCRCAppStatus)st.CalCRCApp.AppStatus).c_str());
    st.CalCRCApp.FtpStorageLatestCRC = TESys::Property::Hub::FtpServer::GetFtpStorageLatestCRC();
    st.CalCRCApp.FtpStorageCurCalculatedCRCByteSize = TESys::Property::Hub::FtpServer::GetFtpStorageCurCalculatedCRCByteSize();
    st.CalCRCApp.FtpStorageTotalFileByteSize = TESys::Property::Hub::FtpServer::GetFtpStorageTotalFileByteSize();
    
    TESys::Net::Command::Control command = TESys::Net::Command::Control::N_HO_HUB_STATUS;
    std::shared_ptr<TESys::Net::PacketControl> notifyPack = std::make_shared<TESys::Net::PacketControl>();
    assert(notifyPack);

    assert(sizeof(st) <= TESys::Net::PacketControl::GetMaxDataByteSize());

    notifyPack->SetCommand(command);
    notifyPack->SetInt(0, sizeof(st));
    notifyPack->SetData((const unsigned char*)&st, sizeof(st));
    notifyPack->GenCRC();

    TESysControlHub::Notifier::Inst()->BoardCastToOperator(notifyPack);
    
}

void sig_handler(int signo) {
    CLOGI("Received Kill Signal");
    s_IsAppRun = false;
}

int main(int argc, char* argv[]) {

#if (CommOS == CommOS_LINUX)
    signal(SIGINT, sig_handler);
#endif

    OAL::Log::SysLogOpen(CLOG_TAG);
    OAL::Log::EnableDebug();

    //TESysControlHub::AppGlobal::Init();

    /*
        Notifyer 생성 
          Mission1. Tester가 송신하는 NotifyPacket을  Operator로 전달
          Mission2. Hub가 송신하는 NotifyPacket을 Operator로 전달 
    */
    TESysControlHub::Notifier::Init();

    /*
        명령 수신자.
           Operator가 송신하는 명령을  처리하는 역할
           Operator는 1명만 가능하므로, 2명이 접속을 시도하면, 접속을 불허한다. 
    */
    TESysControlHub::CommanderAgent::Init();

#if (CommOS==CommOS_WIN)
    OAL::Thread::Sleep(2000);
    s_IsAppRun = false;
#endif

    while (s_IsAppRun) {

        OAL::Thread::Sleep(1000);

	    NotifyStatus();
    }

    TESysControlHub::CommanderAgent::Deinit();
    TESysControlHub::Notifier::Deinit();

    CLOGI("Hub destry...");

    OAL::Log::SysLogClose();

    

    return 0;
}




