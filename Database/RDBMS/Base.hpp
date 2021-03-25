#ifndef DATABASE_RDBMS_Base_HPP__
#define DATABASE_RDBMS_Base_HPP__

#include <Comm/Base/Object.hpp>
#include <Database/QueryResult.hpp>
#include <Database/Single/Record.hpp>

namespace Database {
    namespace RDBMS {

        enum class Type {
            MySQL
        };

        class Base : public Comm::Base::Object {

        private:
            static std::shared_ptr<Base> s_Instance;

        public:
            static bool CreateInstance(Type product);
            static bool DestroyInstance();
            static std::shared_ptr<Base> Inst();
        
        protected:
            Base();

        public:
            virtual bool Connect(std::string strServerIP, int port, std::string accountID, std::string accountPW) = 0;
            virtual bool Disconnect() = 0;
            virtual bool IsConnect() = 0;

            virtual bool SelectSchema(std::string strSchema) = 0;
            virtual bool ExecuteQuery(std::string strQuery, QueryResult* queryRes = NULL) = 0;

        protected:
            virtual int QueryInt(std::string strQuery, std::string columnName, int defaultValue = -1) = 0;
            virtual bool QueryInsert(std::string strQuery, bool isDebug=false) = 0;

        public:
            virtual int QueryInt(std::string tableName, std::string getColName, std::string whereColName, int whereColValue, int defaultValue=-1);
            virtual bool QueryInsert(std::string tableName, std::vector<std::string> strValueVec);

            virtual bool InsertRecord(std::string tableName, std::shared_ptr<Database::Single::Record> record, bool isDebug=false);
            
            virtual bool SelectData(std::string tableName, std::shared_ptr<Database::Single::Record> record /*OUT*/, std::shared_ptr<Database::Single::Record> whereRecord, bool isDebug = false);
            virtual bool SelectData(std::string tableName, std::shared_ptr<Database::Single::Record> record /*OUT*/, std::string whereString, bool isDebug = false) = 0;
            virtual std::vector<std::shared_ptr<Database::Single::Record>> SelectMultiData(std::string tableName, std::shared_ptr<Database::Single::Record> record /*ref*/, std::shared_ptr<Database::Single::Record> whereRecord);
            virtual std::vector<std::shared_ptr<Database::Single::Record>> SelectMultiData(std::string tableName, std::shared_ptr<Database::Single::Record> record /*ref*/, std::string whereString) = 0;

            
            virtual bool UpdateData(std::string tableName, std::shared_ptr<Database::Single::Record> record, std::shared_ptr<Database::Single::Record> whereRecord);
            virtual bool UpdateData(std::string tableName, std::string updateString, std::string whereString) = 0;

            //virtual bool SelectData(std::string tableName, std::shared_ptr<Database::Join::Record> record /*OUT*/, std::shared_ptr<Database::Join::Record> whereRecord);
            
            virtual void* TransactionSelectCreateHandle(std::string tableName, std::shared_ptr<Database::Single::Record> refRecord /*ref*/, std::shared_ptr<Database::Single::Record> whereRecord) = 0;
            virtual bool TransactionSelectDestroyHandle(void* hdl) = 0;
            virtual std::shared_ptr<Database::Single::Record> TransactionSelectNext(void* hdl) = 0;

        };

    }; //namespace BaseClass 
}; //namespace Database


#endif

