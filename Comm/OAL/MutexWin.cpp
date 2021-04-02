#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/MutexWin.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
namespace OAL {

    MutexWin::MutexWin(int key) : Mutex(key), _hMutex(NULL) {
    
        char mutex_name[32];

        if (_Key == 0) {
            _hMutex = CreateMutex(NULL, FALSE, NULL);
        }
        else {
            sprintf(mutex_name, "CommOALMutexWIN_0x%08x", _Key);
            _hMutex = CreateMutex(NULL, FALSE, mutex_name);
        }
        assert(_hMutex);
    }

    MutexWin::~MutexWin() {
    
        if (_hMutex != NULL) {
            ::CloseHandle(_hMutex);
            _hMutex = NULL;
        }
        
    }

    void MutexWin::Lock() {
        ::WaitForSingleObject(_hMutex, INFINITE);
    }

    void MutexWin::Unlock() {
        ::ReleaseMutex(_hMutex);
    }

    void* MutexWin::Handle() {
        return (void*)_hMutex;
    }

}; //end of namespace Net
}; //end of namespace Comm

#endif // #if (TESYSOS==TESYSOS_ANDROID)
