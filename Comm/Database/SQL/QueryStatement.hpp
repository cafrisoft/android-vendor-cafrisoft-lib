#ifndef COMM_DATABASE_SQL_QUERYSTATEMENT_HPP__
#define COMM_DATABASE_SQL_QUERYSTATEMENT_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/Database/QueryResult.hpp>

namespace Comm {
    namespace Database {
        namespace SQL {
            namespace QueryStatement {

                //select column_name from information_schema.columns where table_schema='mystockdb' and table_name='corp';
                std::string ColumnName(std::string dbName, std::string tableName);
                std::string Column(std::string dbName, std::string tableName);
            
            }; //namespace QueryStatement {
        };  //namespace SQL
    }; //namespace Database
}; //namespace Comm

#endif

