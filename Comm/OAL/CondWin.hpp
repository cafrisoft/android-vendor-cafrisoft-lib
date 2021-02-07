#ifndef COMM_OAL_COND_WIN_HPP
#define COMM_OAL_COND_WIN_HPP

#include <Comm/OAL/Cond.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
namespace OAL {

    class CondWin : public Cond {

    private:
        HANDLE m_hSema;
        HANDLE m_hMutexInternal;
        CRITICAL_SECTION m_cs_waiter_count;
        int m_waitersCount;

    public:
        CondWin();
        virtual ~CondWin();

    public:
        virtual void Signal();
        virtual void Wait(std::shared_ptr<Mutex> mutex);

    };

}; //end of namespace Net
}; //end of namespace Comm


#endif //#if (TESYSOS==TESYSOS_ANDROID)
#endif // #ifndef TESYSNETCLIENT_HPP

