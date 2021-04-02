#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/CondWin.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
namespace OAL {

    CondWin::CondWin() :
        m_hSema(NULL)
        , m_hMutexInternal(NULL)
        , m_waitersCount(0)

    {
        //CS 초기화 
        InitializeCriticalSection(&m_cs_waiter_count);
     
        //세마포 초기화 
        m_hSema = CreateSemaphore(NULL, 0, 0x7fffffff, NULL);
        assert(m_hSema);

        //내부 뮤텍스 초기화 
        m_hMutexInternal = CreateMutex(NULL, FALSE, NULL);
        assert(m_hMutexInternal);
        
    }

    CondWin::~CondWin() {
    
        ::CloseHandle(m_hSema);
        ::CloseHandle(m_hMutexInternal);
        ::DeleteCriticalSection(&m_cs_waiter_count);
    }

    void CondWin::Signal() {
    
        bool haveWaiters;

        ::WaitForSingleObject(this->m_hMutexInternal, INFINITE); //Wait to get  MUTEX Ownership.

        EnterCriticalSection(&m_cs_waiter_count);
        haveWaiters = (this->m_waitersCount > 0) ? true : false;
        LeaveCriticalSection(&m_cs_waiter_count);

        if (haveWaiters) {
            ReleaseSemaphore(m_hSema, 1, 0);
        }

        /*
            When the owning thread no longer needs to own the mutex object,
            it calls the ReleaseMutex function.
        */
        ::ReleaseMutex(this->m_hMutexInternal);
    }
    
    void CondWin::Wait(std::shared_ptr<Mutex> mutex) {
    
        DWORD res;
        HANDLE hMutex;

        hMutex = (HANDLE)mutex->Handle();

        // Increment the wait count, avoiding race conditions.
        EnterCriticalSection(&m_cs_waiter_count);
        this->m_waitersCount++;
        LeaveCriticalSection(&m_cs_waiter_count);

        res = SignalObjectAndWait(hMutex, m_hSema, INFINITE, FALSE); //Signal hMutex, and Wait Semaphore

        EnterCriticalSection(&m_cs_waiter_count);
        this->m_waitersCount--;
        LeaveCriticalSection(&m_cs_waiter_count);

        WaitForSingleObject(m_hMutexInternal, INFINITE);

        // Release the internal and grab the external.
        ReleaseMutex(m_hMutexInternal);
        WaitForSingleObject(hMutex, INFINITE);
    }

}; //end of namespace Net
}; //end of namespace Comm

#endif // #if (TESYSOS==TESYSOS_ANDROID)
