#include "App.hpp"
#include "HubStatus.hpp"
#include <TESys/Property/FileSync.hpp>

namespace TESysOperator {

    HubStatus::HubStatus(std::shared_ptr<TESys::Control::Operator> oper) :
        _Operator(oper)
        , _IsServiceRun(true)
    {

        memset(&_LatestHubStatus, 0x00, sizeof(_LatestHubStatus));

        _DataConsumerHubHandle = _Operator->DataConsumerHubStatusCreate();
        assert(_DataConsumerHubHandle);

        _ThreadService = std::make_shared<Comm::OAL::ThreadService>(this);
        assert(_ThreadService);
    }

    HubStatus::~HubStatus() {
        
        _IsServiceRun = false;

        _ThreadService.reset();
        _Operator->DataConsumerHubStatusDestroy(_DataConsumerHubHandle);

    }
    
    void HubStatus::Service() {
        //PRINTF("[%s] ln=%d IN\n", __func__, __LINE__);
        _Operator->DataConsumerHubStatusGetApiData(_DataConsumerHubHandle , &_LatestHubStatus);
        //PRINTF("[%s] ln=%d OUT \n", __func__, __LINE__);
    }
    
    void HubStatus::WaitForNextService() {
    
        OAL::Thread::Sleep(1000);
    }
    
    bool HubStatus::IsServiceRun() {
        return _IsServiceRun;
    }

    void HubStatus::DisplayStatus() {
    
        if (_LatestHubStatus.NotifyUtcTime != 0) {

            float rate = 0.0f;
            
            if (_LatestHubStatus.CalCRCApp.FtpStorageTotalFileByteSize > 0) {
                rate = (float)(_LatestHubStatus.CalCRCApp.FtpStorageCurCalculatedCRCByteSize * 100LL) / (float)_LatestHubStatus.CalCRCApp.FtpStorageTotalFileByteSize;
            }

            PRINTF("%s %s %d/%d(%3.1f%c) CRC(%d) \n", 
                OAL::DateTime::GetKstTimeString(_LatestHubStatus.NotifyUtcTime).c_str(),
                TESys::Property::Hub::FtpServer::GetHubCalCRCAppStatusString((TESys::Property::Hub::FtpServer::HubCalCRCAppStatus)_LatestHubStatus.CalCRCApp.AppStatus).c_str(),

                _LatestHubStatus.CalCRCApp.FtpStorageCurCalculatedCRCByteSize,
                _LatestHubStatus.CalCRCApp.FtpStorageTotalFileByteSize,

                rate, '%',

                _LatestHubStatus.CalCRCApp.FtpStorageLatestCRC
            );

        }
        else {
            PRINTF("XXXXXXXXXXXXXXX \n");
        }


        
    }

};