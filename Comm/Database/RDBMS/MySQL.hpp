#ifndef COMM_DATABASE_RDBMS_MySQL_HPP__
#define COMM_DATABASE_RDBMS_MySQL_HPP__

#include <Comm/Database/RDBMS/Product.hpp>
#include <Comm/OAL/CriticalSection.hpp>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

namespace Comm {
    namespace Database {
        namespace RDBMS {

            class MySQL : public Product {

            private:
                std::shared_ptr<Comm::OAL::CriticalSection> _Cs;

                sql::Driver* _Driver;
                sql::Connection* _Connection;
                sql::Statement* _Statement;
                sql::ResultSet* _ResultSet;

            public:
                MySQL();
                virtual ~MySQL();

            public:
                virtual bool Connect(std::string strServerIP = "127.0.0.1");
                virtual bool Disconnect();
                virtual bool IsConnect();

                virtual bool SelectSchema(std::string strSchema);
                virtual bool ExecuteQuery(std::string strQuery, QueryResult* queryRes = NULL);
            };

        }; //namespace RDBMS
    }; //namespace OAL
}; //namespace Comm

#endif

