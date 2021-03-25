#ifndef DATABASE_RDBMS_MySQL_HPP__
#define DATABASE_RDBMS_MySQL_HPP__

#include <Database/RDBMS/Base.hpp>
#include <Comm/OAL/CriticalSection.hpp>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

namespace Database {
    namespace RDBMS {

        class MySQL : public Base {

        private:
            class TransactionSelect {
            public:
                std::shared_ptr<Database::Single::Record> _ReadRefRecord;    /*Read ref Record*/
                std::shared_ptr<Database::Single::Record> _WhereRecord;      /*Where Record*/
                sql::ResultSet* _SqlResult;
                sql::Statement* _Statement;
            };

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
            virtual bool Connect(std::string strServerIP, int port, std::string accountID, std::string accountPW);
            virtual bool Disconnect();
            virtual bool IsConnect();

            virtual bool SelectSchema(std::string strSchema);
            virtual bool ExecuteQuery(std::string strQuery, QueryResult* queryRes = NULL);

        private:
            virtual int QueryInt(std::string strQuery, std::string getColName, int defaultValue); 
            virtual bool QueryInsert(std::string strQuery, bool isDebug=false);

            virtual std::vector<int> QueryIntVector(std::string strQuery, std::string columnName, QueryResult* queryRes = NULL);
        
            
            virtual bool UpdateData(std::string tableName, std::string updateString, std::string whereString);


            /* Select Functions*/
        private:
            bool SelectReadRecordByIdx(sql::ResultSet* sqlResult, std::shared_ptr<Database::Single::Record> readRecord, bool isDebug=false);
            bool SelectReadRecordByColNmae(sql::ResultSet* sqlResult, std::shared_ptr<Database::Single::Record> readRecord);
            
        public:
            virtual bool SelectData(std::string tableName, std::shared_ptr<Database::Single::Record> record /*OUT*/, std::string whereString, bool isDebug = false);
            virtual std::vector<std::shared_ptr<Database::Single::Record>> SelectMultiData(std::string tableName, std::shared_ptr<Database::Single::Record> record /*ref*/, std::string whereString);

            virtual void* TransactionSelectCreateHandle(std::string tableName, std::shared_ptr<Database::Single::Record> refRecord /*ref*/, std::shared_ptr<Database::Single::Record> whereRecord);
            virtual bool TransactionSelectDestroyHandle(void* hdl);
            virtual std::shared_ptr<Database::Single::Record> TransactionSelectNext(void* hdl);

        };

    }; //namespace RDBMS
}; //namespace OAL


#endif

