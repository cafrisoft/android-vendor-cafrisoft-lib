#ifndef COMM_DATABASE_QUERYRESULT_HPP__
#define COMM_DATABASE_QUERYRESULT_HPP__

#include <Comm/Base/Object.hpp>

namespace Comm {
    namespace Database {

        enum class QueryResult {
            Error = -1, 
            Success = 0,
            Error_Duplicated_Entry = 1062
        };


    }; //namespace Database
}; //namespace Comm

#endif
