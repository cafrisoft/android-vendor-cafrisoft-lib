#ifndef COMM_OAL_PROCESSMUTEX_WIN_HPP
#define COMM_OAL_PROCESSMUTEX_WIN_HPP

#include <Comm/OAL/ProcessMutex.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
namespace OAL {

    class ProcessMutexWin : public ProcessMutex {

    private:
        HANDLE _hProcessMutex;

    public:
        ProcessMutexWin(int key);
        virtual ~ProcessMutexWin();

        virtual void Lock();
        virtual void Unlock();
        
    };

}; //end of namespace Net
}; //end of namespace Comm


#endif //#if (TESYSOS==TESYSOS_ANDROID)
#endif // #ifndef TESYSNETCLIENT_HPP

