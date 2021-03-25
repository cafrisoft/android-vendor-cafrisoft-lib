#ifndef DATABASE_JOIN_LIST_HPP__
#define DATABASE_JOIN_LIST_HPP__

#include <Database/Global/BuildOptions.h>
#include <Database/Single/Table.hpp>

namespace Database {
    namespace Join {

        class List : public Comm::Base::Object {

        private:
            /*
              New Joined Table =  SingleTable(Left) <join>  SingleTable(Right)
            */
            class Node {
            public:
                std::shared_ptr<Database::Single::Header> _HeaderRight;
                Database::SqlType::Join _JoinType;
                std::string _TableColumnNameLeft; // [Table].[Column]
                std::string _TableColumnNameRight; // [Table].[Column]
            };

        private:
            std::shared_ptr<Database::Single::Header> _FirstHeader;
            std::vector<std::shared_ptr<Node>> _NextNodeVector;

        public:
            List();

        protected:
            bool AddFirst(std::shared_ptr<Database::Single::Header> hdr);
            bool AddNext(std::shared_ptr<Database::Single::Header> hdrLeft, std::string tableColumnNameLeft, std::shared_ptr<Database::Single::Header> hdrRight, std::string tableColumnNameRight, Database::SqlType::Join joinType);
        
            std::vector<std::shared_ptr<Database::Single::Header>> GetJoinedHeader();

        public:
            bool IsThisSingleTable(std::string tableName);
            bool IsThisTableColumnName(std::string tableColumnName);

        public:
            std::string GetJoinedTableName();
            std::vector<std::shared_ptr<Database::Single::Column>> GetJoinedColumnVector();

        };

    }; //namespace Table
}; //namespace Database


#endif

