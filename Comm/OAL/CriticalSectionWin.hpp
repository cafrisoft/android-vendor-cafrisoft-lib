#ifndef TESYSOALCRITICALSECTIONWIN_HPP
#define TESYSOALCRITICALSECTIONWIN_HPP

#include <Comm/OAL/CriticalSection.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
namespace OAL {

    class CriticalSectionWin : public CriticalSection {

    private:
        CRITICAL_SECTION _CS;

    public:
        CriticalSectionWin();
        virtual ~CriticalSectionWin();

        virtual void Lock();
        virtual void Unlock();
    };

}; //end of namespace Net
}; //end of namespace Comm


#endif //#if (TESYSOS==TESYSOS_ANDROID)
#endif // #ifndef TESYSNETCLIENT_HPP

