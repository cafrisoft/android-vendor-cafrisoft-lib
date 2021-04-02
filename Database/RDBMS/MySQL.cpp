#include <Database/Global/BuildOptions.h>
#define CLOG_TAG "DatabaseRMDBMSMySQL"
#include <Database/RDBMS/MySQL.hpp>
#include <Comm/OAL/Lock.hpp>
#include <Comm/Utils/StringTool.hpp>
#include <Comm/OAL/Log.hpp>
#include <Comm/OAL/DateTime.hpp>

//#define ENABLE_CREATE_STATEMENT

namespace Database {
    namespace RDBMS {

        MySQL::MySQL() :
            _Driver(NULL)
            , _Connection(NULL)
            , _Statement(NULL)
            , _ResultSet(NULL)
        {
            _Cs = Comm::OAL::CriticalSection::CreateObject();
            assert(_Cs);
        
            _Driver = get_driver_instance();
            assert(_Driver);
        }

        MySQL::~MySQL() {
        

            this->Disconnect();

        }

        bool MySQL::Connect(std::string strServerIP, int port, std::string accountID, std::string accountPW) {

            bool bRet = false;
            Comm::OAL::Lock lock(_Cs);

            sql::Driver* driver = (sql::Driver*)_Driver;
            sql::Connection* connection;
#ifndef ENABLE_CREATE_STATEMENT
            sql::Statement* statement;
#endif

            std::string strConn = Comm::Utils::StringFormat("tcp://%s:%d", strServerIP.c_str(), port);
            connection = driver->connect(strConn.c_str(), accountID.c_str(), accountPW.c_str());
            if (connection) {
                bRet = true;

#ifndef ENABLE_CREATE_STATEMENT
                statement = connection->createStatement();
                assert(statement);
#endif

                _Connection = connection;
#ifndef ENABLE_CREATE_STATEMENT
                _Statement = statement;
#endif
            }

            return bRet;
        }

        bool MySQL::Disconnect() {

            Comm::OAL::Lock lock(_Cs);

            sql::Connection* connection = _Connection;
            sql::Statement* statement = _Statement;;

            if (statement) {
                delete statement;
                _Statement = NULL;
            }

            if (connection) {
                delete connection;
                _Connection = NULL;
            }

            return true;
        }

        bool MySQL::IsConnect() {

            bool bIsConn = false;
            Comm::OAL::Lock lock(_Cs);

            if (_Connection) {
                bIsConn = true;
            }

            return bIsConn;
        }

        bool MySQL::SelectSchema(std::string strSchema) {
        
            sql::Connection* connection = _Connection;

            assert(_Connection);

            connection->setSchema(strSchema.c_str());

            return true;
        }

        bool MySQL::ExecuteQuery(std::string strQuery, QueryResult* queryRes) {
        
#if 0
            sql::Connection* connection = (sql::Connection*)_Connection;

            bool bRet = false;
            Comm::OAL::Lock lock(_Cs);

#if (CommOS==CommOS_WIN)
            std::string strQueryUTF8 = Comm::Utils::StringTool::AnsiToUtf8(strQuery);
#else
            std::string strQueryUTF8 = strQueryIn;
#endif

            try {

                sql::ResultSet* res = _Statement->executeQuery(strQueryUTF8.c_str());
                assert(res);

                while (res->next()) {
                    PRINTF("%s \n", res->getString(1));
                }
                delete res;

                bRet = true;
            }
            catch (sql::SQLException & e) {

                if (queryRes) {
                    *queryRes = (QueryResult)e.getErrorCode();
                }

                if (e.getErrorCode() == 0) {

                    CLOGI("Query [%s]... OK ", strQuery.c_str());
                    bRet = true;
                }
                else {
                    CLOGE("# ERR: SQLException in %s (%s) on line", __FILE__, __FUNCTION__, __LINE__);
                    CLOGE("# ERR: %s", e.what());
                    CLOGE("   MySQL error code: %d, SQLState: %s", e.getErrorCode(), e.getSQLState().c_str());
                }
            }

            return bRet;
#else
            return false;
#endif
        }
        
        
        int MySQL::QueryInt(std::string strQuery, std::string getColName, int defaultValue) {
        
            int intValue = defaultValue;

            

            sql::Connection* connection = _Connection;
#ifdef ENABLE_CREATE_STATEMENT
            sql::Statement* statement = connection->createStatement();
            assert(statement);
#else
            sql::Statement* statement = _Statement;;
            Comm::OAL::Lock lock(_Cs);
#endif
            

#if (CommOS==CommOS_WIN)
            std::string strQueryUTF8 = Comm::Utils::StringTool::AnsiToUtf8(strQuery);
#else
            std::string strQueryUTF8 = strQuery;
#endif

            try {

                sql::ResultSet* res = statement->executeQuery(strQueryUTF8.c_str());
                assert(res);

                while (res->next()) {
                    intValue = res->getInt(getColName.c_str());
                }
                delete res;

            }
            catch (sql::SQLException& e) {
                if (e.getErrorCode() == 0) {
                    //CLOGI("Query [%s]... OK ", strQuery.c_str());
                }
                else {
                    CLOGE("# ERR: SQLException in %s (%s) on line", __FILE__, __FUNCTION__, __LINE__);
                    CLOGE("# ERR: %s", e.what());
                    CLOGE("   MySQL error code: %d, SQLState: %s", e.getErrorCode(), e.getSQLState().c_str());
                    CLOGE("Query [%s]... FAIL ", strQuery.c_str());
                }
            }

#ifdef ENABLE_CREATE_STATEMENT
            delete statement;
#endif

            return intValue;
        }

#if 0
        int MySQL::QueryInt(std::string tableName, std::string getColName, std::string whereColName, int whereColValue, QueryResult* queryRes) {
        
        }
#endif

        std::vector<int> MySQL::QueryIntVector(std::string strQuery, std::string columnName, QueryResult* queryRes) {

            std::vector<int> intVector;

            sql::Connection* connection = _Connection;
            
#ifdef ENABLE_CREATE_STATEMENT
            sql::Statement* statement = connection->createStatement();
            assert(statement);
#else
            sql::Statement* statement = _Statement;;
            Comm::OAL::Lock lock(_Cs);
#endif


            std::string strQueryUTF8 = Comm::Utils::StringTool::AnsiToUtf8(strQuery);

            try {

                sql::ResultSet* res = statement->executeQuery(strQueryUTF8.c_str());
                assert(res);

                while (res->next()) {
                    int intValue = res->getInt(columnName.c_str());
                    intVector.push_back(intValue);
                }
                delete res;

                if (queryRes) {
                    *queryRes = QueryResult::Success;
                }

            }
            catch (sql::SQLException& e) {

                if (queryRes) {
                    *queryRes = (QueryResult)e.getErrorCode();
                }

                if (e.getErrorCode() == 0) {
                    //CLOGI("Query [%s]... OK ", strQuery.c_str());
                }
                else {
                    CLOGE("# ERR: SQLException in %s (%s) on line", __FILE__, __FUNCTION__, __LINE__);
                    CLOGE("# ERR: %s", e.what());
                    CLOGE("   MySQL error code: %d, SQLState: %s", e.getErrorCode(), e.getSQLState().c_str());
                    CLOGE("Query [%s]... FAIL ", strQuery.c_str());
                }
            }

#ifdef ENABLE_CREATE_STATEMENT
            delete statement;
#endif

            return intVector;
        }

        bool MySQL::QueryInsert(std::string strQuery, bool isDebug) {
        
#ifdef ENABLE_CREATE_STATEMENT
            sql::Statement* statement = _Connection->createStatement();
            assert(statement);
#else
            sql::Statement* statement = _Statement;;
            Comm::OAL::Lock lock(_Cs);
#endif

            bool bRet;
            std::string strQueryUTF8 = Comm::Utils::StringTool::AnsiToUtf8(strQuery);

            if (isDebug) {
                PRINTF("[MySQL::QueryInsert] Query=[%s] \n", strQuery.c_str());
            }

            try {
                sql::ResultSet* res = statement->executeQuery(strQueryUTF8.c_str());
                assert(res);
                while (res->next()) {
                    //PRINTF("%s \n", g_ResultSet->getString(1));
                    //PRINTF("[InsertRecordToTableBoard] BoardID=%d %s \n", boardID, g_ResultSet->getString(1));
                }
                delete res;
                bRet = true;
            }
            catch (sql::SQLException& e) {

                //if (queryRes) {
                  //  *queryRes = (QueryResult)e.getErrorCode();
                //}

                if (e.getErrorCode() == 0) {
                    //CLOGI("Query [%s]... OK ", strQuery.c_str());

                    bRet = true;
                }
                else {
                    CLOGE("# ERR: SQLException in %s (%s) on line", __FILE__, __FUNCTION__, __LINE__);
                    CLOGE("# ERR: %s", e.what());
                    CLOGE("   MySQL error code: %d, SQLState: %s", e.getErrorCode(), e.getSQLState().c_str());
                    CLOGE("Query [%s]... FAIL ", strQuery.c_str());
                    bRet = false;
                }
            }

#ifdef ENABLE_CREATE_STATEMENT
            delete statement;
#endif

            return bRet;
        }

        bool MySQL::UpdateData(std::string tableName, std::string updateString, std::string whereString) {

#ifdef ENABLE_CREATE_STATEMENT
            sql::Statement* statement = _Connection->createStatement();
            assert(statement);
#else
            sql::Statement* statement = _Statement;;
            Comm::OAL::Lock lock(_Cs);
#endif


            bool bRet = false;
            std::string strQuery;

            if (whereString.size() > 0) {
                strQuery = Comm::Utils::StringFormat("update %s SET %s where %s", tableName.c_str(),
                    updateString.c_str(),
                    whereString.c_str()
                );
            }
            else {
                strQuery = Comm::Utils::StringFormat("update %s SET %s ", tableName.c_str(),
                    updateString.c_str()
                );
            }

            std::string strQueryUTF8 = Comm::Utils::StringTool::AnsiToUtf8(strQuery);

            try {

                sql::ResultSet* res = statement->executeQuery(strQueryUTF8.c_str());
                assert(res);

                while (res->next()) {
                    /* Nothing to do */
                }
                delete res;
                bRet = true;
            }
            catch (sql::SQLException& e) {
                if (e.getErrorCode() == 0) {
                    //CLOGI("Query [%s]... OK ", strQuery.c_str());
                    bRet = true;
                }
                else {
                    CLOGE("# ERR: SQLException in %s (%s) on line", __FILE__, __FUNCTION__, __LINE__);
                    CLOGE("# ERR: %s", e.what());
                    CLOGE("   MySQL error code: %d, SQLState: %s", e.getErrorCode(), e.getSQLState().c_str());
                }
            }

#ifdef ENABLE_CREATE_STATEMENT
            delete statement;
#endif

            return bRet;
        }

        bool MySQL::SelectReadRecordByColNmae(sql::ResultSet* sqlResult, std::shared_ptr<Database::Single::Record> readRecord) {
                    
            for (int idx = 0; idx < readRecord->GetColumnCount(); idx++) {

                if (!readRecord->IsEnable(idx)) {
                    continue;
                }
                
                
                std::string colName = readRecord->GetColumnName(idx);
                Comm::VarType::SQL sqlType = readRecord->GetDataType(idx);

                switch (sqlType) {

                case Comm::VarType::SQL::SmallInt:
                {
                    short value = (short)sqlResult->getInt(colName.c_str());
                    readRecord->SetValue(idx, value);
                    break;
                }

                case Comm::VarType::SQL::SmallUint:
                {
                    unsigned short value = (unsigned short)sqlResult->getUInt(colName.c_str());
                    readRecord->SetValue(idx, value);
                    break;
                }

                case Comm::VarType::SQL::Uint:
                {
                    //unsigned int value = sqlResult->getUInt(colName.c_str());
                    unsigned int value = sqlResult->getUInt(idx+1);
                    readRecord->SetValue(idx, value);
                    break;
                }

                case Comm::VarType::SQL::Int:
                {
                    int intValue = sqlResult->getInt(colName.c_str());
                    readRecord->SetValue(idx, intValue);
                    break;
                }

                case Comm::VarType::SQL::BigInt:
                {
                    long long value = sqlResult->getInt64(colName.c_str());
                    readRecord->SetValueBigInt(idx, value);
                    break;
                }

                case Comm::VarType::SQL::BigUint:
                {
                    unsigned long long value = sqlResult->getUInt64(colName.c_str());
                    readRecord->SetValueBigUint(idx, value);
                    break;
                }

                case Comm::VarType::SQL::Float:
                {
                    sql::SQLString sqlString = sqlResult->getString(colName.c_str());
                    float value = (float)atof(sqlString.c_str());
                    readRecord->SetValue(idx, value);
                    break;
                }

                case Comm::VarType::SQL::Date:
                {

                    sql::SQLString sqlString = sqlResult->getString(colName.c_str());
                    time_t t = Comm::OAL::DateTime::GetUtcTime_KST_SqlFmtDate(sqlString.c_str());
                    //PRINTF("sqlTime %s \n", Comm::OAL::DateTime::GetKstDateTimeString(t).c_str());
                    readRecord->SetValueTime(idx, t);
                    break;
                }


                case Comm::VarType::SQL::DateTime:
                {

                    sql::SQLString sqlString = sqlResult->getString(colName.c_str());
                    time_t t = Comm::OAL::DateTime::GetUtcTime_KST_SqlFmtDateTime(sqlString.c_str());
                    //PRINTF("sqlTime %s \n", Comm::OAL::DateTime::GetKstDateTimeString(t).c_str());
                    readRecord->SetValueTime(idx, t);
                    break;
                }

                case Comm::VarType::SQL::VarChar:
                {
                    sql::SQLString sqlString = sqlResult->getString(colName.c_str());
                    std::string strAnsi;

                    #if (CommOS==CommOS_WIN)
                    std::string strUtf8 = sqlString.c_str();
                    strAnsi = Comm::Utils::StringTool::Utf8ToAnsi(strUtf8);
                    #else       
                    strAnsi = sqlString.c_str();
                    #endif

                    readRecord->SetValue(idx, strAnsi);
                    break;
                }


                default:
                    assert(0);

                }

            } //for (std::vector<int>::const_iterator it = colIdxVec.cbegin();

            return true;
        } 
        
        bool MySQL::SelectReadRecordByIdx(sql::ResultSet* sqlResult, std::shared_ptr<Database::Single::Record> readRecord, bool isDebug) {

            int sqlColIdx = 0;
            for (int idx = 0; idx < readRecord->GetColumnCount(); idx++) {

                if (!readRecord->IsEnable(idx)) {
                    continue;
                }

                sqlColIdx++;
                Comm::VarType::SQL sqlType = readRecord->GetDataType(idx);

                switch (sqlType) {

                case Comm::VarType::SQL::SmallInt:
                {
                    short value = (short)sqlResult->getInt(sqlColIdx);
                    readRecord->SetValue(idx, value);
                    if (isDebug) PRINTF("[SQL::SmallInt] idx=%d value=%d \n", idx, value);
                    break;
                }

                case Comm::VarType::SQL::SmallUint:
                {
                    unsigned short value = (unsigned short)sqlResult->getUInt(sqlColIdx);
                    readRecord->SetValue(idx, value);
                    if (isDebug) PRINTF("[SQL::SmallUint] idx=%d value=%d \n", idx, value);
                    break;
                }

                case Comm::VarType::SQL::Uint:
                {
                    unsigned int value = sqlResult->getUInt(sqlColIdx);
                    readRecord->SetValue(idx, value);
                    if (isDebug) PRINTF("[SQL::Uint] idx=%d value=%d \n", idx, value);
                    break;
                }

                case Comm::VarType::SQL::Int:
                {
                    int intValue = sqlResult->getInt(sqlColIdx);
                    readRecord->SetValue(idx, intValue);
                    if (isDebug) PRINTF("[SQL::Int] idx=%d value=%d \n", idx, intValue);
                    break;
                }

                case Comm::VarType::SQL::BigInt:
                {
                    long long value = sqlResult->getInt64(sqlColIdx);
                    readRecord->SetValueBigInt(idx, value);
                    if (isDebug) PRINTF("[SQL::BigInt] idx=%d value=%lld \n", idx, value);
                    break;
                }

                case Comm::VarType::SQL::BigUint:
                {
                    unsigned long long value = sqlResult->getUInt64(sqlColIdx);
                    readRecord->SetValueBigUint(idx, value);
                    if (isDebug) PRINTF("[SQL::BigUint] idx=%d value=%lld \n", idx, value);
                    break;
                }

                case Comm::VarType::SQL::Float:
                {
                    sql::SQLString sqlString = sqlResult->getString(sqlColIdx);
                    float value = (float)atof(sqlString.c_str());
                    readRecord->SetValue(idx, value);
                    if (isDebug) PRINTF("[SQL::Float] idx=%d value=%f \n", idx,value);
                    break;
                }

                case Comm::VarType::SQL::Date:
                {

                    sql::SQLString sqlString = sqlResult->getString(sqlColIdx);
                    time_t t = Comm::OAL::DateTime::GetUtcTime_KST_SqlFmtDate(sqlString.c_str());
                    //PRINTF("sqlTime %s \n", Comm::OAL::DateTime::GetKstDateTimeString(t).c_str());
                    readRecord->SetValueTime(idx, t);
                    if (isDebug) PRINTF("[SQL::Date] idx=%d time=%lld timestr=[%s] \n", idx, t, Comm::OAL::DateTime::GetKstDateTimeString(t).c_str());
                    break;
                }


                case Comm::VarType::SQL::DateTime:
                {

                    sql::SQLString sqlString = sqlResult->getString(sqlColIdx);
                    time_t t = Comm::OAL::DateTime::GetUtcTime_KST_SqlFmtDateTime(sqlString.c_str());
                    //PRINTF("sqlTime %s \n", Comm::OAL::DateTime::GetKstDateTimeString(t).c_str());
                    readRecord->SetValueTime(idx, t);
                    if (isDebug) PRINTF("[SQL::DateTime] idx=%d time=%lld timestr=[%s] \n", idx, t, Comm::OAL::DateTime::GetKstDateTimeString(t).c_str());
                    break;
                }

                case Comm::VarType::SQL::VarChar:
                {

                    sql::SQLString sqlString = sqlResult->getString(sqlColIdx);
                    std::string strAnsi;

#if (CommOS==CommOS_WIN)
                    std::string strUtf8 = sqlString.c_str();
                    strAnsi = Comm::Utils::StringTool::Utf8ToAnsi(strUtf8);
#else       
                    strAnsi = sqlString.c_str();
#endif

                    readRecord->SetValue(idx, strAnsi);

                    break;
                }


                default:
                    assert(0);

                }

            } //for (std::vector<int>::const_iterator it = colIdxVec.cbegin();

            return true;
        }
        bool MySQL::SelectData(std::string tableName, std::shared_ptr<Database::Single::Record> record /*OUT*/, std::string whereString, bool isDebug) {

            bool bRet = true;
            
#ifdef ENABLE_CREATE_STATEMENT
            sql::Statement* statement = _Connection->createStatement();
            assert(statement);
#else
            sql::Statement* statement = _Statement;;
            Comm::OAL::Lock lock(_Cs);
#endif


            std::string colNameArr = record->GetEnabledColumnNameSqlArgString();
            std::string strQuery;
        
            if (whereString.size() > 0) {
                strQuery = Comm::Utils::StringFormat("select %s from %s where %s", colNameArr.c_str(), tableName.c_str(), whereString.c_str());
            }
            else {
                strQuery = Comm::Utils::StringFormat("select %s from %s", colNameArr.c_str(), tableName.c_str());
            }

            std::string strQueryUTF8 = Comm::Utils::StringTool::AnsiToUtf8(strQuery);

            try {

                if (isDebug) {
                    PRINTF("-------------MySQL::SelectData----------------\n");
                    PRINTF("%s \n\n", strQuery.c_str());
                }

                int recCnt = 0;
                sql::ResultSet* res = statement->executeQuery(strQueryUTF8.c_str());
                assert(res);

                while (res->next()) {
                    this->SelectReadRecordByIdx(res, record, isDebug);
                    recCnt++;
                }
                delete res;

                if (recCnt == 0) {
                    bRet = false;
                }
                else {
                    bRet = true;
                }

                if (isDebug) {
                    PRINTF("QueryResCount=%d %s \n\n", recCnt);
                }


            }
            catch (sql::SQLException& e) {
                if (e.getErrorCode() == 0) {
                    //CLOGI("Query [%s]... OK ", strQuery.c_str());
                }
                else {
                    CLOGE("# ERR: SQLException in %s (%s) on line", __FILE__, __FUNCTION__, __LINE__);
                    CLOGE("# ERR: %s", e.what());
                    CLOGE("   MySQL error code: %d, SQLState: %s", e.getErrorCode(), e.getSQLState().c_str());

                    CLOGE("Query [%s]... FAIL ", strQuery.c_str());
                    assert(0);
                    bRet = false;
                }
            }

#ifdef ENABLE_CREATE_STATEMENT
            delete statement;
#endif

            return bRet;
        }

        std::vector<std::shared_ptr<Database::Single::Record>> MySQL::SelectMultiData(std::string tableName, 
                                                                                      std::shared_ptr<Database::Single::Record> refRecord /*ref*/, 
                                                                                      std::string whereString) 
        {
#ifdef ENABLE_CREATE_STATEMENT
            sql::Statement* statement = _Connection->createStatement();
            assert(statement);
#else
            sql::Statement* statement = _Statement;;
            Comm::OAL::Lock lock(_Cs);
#endif


            std::vector<std::shared_ptr<Database::Single::Record>> recordVector;
            std::string colNameArr = refRecord->GetEnabledColumnNameSqlArgString();
            std::string strQuery;

            if (whereString.size() > 0) {
                strQuery = Comm::Utils::StringFormat("select %s from %s where %s", colNameArr.c_str(), tableName.c_str(), whereString.c_str());
            }
            else {
                strQuery = Comm::Utils::StringFormat("select %s from %s", colNameArr.c_str(), tableName.c_str());
            }

#if (CommOS==CommOS_WIN)
            PRINTF("------------------------------------------------------\n");
            PRINTF("%s", strQuery.c_str());
            PRINTF("\n\n");
#endif

            std::string strQueryUTF8 = Comm::Utils::StringTool::AnsiToUtf8(strQuery);

            try {
                int recCnt = 0;
                sql::ResultSet* res = statement->executeQuery(strQueryUTF8.c_str());
                assert(res);

                while (res->next()) {
                    std::shared_ptr<Database::Single::Record> record = std::make_shared<Database::Single::Record>(refRecord);
                    assert(record);
                    this->SelectReadRecordByIdx(res, record);
                    recCnt++;
                    recordVector.push_back(record);
                } //end of while (res->next()) {
                delete res;
            }
            catch (sql::SQLException& e) {
                if (e.getErrorCode() == 0) {
                    //CLOGI("Query [%s]... OK ", strQuery.c_str());
                }
                else {
                    CLOGE("# ERR: SQLException in %s (%s) on line", __FILE__, __FUNCTION__, __LINE__);
                    CLOGE("# ERR: %s", e.what());
                    CLOGE("   MySQL error code: %d, SQLState: %s", e.getErrorCode(), e.getSQLState().c_str());

                    CLOGE("Query [%s]... FAIL ", strQuery.c_str());
                    assert(0);
                }
            }

#ifdef ENABLE_CREATE_STATEMENT
            delete statement;
#endif

            return recordVector;
        }

        

        void* MySQL::TransactionSelectCreateHandle(std::string tableName, std::shared_ptr<Database::Single::Record> refRecord /*ref*/, std::shared_ptr<Database::Single::Record> whereRecord) {
        
            TransactionSelect* tr = new TransactionSelect;
            assert(tr);
            tr->_ReadRefRecord = refRecord;
            tr->_WhereRecord = whereRecord;
            tr->_SqlResult = NULL;

#ifdef ENABLE_CREATE_STATEMENT
            tr->_Statement = _Connection->createStatement();
            assert(tr->_Statement);
#else
            tr->_Statement = _Statement;;
            Comm::OAL::Lock lock(_Cs);
#endif

            std::vector<std::shared_ptr<Database::Single::Record>> recordVector;
            std::string colNameArr = tr->_ReadRefRecord->GetEnabledColumnNameSqlArgString();
            std::string whereString = tr->_WhereRecord->GetEnabledColumnValueSqlWhereString();
            std::string strQuery;

            if (whereString.size() > 0) {
                strQuery = Comm::Utils::StringFormat("select %s from %s where %s", colNameArr.c_str(), tableName.c_str(), whereString.c_str());
            }
            else {
                strQuery = Comm::Utils::StringFormat("select %s from %s", colNameArr.c_str(), tableName.c_str());
            }
            std::string strQueryUTF8 = Comm::Utils::StringTool::AnsiToUtf8(strQuery);


            try {
                tr->_SqlResult = tr->_Statement->executeQuery(strQueryUTF8.c_str());
                assert(tr->_SqlResult);
            }
            catch (sql::SQLException& e) {
                //if (e.getErrorCode() == 0) {
                    //CLOGI("Query [%s]... OK ", strQuery.c_str());
                //}
                //else {
                    CLOGE("# ERR: SQLException in %s (%s) on line", __FILE__, __FUNCTION__, __LINE__);
                    CLOGE("# ERR: %s", e.what());
                    CLOGE("   MySQL error code: %d, SQLState: %s", e.getErrorCode(), e.getSQLState().c_str());
                    CLOGE("Query [%s]... FAIL ", strQuery.c_str());
                    assert(0);
                //}
            }

            return (void*)tr;
        }

        bool MySQL::TransactionSelectDestroyHandle(void* hdl) {
        
            TransactionSelect* tr = (TransactionSelect*)hdl;
            assert(tr);
            tr->_ReadRefRecord.reset();
            tr->_WhereRecord.reset();
            if (tr->_SqlResult) {
                delete tr->_SqlResult;
            }

#ifdef ENABLE_CREATE_STATEMENT
            if (tr->_Statement) {
                delete tr->_Statement;
            }
#else
            tr->_Statement = NULL;
#endif

            delete tr;
            return true;
        }

        std::shared_ptr<Database::Single::Record> MySQL::TransactionSelectNext(void* hdl) {
        
            std::shared_ptr<Database::Single::Record> readRecord;
            TransactionSelect* tr = (TransactionSelect*)hdl;
            assert(tr);

            if (tr->_SqlResult->next()) {

                readRecord = std::make_shared<Database::Single::Record>(tr->_ReadRefRecord);
                assert(readRecord);
                this->SelectReadRecordByIdx(tr->_SqlResult, readRecord);
            }

            return readRecord;
        }

    }; //namespace RDBMS
}; //namespace OAL

