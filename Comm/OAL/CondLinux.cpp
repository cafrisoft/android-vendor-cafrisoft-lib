#include <Comm/OAL/CondLinux.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

namespace Comm {
namespace OAL {

    CondLinux::CondLinux() {
    
        if (1) { //type == SHARED) {
            pthread_condattr_t attr;
            pthread_condattr_init(&attr);
            pthread_condattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
            pthread_cond_init(&mCond, &attr);
            pthread_condattr_destroy(&attr);
        }
        else {
            pthread_cond_init(&mCond, NULL);
        }

    }

    CondLinux::~CondLinux() {
    
        pthread_cond_destroy(&mCond);
    }


    void CondLinux::Signal() {

        pthread_cond_signal(&mCond);
    }

    void CondLinux::Wait(std::shared_ptr<Mutex> mutex) {

        pthread_mutex_t* p_mutex_t;

        p_mutex_t = (pthread_mutex_t*)mutex->Handle();

        pthread_cond_wait(&mCond, p_mutex_t);
    }

}; //end of namespace Net
}; //end of namespace Comm

#endif // #if (TESYSOS==TESYSOS_ANDROID)
