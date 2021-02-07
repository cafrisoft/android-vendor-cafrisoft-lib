#include <Comm/Database/SQL/QueryStatement.hpp>
#include <Comm/Utils/StringTool.hpp>

namespace Comm {
    namespace Database {
        namespace SQL {
            namespace QueryStatement {

                //select column_name from information_schema.columns where table_schema='mystockdb' and table_name='corp';
                std::string ColumnName(std::string dbName, std::string tableName) {
                
                    const char* fmtStr = "select column_name from information_schema.columns where table_schema='%s' and table_name='%s'";
                    return Comm::Utils::StringFormat(fmtStr, dbName.c_str(), tableName.c_str() );
                }

                std::string Column(std::string dbName, std::string tableName) {

                    const char* fmtStr = "select * from information_schema.columns where table_schema='%s' and table_name='%s'";
                    return Comm::Utils::StringFormat(fmtStr, dbName.c_str(), tableName.c_str());
                }

            }; //namespace QueryStatement {
        };  //namespace SQL
    }; //namespace Database
}; //namespace Comm
