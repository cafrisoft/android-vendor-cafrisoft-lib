#ifndef COMM_OAL_MUTEX_WIN_HPP
#define COMM_OAL_MUTEX_WIN_HPP

#include <Comm/OAL/Mutex.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
namespace OAL {

    class MutexWin : public Mutex {

    private:
        HANDLE _hMutex;

    public:
        MutexWin(int key);
        virtual ~MutexWin();

        virtual void Lock();
        virtual void Unlock();
        virtual void* Handle();
    };

}; //end of namespace Net
}; //end of namespace Comm


#endif //#if (TESYSOS==TESYSOS_ANDROID)
#endif // #ifndef TESYSNETCLIENT_HPP

