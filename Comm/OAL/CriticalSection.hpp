#ifndef OALCRITICALSECTION_HPP
#define OALCRITICALSECTION_HPP

#include <Comm/OAL/SyncObject.hpp>

namespace Comm {
namespace OAL {

    class CriticalSection : public SyncObject {

    public:
        static std::shared_ptr<CriticalSection> CreateObject(void);

    protected:
        CriticalSection();
        virtual ~CriticalSection();

        //virtual void Lock() = 0;
        //virtual void Unlock() = 0;
    };

}; //end of namespace Net
}; //end of namespace Comm

#endif // #ifndef TESYSNETCLIENT_HPP

