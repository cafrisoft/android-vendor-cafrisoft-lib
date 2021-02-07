#ifndef COMM_OAL_THREAD_HPP__
#define COMM_OAL_THREAD_HPP__

#include <Comm/Base/Object.hpp>

namespace Comm {
namespace OAL {

    class Thread : public Base::Object {

    public:
        static std::shared_ptr<Thread> CreateObject(ThreadServiceFuncType srvFunc, void* arg);

    private:
        ThreadServiceFuncType _SrvFunc;
        void* _Arg0;

    protected:
        Thread(ThreadServiceFuncType srvFunc, void* arg);
        virtual ~Thread();

    public:
        static void Sleep(int miliSec);
    };

    
}; //end of namespace OAL
}; //end of namespace Comm

#endif // #ifndef TESYSNETCLIENT_HPP

