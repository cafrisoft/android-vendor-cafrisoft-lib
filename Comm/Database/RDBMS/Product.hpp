#ifndef COMM_DATABASE_RDBMS_PRODUCT_HPP__
#define COMM_DATABASE_RDBMS_PRODUCT_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/Database/QueryResult.hpp>

namespace Comm {
    namespace Database {
        namespace RDBMS {

            class Product : public Base::Object {

            public:
                enum class Type {
                    MySQL
                };

                static std::shared_ptr<Product> CreateObject(Type product);

            public:
                enum class QueryResult {
                    Success = 0,
                    Error_Duplicated_Entry = 1062
                };

            protected:
                Product();

            public:
                virtual bool Connect(std::string strServerIP = "127.0.0.1") = 0;
                virtual bool Disconnect() = 0;
                virtual bool IsConnect() = 0;

                virtual bool SelectSchema(std::string strSchema) = 0;
                virtual bool ExecuteQuery(std::string strQuery, QueryResult* queryRes = NULL) = 0;
            };

        }; //namespace RDBMS 
    }; //namespace Database
}; //namespace Comm

#endif

