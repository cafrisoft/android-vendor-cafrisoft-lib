#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/Cond.hpp>
#include <Comm/OAL/CondWin.hpp>
#include <Comm/OAL/CondLinux.hpp>

namespace Comm {
namespace OAL {

    std::shared_ptr<Cond> Cond::CreateObject() {

        std::shared_ptr<Cond> obj;

#if (CommOS==CommOS_WIN)
        obj = std::make_shared<CondWin>();

#elif (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)
        obj = std::make_shared<CondLinux>();

#else
#error "Select OS"
#endif
        assert(obj);

        return obj;
    }


    Cond::Cond()  {
    
    }

    Cond::~Cond() {
    
    }


}; //end of namespace Net
}; //end of namespace Comm
