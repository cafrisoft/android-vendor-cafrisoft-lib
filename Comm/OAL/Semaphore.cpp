#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/Semaphore.hpp>
#include <Comm/OAL/SemaphoreWin.hpp>
#include <Comm/OAL/SemaphoreLinux.hpp>

namespace Comm {
namespace OAL {

    std::shared_ptr<Semaphore> Semaphore::CreateObject(int initialCount) {

        std::shared_ptr<Semaphore> obj;

#if (CommOS==CommOS_WIN)
        obj = std::make_shared<SemaphoreWin>(initialCount);

#elif (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)
        obj = std::make_shared<SemaphoreLinux>(initialCount);

#else
#error "Select OS"
#endif
        assert(obj);

        return obj;
    }


    Semaphore::Semaphore() {
    
    }

    Semaphore::~Semaphore() {
    
    }


}; //end of namespace Net
}; //end of namespace Comm
