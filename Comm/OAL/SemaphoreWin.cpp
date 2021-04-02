#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/SemaphoreWin.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
namespace OAL {

    SemaphoreWin::SemaphoreWin(int initialCount) {
    
        //세마포 초기화 
        _hSema = CreateSemaphore(NULL, 
                                 initialCount /*Semaphore Initial Value*/, 
                                 0x7fffffff,  /*Semaphore Maximum Value*/
                                 NULL);
        assert(_hSema);

        
    }

    SemaphoreWin::~SemaphoreWin() {
    
        ::CloseHandle(_hSema);
    }


    //세마포어값을 1 감소한다.  현재값이 ZERO이면 대기 
    void SemaphoreWin::Wait_Decrease() {
        ::WaitForSingleObject(_hSema, INFINITE);
    }

    //세마포어값을 1 증가한다.
    void SemaphoreWin::Increase() {
        ::ReleaseSemaphore(_hSema, 1, NULL);
    }


}; //end of namespace Net
}; //end of namespace Comm

#endif // #if (TESYSOS==TESYSOS_ANDROID)
