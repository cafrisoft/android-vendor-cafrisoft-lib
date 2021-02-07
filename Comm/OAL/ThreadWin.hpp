#ifndef TESYSOALThreadWIN_HPP
#define TESYSOALThreadWIN_HPP

#include <Comm/OAL/Thread.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
namespace OAL {

    class ThreadWin : public Thread {

    private:
        HANDLE _ThreadHandle;

    public:
        ThreadWin(ThreadServiceFuncType srvFunc, void* arg);
        virtual ~ThreadWin();
                
    };

}; //end of namespace Net
}; //end of namespace Comm


#endif //#if (TESYSOS==TESYSOS_ANDROID)
#endif // #ifndef TESYSNETCLIENT_HPP

