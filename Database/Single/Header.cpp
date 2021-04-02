#include <Database/Global/BuildOptions.h>
#include <Database/Single/Header.hpp>
#include <Comm/OAL/Log.hpp>

namespace Database {
    namespace Single {

        Header::Header(std::string tableName, std::vector<std::shared_ptr<Column>> columnVector) :
            _TableName(tableName)
        {

            _ColumnCount = (int)columnVector.size();
            _ColumnArray = new std::shared_ptr<Column>[_ColumnCount];
            assert(_ColumnArray);

            for (int i = 0; i < _ColumnCount; i++) {

                std::shared_ptr<Column> col = columnVector[i];
                _ColumnArray[i] = std::make_shared<Column>(col);
                assert(_ColumnArray[i]);
            }

        }

        Header::Header(std::string tableName, std::vector<struct Column::Property> columnPropVec) :
            _TableName(tableName)
        {
            
            _ColumnCount = (int)columnPropVec.size();
            _ColumnArray = new std::shared_ptr<Column>[_ColumnCount];
            assert(_ColumnArray);

            for (int i = 0; i < _ColumnCount; i++) {
                
                struct Column::Property prop = columnPropVec[i];
                assert(prop.columnID == i);
                _ColumnArray[i] = std::make_shared<Column>(tableName, &prop);
                assert(_ColumnArray[i]);
            }

        }

        Header::Header(std::string tableName, const struct Column::Property columnPropVec[], int propCnt) :
        _TableName(tableName)
        {
        
            _ColumnCount = propCnt;
            _ColumnArray = new std::shared_ptr<Column>[_ColumnCount];
            assert(_ColumnArray);

            for (int i = 0; i < _ColumnCount; i++) {
                const struct Column::Property* pProp = &columnPropVec[i];
                assert(pProp->columnID == i);
                _ColumnArray[i] = std::make_shared<Column>(tableName, pProp);
                assert(_ColumnArray[i]);
            }
        }

        Header::Header(const std::shared_ptr<Header> obj) {
        
            _TableName = obj->_TableName;
            _ColumnCount = obj->_ColumnCount;
            _ColumnArray = new std::shared_ptr<Column>[_ColumnCount];
            assert(_ColumnArray);

            for (int i = 0; i < _ColumnCount; i++) {
                std::shared_ptr<Column> col = obj->_ColumnArray[i];
                _ColumnArray[i] = std::make_shared<Column>(col);
                assert(_ColumnArray[i]);
            }
        }
       
        int Header::GetColumnCount() {
            return _ColumnCount;
        }

        std::string Header::GetTableName() {
        
            return _TableName;
        }

        std::string Header::GetTableName(int colIdx) {

            assert((colIdx >= 0) && (colIdx < _ColumnCount));

            return _ColumnArray[colIdx]->GetTableName();
        }

        std::string Header::GetTableDotColumnName(int colIdx) {

            assert((colIdx >= 0) && (colIdx < _ColumnCount));

            return _ColumnArray[colIdx]->GetTableDotColumnName();
        }

        std::string Header::GetColumnName(int colIdx) {

            assert((colIdx >= 0) && (colIdx < _ColumnCount));

            return _ColumnArray[colIdx]->GetColumnName();
        }

        std::shared_ptr<Column> Header::GetColumn(int colIdx) {
                    
            assert((colIdx >= 0) && (colIdx < _ColumnCount));
            
            return _ColumnArray[colIdx];
        }

        Comm::VarType::SQL Header::GetColumnSqlVarType(int colIdx) {
        
            assert((colIdx >= 0) && (colIdx < _ColumnCount));

            return _ColumnArray[colIdx]->GetSqlVarType();
        }

        long long  Header::GetColumnMaxByteSize(int colIdx) {
        
            assert((colIdx >= 0) && (colIdx < _ColumnCount));

            return _ColumnArray[colIdx]->GetMaxDataByteSize();
        }

        bool Header::IsThisTable(std::string tableName) {
        
            bool bRet = false;

            if (tableName == _TableName) {
                bRet = true;
            }

            return bRet;
        }

        bool Header::IsThisTableDotColumnName(std::string tableColumnName) {

            bool bRet = false;

            for (int icol = 0; icol < _ColumnCount; icol++) {
            
                bRet = _ColumnArray[icol]->IsThisTableDotColumnName(tableColumnName);
                if (bRet) {
                    break;
                }
            }

            return bRet;
        }

    }; //namespace SQL 
}; //namespace Database

