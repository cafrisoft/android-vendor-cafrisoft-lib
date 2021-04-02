#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/Mutex.hpp>
#include <Comm/OAL/MutexWin.hpp>
#include <Comm/OAL/MutexLinux.hpp>

namespace Comm {
namespace OAL {

    std::shared_ptr<Mutex> Mutex::CreateObject(int key) {

        std::shared_ptr<Mutex> obj;

#if (CommOS==CommOS_WIN)
        obj = std::make_shared<MutexWin>(key);

#elif (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)
        obj = std::make_shared<MutexLinux>(key);

#else
#error "Select OS"
#endif
        assert(obj);

        return obj;
    }


    Mutex::Mutex(int key) : _Key(key) {
    
    }

    Mutex::~Mutex() {
    
    }


}; //end of namespace Net
}; //end of namespace Comm
