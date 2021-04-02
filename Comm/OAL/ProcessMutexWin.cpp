#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/ProcessMutexWin.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
namespace OAL {

    ProcessMutexWin::ProcessMutexWin(int key) : ProcessMutex(key), _hProcessMutex(NULL) {
    
        char mutex_name[32];

        if (_Key == 0) {
            _hProcessMutex = CreateMutex(NULL, FALSE, NULL);
        }
        else {
            sprintf(mutex_name, "CommOALProcessMutexWIN_0x%08x", _Key);
            _hProcessMutex = CreateMutex(NULL, FALSE, mutex_name);
        }
        assert(_hProcessMutex);
    }

    ProcessMutexWin::~ProcessMutexWin() {
    
        if (_hProcessMutex != NULL) {
            ::CloseHandle(_hProcessMutex);
            _hProcessMutex = NULL;
        }
        
    }

    void ProcessMutexWin::Lock() {
        ::WaitForSingleObject(_hProcessMutex, INFINITE);
    }

    void ProcessMutexWin::Unlock() {
        ::ReleaseMutex(_hProcessMutex);
    }

    
}; //end of namespace Net
}; //end of namespace Comm

#endif // #if (TESYSOS==TESYSOS_ANDROID)
