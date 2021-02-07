#include <Comm/OAL/CriticalSection.hpp>
#include <Comm/OAL/CriticalSectionWin.hpp>
#include <Comm/OAL/CriticalSectionLinux.hpp>

namespace Comm {
namespace OAL {

    std::shared_ptr<CriticalSection> CriticalSection::CreateObject(void) {

        std::shared_ptr<CriticalSection> obj;

#if (CommOS==CommOS_WIN)
        obj = std::make_shared<CriticalSectionWin>();

#elif (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)
        obj = std::make_shared<CriticalSectionLinux>();

#else
#error "Select OS"
#endif
        assert(obj);

        return obj;
    }


    CriticalSection::CriticalSection() {
    
    }

    CriticalSection::~CriticalSection() {
    
    }


}; //end of namespace Net
}; //end of namespace Comm
