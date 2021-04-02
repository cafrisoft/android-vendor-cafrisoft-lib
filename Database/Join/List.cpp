#include <Database/Global/BuildOptions.h>
#include <Database/Join/List.hpp>

namespace Database {
    namespace Join {

        List::List() {
        
        }

        bool List::AddFirst(std::shared_ptr<Database::Single::Header> hdr) {
        
            assert(_FirstHeader == NULL);

            _FirstHeader = std::make_shared<Database::Single::Header>(hdr);
            assert(_FirstHeader);

            return true;
        }

        bool List::AddNext(std::shared_ptr<Database::Single::Header> hdrLeft, std::string tableColumnNameLeft, std::shared_ptr<Database::Single::Header> hdrRight, std::string tableColumnNameRight, Database::SqlType::Join joinType) {
        
            assert(_FirstHeader);
            
            assert(this->IsThisSingleTable(hdrLeft->GetTableName()) == true);
            assert(this->IsThisSingleTable(hdrRight->GetTableName()) == false);

            assert(hdrLeft);
            assert(hdrRight);
            assert(hdrLeft->IsThisTableDotColumnName(tableColumnNameLeft) == true);
            assert(hdrRight->IsThisTableDotColumnName(tableColumnNameRight) == true);

            
            std::shared_ptr<Node> node = std::make_shared<Node>();
            assert(node);
            node->_HeaderRight = std::make_shared< Database::Single::Header>(hdrRight);
            node->_JoinType = joinType;
            node->_TableColumnNameLeft = tableColumnNameLeft;
            node->_TableColumnNameRight = tableColumnNameRight;

            this->_NextNodeVector.push_back(node);


            return true;
        }

        std::string List::GetJoinedTableName() {
        
            std::string strJoinTableName;

            assert(_FirstHeader);
            std::string tableName = _FirstHeader->GetTableName();

            strJoinTableName = tableName;
            strJoinTableName += '\n';

            for(std::vector<std::shared_ptr<Node>>::const_iterator it = _NextNodeVector.cbegin();
                it != _NextNodeVector.cend();
                it++) {

                std::string joinName;

                switch ((*it)->_JoinType) {
                
                    case Database::SqlType::Join::Inner:
                        joinName = "inner join ";
                        break;

                    case Database::SqlType::Join::Left:
                        joinName = "left join ";
                        break;

                    case Database::SqlType::Join::Right:
                        joinName = "right join ";
                        break;

                    default:
                        assert(0);
                } 

                strJoinTableName += joinName;
                strJoinTableName += (*it)->_HeaderRight->GetTableName();
                strJoinTableName += " on ";

                strJoinTableName += (*it)->_TableColumnNameRight;
                strJoinTableName += '=';
                strJoinTableName += (*it)->_TableColumnNameLeft;

                strJoinTableName += '\n';
            }

            return strJoinTableName;
        }

        std::vector<std::shared_ptr<Database::Single::Column>> List::GetJoinedColumnVector() {
        
            int icol, colsz;
            std::vector<std::shared_ptr<Database::Single::Column>> colVec;

            assert(_FirstHeader);

            colsz = _FirstHeader->GetColumnCount();
            for (icol = 0; icol < colsz; icol++) {
                colVec.push_back(_FirstHeader->GetColumn(icol));
            }

            for (std::vector<std::shared_ptr<Node>>::const_iterator it = _NextNodeVector.cbegin();
                it != _NextNodeVector.cend();
                it++) {

                colsz = (*it)->_HeaderRight->GetColumnCount();
                for (icol = 0; icol < colsz; icol++) {
                    colVec.push_back((*it)->_HeaderRight->GetColumn(icol));
                }
            }

            return colVec;
        }

        std::vector<std::shared_ptr<Database::Single::Header>> List::GetJoinedHeader() {
        
            std::vector<std::shared_ptr<Database::Single::Header>> vec;
            return vec;
        }

        bool List::IsThisSingleTable(std::string tableName) {
        
            bool bRet = false;

            assert(_FirstHeader);
            bRet = _FirstHeader->IsThisTable(tableName);
            if (!bRet) {
            
                for (std::vector<std::shared_ptr<Node>>::const_iterator it = _NextNodeVector.cbegin();
                    it != _NextNodeVector.cend();
                    it++) {
                
                    std::shared_ptr<Node> node = *it;
                    assert(node->_HeaderRight);
                    bRet = node->_HeaderRight->IsThisTable(tableName);
                    if (bRet) {
                        break;
                    }
                }
            }

            return bRet;
        }

        bool List::IsThisTableColumnName(std::string tableColumnName) {
        
            bool bRet = false;

            assert(_FirstHeader);
            bRet = _FirstHeader->IsThisTableDotColumnName(tableColumnName);
            if (!bRet) {

                for (std::vector<std::shared_ptr<Node>>::const_iterator it = _NextNodeVector.cbegin();
                    it != _NextNodeVector.cend();
                    it++) {

                    std::shared_ptr<Node> node = *it;
                    assert(node->_HeaderRight);
                    bRet = node->_HeaderRight->IsThisTableDotColumnName(tableColumnName);
                    if (bRet) {
                        break;
                    }
                }
            }

            return bRet;
        }

    }; //namespace Join
}; //namespace Database

