#ifndef COMM_DATABASE_TABLE_COLUMN_HPP__
#define COMM_DATABASE_TABLE_COLUMN_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/Database/QueryResult.hpp>

namespace Comm {
    namespace Database {
        namespace Table {

            class Column : public Base::Object {

            private:
                std::string _Name;

            public:
                Column();

            public:
                
            };

        }; //namespace Table
    }; //namespace Database
}; //namespace Comm

#endif

