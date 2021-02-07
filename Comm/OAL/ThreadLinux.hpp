#ifndef TESYSOALThreadLinux_HPP
#define TESYSOALThreadLinux_HPP

#include <Comm/OAL/Thread.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

namespace Comm {
namespace OAL {

    class ThreadLinux : public Thread {

    private:
        pthread_t m_task_hdl;

    public:
        ThreadLinux(ThreadServiceFuncType srvFunc, void* arg);
        virtual ~ThreadLinux();
                
    };

}; //end of namespace Net
}; //end of namespace Comm


#endif //#if (TESYSOS==TESYSOS_ANDROID)
#endif // #ifndef TESYSNETCLIENT_HPP

