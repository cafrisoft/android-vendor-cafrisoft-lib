#include <Comm/OAL/ProcessMutex.hpp>
#include <Comm/OAL/ProcessMutexWin.hpp>
#include <Comm/OAL/ProcessMutexLinux.hpp>

namespace Comm {
namespace OAL {

    std::shared_ptr<ProcessMutex> ProcessMutex::CreateObject(int key) {

        std::shared_ptr<ProcessMutex> obj;

#if (CommOS==CommOS_WIN)
        obj = std::make_shared<ProcessMutexWin>(key);

#elif (CommOS==CommOS_LINUX )
        obj = std::make_shared<ProcessMutexLinux>(key);

#elif (CommOS==CommOS_ANDROID )
        obj = NULL;

#else
#error "Select OS"
#endif
        assert(obj);

        return obj;
    }


    ProcessMutex::ProcessMutex(int key) : _Key(key) {
    
    }

    ProcessMutex::~ProcessMutex() {
    
    }


}; //end of namespace Net
}; //end of namespace Comm
