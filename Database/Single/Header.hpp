#ifndef DATABASE_TABLE_HEADER_HPP__
#define DATABASE_TABLE_HEADER_HPP__

#include <Database/Single/Column.hpp>


namespace Database {
    namespace Single {

        class Header : public Comm::Base::Object {

        protected:
            std::string _TableName;
            int _ColumnCount;
            std::shared_ptr<Column> *_ColumnArray;

        public:
            Header(std::string tableName, std::vector<std::shared_ptr<Column>> columnVector);
            Header(std::string tableName, std::vector<struct Column::Property> columnPropVec);
            Header(std::string tableName, const struct Column::Property columnPropVec[], int propCnt);
            Header(const std::shared_ptr<Header> obj);

        public:
            std::string GetTableName();
            std::string GetTableName(int colIdx);
            int GetColumnCount();
            std::string GetTableDotColumnName(int  colIdx);
            std::string GetColumnName(int  colIdx);
            std::shared_ptr<Column> GetColumn(int colIdx);
            Comm::VarType::SQL GetColumnSqlVarType(int colIdx);
            long long  GetColumnMaxByteSize(int colIdx);

            bool IsThisTable(std::string tableName);
            bool IsThisTableDotColumnName(std::string tableColumnName);
        };

    }; //namespace Table
}; //namespace Database


#endif

