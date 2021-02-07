#include <Comm/OAL/ThreadWin.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
namespace OAL {

    void Thread::Sleep(int miliSec) {
        if (miliSec > 0) {
            ::Sleep(miliSec);
        }
    }

    ThreadWin::ThreadWin(ThreadServiceFuncType srvFunc, void* arg) : Thread(srvFunc, arg) {
    
        _ThreadHandle = ::CreateThread(NULL, 1024 * 32, (LPTHREAD_START_ROUTINE)srvFunc, arg, 0, NULL);
        assert(_ThreadHandle);
    }

    ThreadWin::~ThreadWin() {
    
        if (_ThreadHandle != NULL) {
            
            ::WaitForSingleObject(_ThreadHandle, INFINITE);
            ::CloseHandle(_ThreadHandle);

            _ThreadHandle = NULL;
        }

    }


    

}; //end of namespace Net
}; //end of namespace Comm

#endif // #if (TESYSOS==TESYSOS_ANDROID)
