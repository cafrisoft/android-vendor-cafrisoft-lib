#ifndef APPOPERATOR_HUB_STATUS
#define APPOPERATOR_HUB_STATUS

#include <Comm/OAL/ThreadService.hpp>

namespace TESysOperator {

    class HubStatus : public Comm::OAL::IThreadService  {

    private:
        std::shared_ptr<TESys::Control::Operator> _Operator;

        std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;
        void* _DataConsumerHubHandle;
        
        struct TESys::Data::Status::Hub _LatestHubStatus;
        bool _IsServiceRun;

    public:
        HubStatus(std::shared_ptr<TESys::Control::Operator> oper);
        ~HubStatus();

    private:
        virtual void Service();
        virtual void WaitForNextService();
        virtual bool IsServiceRun();

    public:
        void DisplayStatus();
    };

};


#endif
