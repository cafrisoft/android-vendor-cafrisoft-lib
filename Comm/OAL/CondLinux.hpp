#ifndef COMM_OAL_CONDLINUX_HPP
#define COMM_OAL_CONDLINUX_HPP

#include <Comm/OAL/Cond.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

namespace Comm {
namespace OAL {

    class CondLinux : public Cond {

    private:
        pthread_cond_t mCond;

    public:
        CondLinux();
        virtual ~CondLinux();

    public:
        virtual void Signal();
        virtual void Wait(std::shared_ptr<Mutex> mutex);
    };

}; //end of namespace Net
}; //end of namespace Comm


#endif //#if (TESYSOS==TESYSOS_ANDROID)
#endif // #ifndef TESYSNETCLIENT_HPP

