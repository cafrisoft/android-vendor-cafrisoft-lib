#include <Comm/OAL/Thread.hpp>
#include <Comm/OAL/ThreadWin.hpp>
#include <Comm/OAL/ThreadLinux.hpp>

namespace Comm {
namespace OAL {

    std::shared_ptr<Thread> Thread::CreateObject(ThreadServiceFuncType srvFunc, void* arg) {

        std::shared_ptr<Thread> obj;

#if (CommOS==CommOS_WIN)
        obj = std::make_shared<ThreadWin>(srvFunc, arg);

#elif (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)
        obj = std::make_shared<ThreadLinux>(srvFunc, arg);

#else
#error "Select OS"
#endif
        assert(obj);

        return obj;
    }


    Thread::Thread(ThreadServiceFuncType srvFunc, void* arg) :
        _SrvFunc(srvFunc)
        ,_Arg0(arg)
    {
    
    }

    Thread::~Thread() {
    
    }


}; //end of namespace OAL
}; //end of namespace Comm
