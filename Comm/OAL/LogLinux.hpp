#ifndef COMM_OAL_LOGLINUX_HPP
#define COMM_OAL_LOGLINUX_HPP

#include <Comm/OAL/Log.hpp>

#if (CommOS==CommOS_LINUX)

namespace Comm {
    namespace OAL {

        class LogLinux : public Log {

        public:
            LogLinux();

            virtual void __SysLogOpen(const char* logTag);
            virtual void __SysLogClose();

        };

    }; //end of namespace OAL
}; //end of namespace Comm


#endif //#if (CommOS==CommOS_WIN)

#endif // #ifndef COMM_OAL_LOG_HPP

