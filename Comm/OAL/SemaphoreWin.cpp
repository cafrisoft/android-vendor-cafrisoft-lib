#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/SemaphoreWin.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
namespace OAL {

    SemaphoreWin::SemaphoreWin(int initialCount) {
    
        //������ �ʱ�ȭ 
        _hSema = CreateSemaphore(NULL, 
                                 initialCount /*Semaphore Initial Value*/, 
                                 0x7fffffff,  /*Semaphore Maximum Value*/
                                 NULL);
        assert(_hSema);

        
    }

    SemaphoreWin::~SemaphoreWin() {
    
        ::CloseHandle(_hSema);
    }


    //��������� 1 �����Ѵ�.  ���簪�� ZERO�̸� ��� 
    void SemaphoreWin::Wait_Decrease() {
        ::WaitForSingleObject(_hSema, INFINITE);
    }

    //��������� 1 �����Ѵ�.
    void SemaphoreWin::Increase() {
        ::ReleaseSemaphore(_hSema, 1, NULL);
    }


}; //end of namespace Net
}; //end of namespace Comm

#endif // #if (TESYSOS==TESYSOS_ANDROID)
