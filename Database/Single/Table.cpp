#define CLOG_TAG "DatabaseSingleTable"
#include <Database/Single/Table.hpp>
#include <Database/RDBMS/Base.hpp>
#include <Comm/OAL/Log.hpp>

namespace Database {
    namespace Single {

        
        Table::Table(std::shared_ptr<Header> header) :
            _TableName(header->GetTableName())
            , _Header(header)
        {
            _Cs = Comm::OAL::CriticalSection::CreateObject();
            assert(_Cs);

        }

        std::string Table::GetTableName() {
        
            return _TableName;
        }

        std::shared_ptr<Header> Table::GetHeader() {

            return _Header;
        }
        
        std::string Table::GetTableDotColumnName(int colIdx) {

            std::string name;

            name = _TableName;
            name += '.';
            name += _Header->GetColumnName(colIdx);

            return name;
        }

        int Table::GetColumnCount() {
        
            return _Header->GetColumnCount();
        }

        std::string Table::GetColumnName(int colIdx) {

            return _Header->GetColumnName(colIdx);
        }

        Comm::VarType::SQL Table::GetColumnSqlVarType(int colIdx) {
        
            return _Header->GetColumnSqlVarType(colIdx);
        }

        long long Table::GetColumnMaxByteSize(int colIdx) {
        
            return _Header->GetColumnMaxByteSize(colIdx);
        }

        int Table::QuerySelectInt(int getColID, int whereColID, int whereColValue, int defaultValue) {

            std::string getColName = _Header->GetColumnName(getColID);
            std::string whereColName = _Header->GetColumnName(whereColID);

            return Database::RDBMS::Base::Inst()->QueryInt(_TableName, getColName, whereColName, whereColValue, defaultValue);
        }

        bool Table::IsThisPKInternal(std::shared_ptr<Record> inputRecord, bool isDebug) {
        
            bool isThisRec = false;

            //where Record 설정 
            std::shared_ptr<Database::Single::Record> whereKeyRecord = std::make_shared<Database::Single::Record>(inputRecord);
            whereKeyRecord->EnableOnlyAllPK();

            //record 생성 
            std::shared_ptr<Database::Single::Record> readRecord = std::make_shared<Database::Single::Record>(this);
            assert(readRecord);
            readRecord->EnableOnlyAllPK();
            
            bool bRet = Database::RDBMS::Base::Inst()->SelectData(_TableName, readRecord, whereKeyRecord, isDebug);
            if (bRet) {

                if (readRecord->IsEqualData(whereKeyRecord)) {
                    isThisRec = true;
                }
            }

            return isThisRec;
        }

        //입력된 whereRecord의 PK값이 같은 Record가 Table안에 존재하는가?
        bool Table::IsThisPK(std::shared_ptr<Record> whereKeyRecord) {
        
            Comm::OAL::Lock lock(_Cs);

            return this->IsThisPKInternal(whereKeyRecord);
        }

        bool Table::InsertInternal(std::shared_ptr<Record> record, bool isDebug) {
        
            bool bRet;

            if (IsThisPKInternal(record, isDebug) == true) {
                bRet = false;
            }
            else {
                std::shared_ptr<Database::Single::Record> updateRecord = std::make_shared<Database::Single::Record>(record);
                assert(updateRecord);
                updateRecord->EnableAll();

                bRet = Database::RDBMS::Base::Inst()->InsertRecord(_TableName, updateRecord, isDebug);
                assert(bRet);
            }

            return bRet;
        }

        bool Table::SelectWithPKInternal(std::shared_ptr<Record> readRecord, std::shared_ptr<Record> whereRecord) {

            whereRecord->EnableOnlyAllPK();

            return Database::RDBMS::Base::Inst()->SelectData(_TableName, readRecord, whereRecord);
        }

        bool Table::SelectInternal(std::shared_ptr<Record> readRecord, unsigned int ak) {

            std::shared_ptr<Record> whereRecord = std::make_shared<Record>(this);
            assert(whereRecord);
            whereRecord->SetValue(_AkColumnIndex, ak);
            whereRecord->Enable(_AkColumnIndex);

            return Database::RDBMS::Base::Inst()->SelectData(_TableName, readRecord, whereRecord);
        }

        bool Table::SelectInternal(std::shared_ptr<Record> readRecord, long long ak) {

            int akIdx = readRecord->GetAKIdx();
            assert(akIdx >= 0);

            std::shared_ptr<Record> whereRecord = std::make_shared<Record>(this);
            assert(whereRecord);
            whereRecord->SetValueBigInt(akIdx, ak);
            whereRecord->Enable(akIdx);

            return Database::RDBMS::Base::Inst()->SelectData(_TableName, readRecord, whereRecord);
        }

        bool Table::SelectInternal(std::shared_ptr<Record> readRecord, std::shared_ptr<Record> whereRecord) {

            return Database::RDBMS::Base::Inst()->SelectData(_TableName, readRecord, whereRecord);
        }

        std::vector<std::shared_ptr<Record>> Table::SelectRecordVecInternal(std::shared_ptr<Record> readRecord, std::shared_ptr<Record> whereRecord) {

            return Database::RDBMS::Base::Inst()->SelectMultiData(_TableName, readRecord, whereRecord);
        }

        bool Table::UpdateInternal(std::shared_ptr<Record> record, unsigned int ak) {

            std::shared_ptr<Record> whereRecord = std::make_shared<Record>(this);
            assert(whereRecord);
            whereRecord->SetValue(_AkColumnIndex, ak);
            whereRecord->Enable(_AkColumnIndex);

            return Database::RDBMS::Base::Inst()->UpdateData(_TableName, record, whereRecord);
        }

        bool Table::UpdateInternal(std::shared_ptr<Record> record, long long ak) {

            int akIdx = record->GetAKIdx();
            assert(akIdx >= 0);

            std::shared_ptr<Record> whereRecord = std::make_shared<Record>(this);
            assert(whereRecord);
            whereRecord->SetValueBigInt(akIdx, ak);
            whereRecord->Enable(akIdx);

            std::shared_ptr<Record> updateRecord = std::make_shared<Record>(record);
            assert(updateRecord);
            updateRecord->Disble(akIdx);

            return Database::RDBMS::Base::Inst()->UpdateData(_TableName, updateRecord, whereRecord);
        }

        bool Table::UpdateInternal(std::shared_ptr<Record> record, std::shared_ptr<Record> whereRecord) {

            std::shared_ptr<Record> updateRecord = std::make_shared<Record>(record);
            assert(updateRecord);

            return Database::RDBMS::Base::Inst()->UpdateData(_TableName, updateRecord, whereRecord);
        }

        bool Table::InsertRecord(std::shared_ptr<Record> record, bool isDebug) {

            Comm::OAL::Lock lock(_Cs);

            return this->InsertInternal(record, isDebug);
        }

        bool Table::SelectWithPK(std::shared_ptr<Record> record, std::shared_ptr<Record> whereRecord) {
        
            Comm::OAL::Lock lock(_Cs);

            return this->SelectWithPKInternal(record, whereRecord);
        }

        bool Table::SelectRecord(std::shared_ptr<Record> record, unsigned int ak) {
        
            Comm::OAL::Lock lock(_Cs);

            return this->SelectInternal(record, ak);
        }
        
        bool Table::SelectRecord(std::shared_ptr<Record> record, long long ak) {

            Comm::OAL::Lock lock(_Cs);

            return this->SelectInternal(record, ak);
        }

        bool Table::SelectRecord(std::shared_ptr<Record> record, std::shared_ptr<Record> whereRecord) {

            Comm::OAL::Lock lock(_Cs);

            return this->SelectInternal(record, whereRecord);
        }

        std::vector<std::shared_ptr<Record>> Table::SelectRecordVec(std::shared_ptr<Record> record, std::shared_ptr<Record> whereRecord) {
        
            Comm::OAL::Lock lock(_Cs);

            return this->SelectRecordVecInternal(record, whereRecord);
        }

        bool Table::Update(std::shared_ptr<Record> record, unsigned int ak) {
        
            Comm::OAL::Lock lock(_Cs);

            return this->UpdateInternal(record, ak);
        }

        bool Table::Update(std::shared_ptr<Record> record, long long ak) {

            Comm::OAL::Lock lock(_Cs);

            return this->UpdateInternal(record, ak);
        }

        bool Table::UpdateRecord(std::shared_ptr<Record> record, std::shared_ptr<Record> whereRecord) {
        
            Comm::OAL::Lock lock(_Cs);

            return this->UpdateInternal(record, whereRecord);
        }


        long long Table::GetAK_BigInt_ByPK(std::shared_ptr<Record> record, bool isDebug) {
        
            long long akValue = -1LL;

            Comm::OAL::Lock lock(_Cs);

            //where Record 설정 
            std::shared_ptr<Record> whereKeyRecord = std::make_shared<Record>(record);
            assert(whereKeyRecord);
            whereKeyRecord->EnableOnlyAllPK();

            //record 생성 
            std::shared_ptr<Database::Single::Record> readRecord = std::make_shared<Database::Single::Record>(this);
            assert(readRecord);
            readRecord->EnableOnlyAK();

            bool bRet = Database::RDBMS::Base::Inst()->SelectData(_TableName, readRecord, whereKeyRecord, isDebug);
            if (bRet) {
                int akIdx = readRecord->GetAKIdx();
                assert(akIdx >= 0);
                akValue = readRecord->GetValueBigInt(akIdx);
            }
            
            return akValue;
        }

        int Table::GetAK_Int_ByPK(std::shared_ptr<Record> record, bool isDebug) {

            int akValue = -1;

            Comm::OAL::Lock lock(_Cs);

            //where Record 설정 
            std::shared_ptr<Record> whereKeyRecord = std::make_shared<Record>(record);
            assert(whereKeyRecord);
            whereKeyRecord->EnableOnlyAllPK();

            //record 생성 
            std::shared_ptr<Database::Single::Record> readRecord = std::make_shared<Database::Single::Record>(this);
            assert(readRecord);
            readRecord->EnableOnlyAK();

            bool bRet = Database::RDBMS::Base::Inst()->SelectData(_TableName, readRecord, whereKeyRecord, isDebug);
            if (bRet) {
                int akIdx = readRecord->GetAKIdx();
                assert(akIdx >= 0);
                akValue = readRecord->GetValueInt(akIdx);
            }

            return akValue;
        }

        std::shared_ptr<Record> Table::GetRecord() {
            std::shared_ptr<Record> record = std::make_shared<Record>(this);
            assert(record);
            return record;
        }

        std::shared_ptr<Record> Table::GetRecord(int enableColumnIdx) {
        
            std::shared_ptr<Record> record = std::make_shared<Record>(this);
            assert(record);
            record->Enable(enableColumnIdx);
            return record;
        }

        std::shared_ptr<Record> Table::GetRecord_EnabledAK() {

            return this->GetRecord(0);
        }

        void Table::PrintColumnNameForPython() {
        
            int colCnt = _Header->GetColumnCount();
            for (int colIdx = 0; colIdx < colCnt; colIdx++) {
                std::string tableName = _Header->GetTableName(colIdx);
                std::string colName = _Header->GetColumnName(colIdx); 
                PRINTF("%s_%s=%d\n", tableName.c_str(), colName.c_str(), colIdx);
            }

        }

        void Table::PrintPythonColumnID() {

            const char* TAB = "    ";

            PRINTF("class ColumnID : \n");

            int colCnt = _Header->GetColumnCount();
            std::string beforeTableName;
            for (int colIdx = 0; colIdx < colCnt; colIdx++) {
                std::string tableName = _Header->GetTableName(colIdx);
                std::string colName = _Header->GetColumnName(colIdx);

                if (tableName != beforeTableName) {
                    PRINTF("%sclass %s(enum.IntEnum) : \n", TAB, tableName.c_str());
                    beforeTableName = tableName;
                }
            
                PRINTF("%s%s%s=%d\n", TAB, TAB, colName.c_str(), colIdx);
            }

        }
                
    }; //namespace Table
}; //namespace Database


