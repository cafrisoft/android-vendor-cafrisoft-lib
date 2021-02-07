#ifndef TESYSOALCriticalSectionLinux_HPP
#define TESYSOALCriticalSectionLinux_HPP

#include <Comm/OAL/CriticalSection.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

namespace Comm {
namespace OAL {

    class CriticalSectionLinux : public CriticalSection {

    private:
        pthread_mutexattr_t _MutexAttr;
        pthread_mutex_t _Mutex;

    public:
        CriticalSectionLinux();
        virtual ~CriticalSectionLinux();

        virtual void Lock();
        virtual void Unlock();
    };

}; //end of namespace Net
}; //end of namespace Comm


#endif //#if (TESYSOS==TESYSOS_ANDROID)
#endif // #ifndef TESYSNETCLIENT_HPP

