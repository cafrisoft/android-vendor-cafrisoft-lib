#include <Database/RDBMS/Base.hpp>
#include <Database/RDBMS/MySQL.hpp>
#include <Comm/Utils/StringTool.hpp>


namespace Database {
    namespace RDBMS {

        std::shared_ptr<Base> Base::s_Instance;

        bool Base::CreateInstance(Type product) {

            std::shared_ptr<Base> obj;

            switch (product) {

            case Type::MySQL:
                obj = std::make_shared<MySQL>();
                break;
            }
            assert(obj);

            s_Instance = obj;

            return true;
        }

        bool Base::DestroyInstance() {
            if (s_Instance.get() != NULL) {
                s_Instance.reset();
            }
            return true;
        }

        std::shared_ptr<Base> Base::Inst() {
        
            return s_Instance;
        }

        Base::Base() {
        
        }
        
        int Base::QueryInt(std::string tableName, std::string getColName, std::string whereColName, int whereColValue, int defaultValue) {
       
            std::string strQuery = Comm::Utils::StringFormat("select %s from %s where %s=%d", getColName.c_str(), tableName.c_str(), whereColName.c_str(), whereColValue);
            return this->QueryInt(strQuery, getColName, defaultValue);
        }

        bool Base::QueryInsert(std::string tableName, std::vector<std::string> strValueVec) {

            //std::string strQuery = Comm::Utils::StringFormat("select %s from %s where %s=%d", getColName.c_str(), tableName.c_str(), whereColName.c_str(), whereColValue);
            //std::string strQuery = Comm::Utils::StringFormat("insert into %s (ID, DutCount) values ('%d', '%d')", tableName.c_str(), boardID, dutCount);

            bool bRet;
            int queryStrAllocByteSize = 1024;
            char* szQuery;

            for (std::vector<std::string>::const_iterator it = strValueVec.cbegin();
                it != strValueVec.cend();
                it++) {
                queryStrAllocByteSize +=  (int)it->size() + 10;
            }

            szQuery = new char[queryStrAllocByteSize];
            assert(szQuery);

            sprintf(szQuery, "insert into %s values (", tableName.c_str());

            for (std::vector<std::string>::const_iterator it = strValueVec.cbegin();
                it != strValueVec.cend();
                it++) {

                if (it != strValueVec.cbegin()) {
                    strcat(szQuery, ", ");
                }

                strcat(szQuery, "'");
                strcat(szQuery, it->c_str());
                strcat(szQuery, "'");

            }
            strcat(szQuery, ")");

            bRet = this->QueryInsert(szQuery);

            delete [] szQuery;

            return bRet;
        }

        bool Base::InsertRecord(std::string tableName, std::shared_ptr<Database::Single::Record> record, bool isDebug) {
        
            bool bRet;
            int queryStrAllocByteSize = 1024;
            char* szQuery;

            //std::vector<std::string> strValueVec = record->ToStringVectorForInsert();
            std::vector<std::string> strValueVec = record->ToStringVector();

            for (std::vector<std::string>::const_iterator it = strValueVec.cbegin();
                it != strValueVec.cend();
                it++) {
                queryStrAllocByteSize += (int)it->size() + 10;
            }

            szQuery = new char[queryStrAllocByteSize];
            assert(szQuery);

            sprintf(szQuery, "insert into %s values (", tableName.c_str());

            for (std::vector<std::string>::const_iterator it = strValueVec.cbegin();
                it != strValueVec.cend();
                it++) {

                if (it != strValueVec.cbegin()) {
                    strcat(szQuery, ", ");
                }

                strcat(szQuery, "'");
                strcat(szQuery, it->c_str());
                strcat(szQuery, "'");

            }
            strcat(szQuery, ")");

            bRet = this->QueryInsert(szQuery, isDebug);

            delete[] szQuery;

            return bRet;

        }

        bool Base::SelectData(std::string tableName, std::shared_ptr<Database::Single::Record> record /*OUT*/, std::shared_ptr<Database::Single::Record> whereRecord, bool isDebug) {
        
            std::string whereString = whereRecord->GetEnabledColumnValueSqlWhereString();

            return this->SelectData(tableName, record, whereString, isDebug);
        }

        std::vector<std::shared_ptr<Database::Single::Record>> Base::SelectMultiData(std::string tableName, 
                                                                               std::shared_ptr<Database::Single::Record> record /*ref*/, 
                                                                               std::shared_ptr<Database::Single::Record> whereRecord) 
        {
            std::string whereString;
            
            if (whereRecord != NULL) {
                whereString = whereRecord->GetEnabledColumnValueSqlWhereString();
            }

            return this->SelectMultiData(tableName, record, whereString);
        }
                
        bool Base::UpdateData(std::string tableName, std::shared_ptr<Database::Single::Record> record, std::shared_ptr<Database::Single::Record> whereRecord) {

            std::string whereString = whereRecord->GetEnabledColumnValueSqlWhereString();
            std::string updateString = record->GetEnabledColumnValueSqlUpdateString();
            
            return this->UpdateData(tableName, updateString, whereString);
        }


    }; //namespace BaseClass {
}; //namespace OAL

