#ifndef COMM_OAL_LOGANDROID_HPP
#define COMM_OAL_LOGANDROID_HPP

#include <Comm/OAL/Log.hpp>

#if (CommOS==CommOS_ANDROID)

namespace Comm {
    namespace OAL {

        class LogAndroid : public Log {

        public:
            LogAndroid();
            
        };

    }; //end of namespace OAL
}; //end of namespace Comm


#endif //#if (CommOS==CommOS_WIN)

#endif // #ifndef COMM_OAL_LOG_HPP

