#ifndef COMM_OAL_THREADSERVICE_HPP__
#define COMM_OAL_THREADSERVICE_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/OAL/Thread.hpp>

namespace Comm {
namespace OAL {

    class IThreadService : public Comm::Base::Object {

    protected:
        long long _TotalReceivedPacketCount;
        long long _ReceivedPacketCount;

    public:
        IThreadService();
        virtual ~IThreadService();

    public:
        virtual void Service() = 0;
        virtual void WaitForNextService() = 0;
        virtual bool IsServiceRun() = 0;

    public:
        long long GetTotalReceivedPacketCount();
        long long GetReceivedPacketCount();
        void ResetReceivedPacketCount();
    };

    class ThreadService {

    private:
        std::shared_ptr<Thread> _Thread;
        IThreadService* _IThreadService;
        bool _IsExit;

    private:
        static void ServiceStub(void* param);

    public:
        ThreadService(IThreadService* pService);
        virtual ~ThreadService();

        bool IsRun();
    };


}; //end of namespace OAL
}; //end of namespace Comm


#endif // #ifndef COMM_OAL_THREADSERVICE_HPP__


