#include <Comm/Global/BuildOptions.h>
#define CLOG_TAG "ProcessMutexLinux"
#include <Comm/OAL/Log.hpp>
#include <Comm/OAL/ProcessMutexLinux.hpp>

#if (CommOS==CommOS_ANDROID)
#include <linux/ipc.h>
#include <linux/sem.h>
#include <sys/syscall.h>
#endif

#if ((CommOS==CommOS_ANDROID ) || (CommOS==CommOS_LINUX))

//#if ANDROID_PLATFORM_SDK_VERSION >= 28  //Android9
union semun {
    int val;
    struct semid_ds* buf;
    unsigned short* array;
    struct seminfo* __buf;
    void* __pad;
};
//#endif

#endif


#if (CommOS==CommOS_ANDROID)
#if (ANDROID_MAJOR_VERSION < 9)
#define __IPC_64            0x100

int semget(key_t key, int nsems, int semflg)
{
    int ret;

    ret = syscall(SYS_semget, key, nsems, semflg);

    //RLOGV("[%s] ln=%d  key=0x%08x  nsems=%d semflg=0x%x semid=%d ", __func__, __LINE__, key, nsems, semflg, ret);

    return ret;
}

int semctl(int semid, int semnum, int cmd, ...)
{
    union semun arg;

    va_list ap;
    int ret;
    const char* cmdstr = "Unknonw";

    arg.buf = NULL;
    va_start(ap, cmd);
    arg = va_arg(ap, union semun);
    va_end(ap);

    ret = syscall(SYS_semctl, semid, semnum, cmd | __IPC_64, arg.__pad);

    switch (cmd) {
    case SETVAL:
        //memcpy(arg.argbuf, &un.val, sizeof(int));
        cmdstr = "SETVAL";
        break;

    case SETALL:
        //memcpy(arg.argbuf, un.array, sizeof(short)*2 /*semnum*/ );
        cmdstr = "SETALL";
        break;

    case IPC_RMID:
        cmdstr = "IPC_RMID";
        break;
    }

    //RLOGV("[%s] ln=%d  semid=%d semnum=%d ret=%d cmd=%d(%s)", __func__, __LINE__, semid, semnum, ret, cmd, cmdstr);

    return ret;
}

int semop(int semid, struct sembuf* sops, unsigned nsops)
{
    int ret;

    ret = syscall(SYS_semop, semid, sops, nsops);

    //RLOGV("[%s] ln=%d  semid=%d sops(num:%d op:%d flg:%d) nsops=%d  ret=%d ", __func__, __LINE__,
      //  semid,
        //sops->sem_num, sops->sem_op, sops->sem_flg,
        //nsops,
        //ret
    //);

    return ret;
}
#endif //#if (ANDROID_MAJOR_VERSION < 9)
#endif //#if (CommOS==CommOS_ANDROID)

#if (CommOS==CommOS_LINUX  )

namespace Comm {
    namespace OAL {

        ProcessMutexLinux::ProcessMutexLinux(int  key) : 
            ProcessMutex(key) 
            , _SemID(-1)
        {

            union semun arg;

            _SemID = semget(_Key, 1, 0666 | IPC_CREAT | IPC_EXCL);
            if (_SemID == -1) {
                _SemID = semget(_Key, 1, 0);
                assert(_SemID != -1);

                CLOGI("Second Process-Semaphore Get : Key=%d SemID=%d ", _Key, _SemID);
            }
            else {
                CLOGI("First Process-Semaphore Get : Key=%d SemID=%d ", _Key, _SemID);

                //최초 생성한 경우이면,  세마포어 값을 1로 설정해  Lock에 진입할 수 있도록 한다. 
                arg.val = 1;                
                if (-1 == semctl(_SemID, 0, SETVAL, arg))
                {
                    fprintf(stderr, "[nv_lock_init] FAIL: semctl(s_mutex_semid, 0, SETVAL, arg) \n");
                    return;
                }
            }
        }

        ProcessMutexLinux::~ProcessMutexLinux() {

            union semun arg;

            if (_SemID != -1) {
                semctl(_SemID, 0, IPC_RMID, arg);
            }
        }


        void ProcessMutexLinux::Lock() {

            struct sembuf pbuf;

            pbuf.sem_num = 0;  /*0번째 세마포어*/
            pbuf.sem_op = -1;
            pbuf.sem_flg = SEM_UNDO;

            semop(_SemID, &pbuf, 1);
        }

        void ProcessMutexLinux::Unlock() {

            struct sembuf vbuf;

            vbuf.sem_num = 0; /*0번째 세마포어*/
            vbuf.sem_op = 1;
            vbuf.sem_flg = SEM_UNDO;

            semop(_SemID, &vbuf, 1);

        }


    }; //end of namespace Net
}; //end of namespace Comm

#endif // #if (TESYSOS==TESYSOS_ANDROID)
