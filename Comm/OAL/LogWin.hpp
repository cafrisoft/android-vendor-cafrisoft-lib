#ifndef COMM_OAL_LOGWIN_HPP
#define COMM_OAL_LOGWIN_HPP

#include <Comm/OAL/Log.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
    namespace OAL {

        class LogWin : public Log {

        public:
            LogWin();
        };

    }; //end of namespace OAL
}; //end of namespace Comm


#endif //#if (CommOS==CommOS_WIN)

#endif // #ifndef COMM_OAL_LOG_HPP

