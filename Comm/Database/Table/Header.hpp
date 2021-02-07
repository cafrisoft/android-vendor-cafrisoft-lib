#ifndef COMM_DATABASE_TABLE_HEADER_HPP__
#define COMM_DATABASE_TABLE_HEADER_HPP__

#include <Comm/Database/Table/Column.hpp>

namespace Comm {
    namespace Database {
        namespace Table {

            class Header : public Base::Object {

            private:
                std::vector<std::shared_ptr<Column>> _ColumnVec;

            public:
                Header();

            public:
                
            };

        }; //namespace Table
    }; //namespace Database
}; //namespace Comm

#endif

