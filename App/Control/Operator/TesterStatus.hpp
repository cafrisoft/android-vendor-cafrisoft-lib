#ifndef APPOPERATOR_TESTER_STATUS
#define APPOPERATOR_TESTER_STATUS

#include <Comm/OAL/ThreadService.hpp>

namespace TESysOperator {

    class TesterStatus : public Comm::OAL::IThreadService  {

    private:
        std::shared_ptr<TESys::Control::Operator> _Operator;

        std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;
        void* _DataConsumerTesterHandle;

        struct TESys::API::PacketTesterStatusArray _PacketTesterStatusArray;

        int _MaxBoardID;
        struct TESys::Data::Status::Tester* _TesterStatus;

        bool _IsServiceRun;

    public:
        TesterStatus(std::shared_ptr<TESys::Control::Operator> oper, int maxBoardID=10);
        ~TesterStatus();

    private:
        virtual void Service();
        virtual void WaitForNextService();
        virtual bool IsServiceRun();

    public:
        void DisplayStatus(int boardID);
    };

};


#endif
