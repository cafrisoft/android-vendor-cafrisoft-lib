#define CLOG_TAG "RDBMSMySQL"
#include <Comm/Database/RDBMS/MySQL.hpp>
#include <Comm/OAL/Lock.hpp>
#include <Comm/Utils/StringTool.hpp>
#include <Comm/OAL/Log.hpp>

namespace Comm {
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
        
            if (_ResultSet) {
                delete _ResultSet;
            }

            if (_Statement) {
                delete _Statement;
            }

            if (_Connection) {
                delete _Connection;
            }

        }

        bool MySQL::Connect(std::string strServerIP) {

            bool bRet = false;
            Comm::OAL::Lock lock(_Cs);

            std::string strConn = Comm::Utils::StringFormat("tcp://%s:3306", strServerIP.c_str());
            _Connection = _Driver->connect(strConn.c_str(), "root", "1234");
            if (_Connection) {
                bRet = true;

                _Statement = _Connection->createStatement();
                assert(_Statement);
            }

            return bRet;
        }

        bool MySQL::Disconnect() {

            Comm::OAL::Lock lock(_Cs);

            if (_Statement) {
                delete _Statement;
                _Statement = NULL;
            }

            if (_Connection) {
                delete _Connection;
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
        
            assert(_Connection);

            _Connection->setSchema(strSchema.c_str());

            return true;
        }

        bool MySQL::ExecuteQuery(std::string strQuery, QueryResult* queryRes) {
        
            bool bRet = false;
            Comm::OAL::Lock lock(_Cs);

#if (CommOS==CommOS_WIN)
            std::string strQueryUTF8 = Comm::Utils::StringTool::AnsiToUTF8(strQuery);
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
        }
        
        }; //namespace RDBMS
    }; //namespace OAL
}; //namespace Comm
