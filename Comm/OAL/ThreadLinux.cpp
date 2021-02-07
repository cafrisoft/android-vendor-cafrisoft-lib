#include <Comm/OAL/ThreadLinux.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

namespace Comm {
namespace OAL {

    void Thread::Sleep(int miliSec) {

        if (miliSec > 0) {
            ::usleep(miliSec * 1000);
        }

    }

    ThreadLinux::ThreadLinux(ThreadServiceFuncType srvFunc, void* arg) : Thread(srvFunc, arg) {
    
        int iret;
        pthread_attr_t attr;
        //size_t stack_size;

        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

        //pthread_attr_getstacksize(&attr, &stack_size);
        //pthread_attr_setstacksize(&attr, 1024*1024*8);
        //pthread_attr_getstacksize(&attr, &stack_size);

        //m_hThread = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)this->m_create_config.service, this->m_create_config.arg, CREATE_SUSPENDED, NULL);
        iret = pthread_create(&m_task_hdl, &attr, (void* (*)(void*))srvFunc, arg);
        if (iret != 0) {
            //m_task_hdl = 0;
            assert(1);
        }


    }

    ThreadLinux::~ThreadLinux() {
    
        void* result_t = NULL;

        if (m_task_hdl != 0) {
            pthread_join(m_task_hdl, &result_t);
        }

    }


    

}; //end of namespace Net
}; //end of namespace Comm

#endif // #if (TESYSOS==TESYSOS_ANDROID)
