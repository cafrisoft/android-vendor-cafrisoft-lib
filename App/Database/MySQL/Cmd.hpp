#ifndef APPDATABASEMYSQL_CMD_HPP__
#define APPDATABASEMYSQL_CMD_HPP__

#include "AppDefine.hpp"

namespace AppDatabaseMySQL {

    namespace Cmd {

        namespace Insert {

            extern bool BasicTable(int argc, const char** argv);
            extern bool RawData(int argc, const char** argv);
        };

        namespace Export {

            extern bool ToCSV(int argc, const char** argv);
        };

        class Verify {

        public:
            static bool CSV(int argc, const char** argv);
        };

    };
};

#endif
