#include "AppDefine.hpp"

#if (CommOS==CommOS_WIN)
#define MYSQL_SERVER_ADDR "205.239.162.119"
#elif (CommOS==CommOS_LINUX)
#define MYSQL_SERVER_ADDR "127.0.0.1"
#else
#error "ERROR: Select OS"
#endif

#if (CommOS==CommOS_WIN)
//#define MYSQL_SERVER_PORT 3306
#define MYSQL_SERVER_PORT 12919
#elif (CommOS==CommOS_LINUX)
#define MYSQL_SERVER_PORT 12919
#else
#error "Select OS"
#endif
#define MYSQL_ACCOUNT_ID "anapass"
#define MYSQL_ACCOUNT_PW "ana!@34"

namespace TESysDB {
  
    void Connect() {

        bool bRet;
        bRet = Database::RDBMS::Base::CreateInstance(Database::RDBMS::Type::MySQL);
        assert(bRet);

        bRet = Database::RDBMS::Base::Inst()->Connect(MYSQL_SERVER_ADDR, MYSQL_SERVER_PORT, MYSQL_ACCOUNT_ID, MYSQL_ACCOUNT_PW);
        if (!bRet) {
            printf("FAIL: connect to mysql server \n");
            exit(0);
        }
        else {
            Database::RDBMS::Base::Inst()->SelectSchema("TESysDB");
        }

    }

    void Disconnect() {

        Database::RDBMS::Base::Inst()->Disconnect();
        Database::RDBMS::Base::DestroyInstance();
    }

};
