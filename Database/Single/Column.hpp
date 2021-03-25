#ifndef DATABASE_SINGLE_COLUMN_HPP__
#define DATABASE_SINGLE_COLUMN_HPP__

#include <Database/Global/BuildOptions.h>
#include <Database/QueryResult.hpp>
#include <Comm/VarType.hpp>

namespace Database {
    namespace Single {

        
        class Column : public Comm::Base::Object {

        public:
            enum {
                 _MaxNameByteSize = 128
            };
            
        public:
            struct Property {
                int columnID;
                char szColumnName[_MaxNameByteSize];
                Comm::VarType::SQL sqlVarType;
                long long maxDataByteSize;
                unsigned int attr;
            };

            class Attr {
            public:
                enum class Bit {
                    PrimaryKey = 0,     // BIT 0  
                    NotNull  = 1,       // BIT 1
                    Unique   = 2,       // BIT 2
                    Binary = 3,         // BIT 3
                    Unsigned = 4,       // BIT 4
                    ZeroFill = 5,       // BIT 5
                    AutoIncrement = 6,  // BIT 6  
                    Generated = 7,      // BIT 7  
                    AritificalKey=8,    // 여러개의 PrimaryKey를 대표하는 대체키 
                };

            private:
                static unsigned int GenValue(unsigned int curErrFlag, Bit errflagbit);

            public:
                static bool IsEnable(unsigned int curErrFlag, Bit errflagbit);

                static unsigned int GetDefault();
                static unsigned int Get_AK();    //Artificial Key, 
                static unsigned int Get_PK();    //Primary Key, 
                static unsigned int Get_PK_AI(); //Primary Key,  Auto Increment 
                static bool IsPrimaryKey(unsigned int attr);
                static bool IsAutoIncrement(unsigned int attr);
            };

        private:
            std::string _TableName;    // Column/Table 이름이 ID여야 한다.
            std::string _ColumnName;
            Comm::VarType::SQL _SqlVarType;
            long long _MaxDataByteSize;
            unsigned int _Attr;

        public:
            Column(std::string tableName, const struct Property* prop);
            Column(const std::shared_ptr<Column> column);
            virtual ~Column();

        public:
            std::string GetTableName();
            std::string GetColumnName();
            std::string GetTableDotColumnName();
            Comm::VarType::SQL GetSqlVarType();
            long long GetMaxDataByteSize();
            
            bool IsPrimaryKey();
            bool IsArtificialKey();
            bool IsAutoIncrement();
            bool IsThisTableDotColumnName(std::string tableColumnName);
        };

    }; //namespace Table
}; //namespace Database


#endif

