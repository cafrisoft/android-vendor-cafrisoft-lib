#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/CriticalSectionWin.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
namespace OAL {

    CriticalSectionWin::CriticalSectionWin() {
    
        ::InitializeCriticalSection(&_CS);
    }

    CriticalSectionWin::~CriticalSectionWin() {
    
        ::DeleteCriticalSection(&_CS);
    }


    void CriticalSectionWin::Lock() {
        ::EnterCriticalSection(&_CS);
        
    }

    void CriticalSectionWin::Unlock() {
        ::LeaveCriticalSection(&_CS);

    }

}; //end of namespace Net
}; //end of namespace Comm

#endif // #if (TESYSOS==TESYSOS_ANDROID)
