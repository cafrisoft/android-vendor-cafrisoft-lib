#include <Database/Global/BuildOptions.h>
#include <Database/Single/Record.hpp>
#include <Database/Single/Table.hpp>
#include <Comm/OAL/Log.hpp>
#include <Comm/Utils/StringTool.hpp>

namespace Database {
    namespace Single {

        Record::Record(Table* pTable) 
        {
            std::shared_ptr<Header> hdr = pTable->GetHeader();

            _ColumnCount = hdr->GetColumnCount();
            assert(_ColumnCount > 0);

            _DataArray = new std::shared_ptr<Data>[_ColumnCount];
            assert(_DataArray);

            for (int i = 0; i < _ColumnCount; i++) {

                std::shared_ptr<Column> col = hdr->GetColumn(i);
                assert(col);

                std::shared_ptr<Data> d = std::make_shared<Data>(col);
                assert(d);

                _DataArray[i] = d;
            }

        }

        Record::Record(std::string tableName, const struct Column::Property columnPropVec[], int propCnt) 
        {
            std::shared_ptr<Header> hdr = std::make_shared<Header>(tableName, columnPropVec, propCnt);

            _ColumnCount = hdr->GetColumnCount();
            assert(_ColumnCount > 0);

            _DataArray = new std::shared_ptr<Data>[_ColumnCount];
            assert(_DataArray);

            for (int i = 0; i < _ColumnCount; i++) {

                std::shared_ptr<Column> col = hdr->GetColumn(i);
                assert(col);

                std::shared_ptr<Data> d = std::make_shared<Data>(col);
                assert(d);

                _DataArray[i] = d;
            }

        }

        Record::Record(std::shared_ptr<Record> obj) {
        
            _ColumnCount = obj->_ColumnCount;
            _DataArray = new std::shared_ptr<Data>[_ColumnCount];
            assert(_DataArray);

            for (int i = 0; i < _ColumnCount; i++) {

                std::shared_ptr<Data> ds = obj->_DataArray[i];
                std::shared_ptr<Data> dt = std::make_shared<Data>(ds);
                assert(dt);
                _DataArray[i] = dt;
            }

        }

        Record::~Record() {
            delete[] _DataArray;
        }

        int Record::GetColumnCount() {

            return _ColumnCount;
        }

        void Record::EnableAll() {

            for (int dIdx = 0; dIdx < _ColumnCount; dIdx++) {

                _DataArray[dIdx]->Enable();
            }

        }

        void Record::EnableOnlyAllPK() {

            for (int dIdx = 0; dIdx < _ColumnCount; dIdx++) {

                std::shared_ptr<Data> d = _DataArray[dIdx];
                if (d) {
                    if (d->IsPrimaryKey()) {
                        d->Enable();
                    }
                    else {
                        d->Disable();
                    }
                }
            }

        }

        void Record::EnableOnlyAK() {

            for (int dIdx = 0; dIdx < _ColumnCount; dIdx++) {

                std::shared_ptr<Data> d = _DataArray[dIdx];
                if (d) {
                    if (d->IsArtificialKey()) {
                        d->Enable();
                    }
                    else {
                        d->Disable();
                    }
                }
            }

        }

        int Record::GetAKIdx() {

            int akIdx = -1;

            for (int dIdx = 0; dIdx < _ColumnCount; dIdx++) {

                std::shared_ptr<Data> d = _DataArray[dIdx];
                if (d) {
                    if (d->IsArtificialKey()) {
                        akIdx = dIdx;
                        break;
                    }
                }
            }

            return akIdx;
        }

        bool Record::IsEnableAll() {

            bool isEnableAll = true;

            for (int dIdx = 0; dIdx < _ColumnCount; dIdx++) {

                if (!_DataArray[dIdx]->IsEnable()) {
                    isEnableAll = false;
                    break;
                }
            }

            return isEnableAll;
        }

        bool Record::IsEnable(int dIdx) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));

            return _DataArray[dIdx]->IsEnable();
        }

        void Record::DisbleAll() {

            for (int dIdx = 0; dIdx < _ColumnCount; dIdx++) {

                _DataArray[dIdx]->Disable();
            }
        }

        void Record::Enable(int dIdx) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));

            _DataArray[dIdx]->Enable();
        }

        void Record::Disble(int dIdx) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));

            _DataArray[dIdx]->Disable();
        }


        std::string Record::GetColumnName(int dIdx) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));

            return _DataArray[dIdx]->GetColumnName();
        }

        std::string Record::GetTableDotColumnName(int dIdx) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));

            return _DataArray[dIdx]->GetTableDotColumnName();
        }

        Comm::VarType::SQL Record::GetDataType(int dIdx) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));

            return _DataArray[dIdx]->GetVarType();
        }

        bool Record::SetValueBigInt(int dIdx, long long value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->SetValueBigInt(value);
        }

        bool Record::SetValueBigUint(int dIdx, unsigned long long value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->SetValueBigUint(value);
        }


        bool Record::SetValue(int dIdx, unsigned short value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->SetValue(value);
        }

        bool Record::SetValue(int dIdx, unsigned int value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->SetValue(value);
        }

        bool Record::SetValue(int dIdx, int value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->SetValue(value);
        }

        bool Record::SetValueIntKstDate(int dIdx, time_t timeValue) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->SetValueIntKstDate(timeValue);
        }

        bool Record::AddValueInt(int dIdx, int value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->AddValueInt(value);
        }

        bool Record::SetValue(int dIdx, unsigned char value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->SetValue(value);
        }

        bool Record::SetValue(int dIdx, float value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->SetValue(value);
        }

        bool Record::SetValueTime(int dIdx, time_t value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->SetValueTime(value);
        }

        bool Record::SetValue(int dIdx, std::string value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->SetValue(value);
        }

        bool Record::GetValueBigUint(int dIdx, unsigned long long* value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->GetValueBigUint(value);
        }


        bool Record::GetValue(int dIdx, int* value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->GetValue(value);
        }

        bool Record::GetValue(int dIdx, unsigned int* value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->GetValue(value);
        }

        bool Record::GetValue(int dIdx, unsigned short* value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->GetValue(value);
        }

        bool Record::GetValue(int dIdx, unsigned char* value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->GetValue(value);
        }

        bool Record::GetValueTime(int dIdx, time_t* value) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->GetValueTime(value);
        }

        short Record::GetValueSmallInt(int dIdx) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->GetValueSmallInt();
        }
        unsigned short Record::GetValueSmallUint(int dIdx) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->GetValueSmallUint();
        }

        int Record::GetValueInt(int dIdx) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->GetValueInt();
        }
        unsigned int Record::GetValueUint(int dIdx) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->GetValueUint();
        }

        long long Record::GetValueBigInt(int dIdx) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->GetValueBigInt();
        }

        unsigned long long  Record::GetValueBigUint(int dIdx) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->GetValueBigUint();
        }

        float Record::GetValueFloat(int dIdx) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->GetValueFloat();
        }

        time_t Record::GetValueTime(int dIdx) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->GetValueTime();
        }

        std::string Record::GetValueString(int dIdx) {
        
            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->GetValueString();
        }
    

        std::string Record::ToString(int dIdx) {

            assert((dIdx >= 0) && (dIdx < _ColumnCount));
            return _DataArray[dIdx]->ToString();
        }


        std::vector<std::string> Record::ToStringVector() {
        
            std::vector<std::string> strVec;

            for (int dIdx = 0; dIdx < _ColumnCount; dIdx++) {
            
                strVec.push_back(_DataArray[dIdx]->ToString());
            }

            return strVec;
        }
        

        std::vector<std::string> Record::GetEnabledColumnNameStringVector() {
        
            std::vector<std::string> strVec;

            for (int dIdx = 0; dIdx < _ColumnCount; dIdx++) {

                std::shared_ptr<Data> d = _DataArray[dIdx];
                if (d) {

                    if (d->IsEnable()) {
                        strVec.push_back(d->GetColumnName());
                    }
                }
            }

            return strVec;
        }

        std::string Record::GetEnabledColumnNameSqlArgString() {

            std::string str;
            int cnt = 0;

            if (this->IsEnableAll()) {
            
                str = "*";
            }
            else {

                for (int dIdx = 0; dIdx < _ColumnCount; dIdx++) {

                    std::shared_ptr<Data> d = _DataArray[dIdx];
                    if (d) {

                        if (d->IsEnable()) {

                            if (cnt != 0) {
                                str += ',';
                            }

                            
                            str += d->GetTableDotColumnName();
                            
                            cnt++;
                        }
                    }
                }
            }

            return str;
        }

        // Col1=1 and col2=2 and ...
        std::string Record::GetEnabledColumnValueSqlWhereString() {
            
            std::string str;
            int cnt = 0;

            for (int dIdx = 0; dIdx < _ColumnCount; dIdx++) {

                std::shared_ptr<Data> d = _DataArray[dIdx];
                if (d) {

                    if (d->IsEnable()) {

                        if (cnt != 0) {
                            str += " and ";
                        }

                        str += Comm::Utils::StringFormat("%s.%s='%s'", d->GetTableName().c_str(), d->GetColumnName().c_str(), d->ToString().c_str());
                        cnt++;
                    }
                }
            }

            return str;
        }

        // Col1=1 ,col2=2, ...
        std::string Record::GetEnabledColumnValueSqlUpdateString() {

            std::string str;
            int cnt = 0;

            for (int dIdx = 0; dIdx < _ColumnCount; dIdx++) {

                std::shared_ptr<Data> d = _DataArray[dIdx];
                if (d) {

                    if (d->IsEnable()) {

                        if (cnt != 0) {
                            str += ", ";
                        }

                        str += Comm::Utils::StringFormat("%s='%s'", d->GetColumnName().c_str(), d->ToString().c_str());
                        cnt++;
                    }
                }
            }

            return str;
        }

        std::vector<int> Record::GetEnabledColumnIdxVector() {

            std::vector<int> intVec;

            for (int dIdx = 0; dIdx < _ColumnCount; dIdx++) {

                std::shared_ptr<Data> d = _DataArray[dIdx];
                if (d) {

                    if (d->IsEnable()) {
                        intVec.push_back(dIdx);
                    }
                }
            }

            return intVec;
        }

        std::vector<std::shared_ptr<Database::Single::Data>> Record::GetEnabledColumnDataVector() {
        
            std::vector<std::shared_ptr<Database::Single::Data>> vec;

            for (int dIdx = 0; dIdx < _ColumnCount; dIdx++) {

                std::shared_ptr<Data> d = _DataArray[dIdx];
                if (d) {
                    if (d->IsEnable()) {
                        vec.push_back(d);
                    }
                }
            }

            return vec;
        }

        bool Record::IsEqualData(std::shared_ptr<Record> record) {
        
            bool isEqual = true;

            for (int dIdx = 0; dIdx < _ColumnCount; dIdx++) {

                std::shared_ptr<Data> d = _DataArray[dIdx];
                if (d) {
                    if (d->IsEnable()) {
                        if (!d->IsEqualData(record->_DataArray[dIdx])) {
                            isEqual = false;
                            break;
                        }
                    }
                }
            }

            return isEqual;
        }

        int Record::GetDataIndex(std::string tableDotColumnName) {
        
            int idx = -1;

            for (int dIdx = 0; dIdx < _ColumnCount; dIdx++) {

                std::shared_ptr<Data> d = _DataArray[dIdx];
                if (d) {
                    if (d->IsThisTableDotColumnName(tableDotColumnName)) {
                        idx = dIdx;
                        break;
                    }
                }
            }

            return idx;
        }

    }; //namespace SQL 
}; //namespace Database

