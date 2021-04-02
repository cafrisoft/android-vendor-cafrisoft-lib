#include <Database/Global/BuildOptions.h>
#include <Database/Single/Column.hpp>
#include <Comm/Utils/StringTool.hpp>
#include <Comm/OAL/DateTime.hpp>


namespace Database {
    namespace Single {

        /***************************************************************************************************************************

            class Column::Attr

        ***************************************************************************************************************************/
                
        unsigned int Column::Attr::GenValue(unsigned int curErrFlag, Bit errflagbit) {

            unsigned int errBit = (unsigned int)errflagbit;
            unsigned int seedValue = 1;
            unsigned int newErrFlag = curErrFlag | (seedValue << errBit);
            return newErrFlag;
        }

        bool Column::Attr::IsEnable(unsigned int curErrFlag, Bit errflagbit) {

            unsigned int errBit = (unsigned int)errflagbit;
            unsigned int seedValue = 1;
            bool bflag  = ((curErrFlag&(seedValue << errBit)) != 0) ? true : false;
            return bflag;
        }

        unsigned int Column::Attr::GetDefault() {
            return 0;
        }

        unsigned int Column::Attr::Get_AK() {
            int attr = GetDefault();
            attr = GenValue(attr, Bit::AritificalKey);
            return attr;
        }

        unsigned int Column::Attr::Get_PK() {
            int attr = GetDefault();
            attr = GenValue(attr, Bit::PrimaryKey);
            return attr;
        }

        unsigned int Column::Attr::Get_PK_AI() {
            int attr = GetDefault();
            attr = GenValue(attr, Bit::PrimaryKey);
            attr = GenValue(attr, Bit::AutoIncrement);
            return attr;
        }

        bool Column::Attr::IsPrimaryKey(unsigned int attr) {
        
            return IsEnable(attr, Bit::PrimaryKey);
        }

        bool Column::Attr::IsAutoIncrement(unsigned int attr) {
        
            return IsEnable(attr, Bit::AutoIncrement);
        }

        /***************************************************************************************************************************

            class Column

        ***************************************************************************************************************************/

        Column::Column(std::string tableName, const struct Property* prop) :
            _TableName(tableName)
            , _ColumnName(prop->szColumnName)
            , _SqlVarType(prop->sqlVarType)
        {


            if (prop->maxDataByteSize > 0) {

                if (_SqlVarType == Comm::VarType::SQL::VarChar) {
                    _MaxDataByteSize = prop->maxDataByteSize + 1;
                }
                else {
                    _MaxDataByteSize = prop->maxDataByteSize;
                }
            }
            else {
                _MaxDataByteSize = Comm::VarType::VarTypeMaxByteSize(_SqlVarType);
            }

            _Attr = prop->attr;
        }

        Column::Column(const std::shared_ptr<Column> column) {
        
            _TableName = column->_TableName;
            _ColumnName = column->_ColumnName;
            _SqlVarType = column->_SqlVarType;
            _MaxDataByteSize = column->_MaxDataByteSize;
            _Attr = column->_Attr;
        }

        Column::~Column() {

        }

        std::string Column::GetTableName() {
        
            return _TableName;
        }

        std::string Column::GetColumnName() {

            return _ColumnName;
        }
        
        std::string Column::GetTableDotColumnName() {

            std::string str = _TableName;
            str += '.';
            str += _ColumnName;

            return str;
        }

        long long Column::GetMaxDataByteSize() {

            return _MaxDataByteSize;
        }

        Comm::VarType::SQL Column::GetSqlVarType() {

            return _SqlVarType;
        }

        bool Column::IsPrimaryKey() {
        
            return Attr::IsPrimaryKey(_Attr);
        }

        bool Column::IsArtificialKey() {

            return Attr::IsEnable(_Attr, Attr::Bit::AritificalKey);
        }

        bool Column::IsAutoIncrement() {
        
            return Attr::IsAutoIncrement(_Attr);
        }
    
        bool Column::IsThisTableDotColumnName(std::string tableColumnName) {
        
            bool bRet = false;
            std::string str = this->GetTableDotColumnName();
            if (str == tableColumnName) {
                bRet = true;
            }
            return bRet;
        }

    }; //namespace SQL 
}; //namespace Database

