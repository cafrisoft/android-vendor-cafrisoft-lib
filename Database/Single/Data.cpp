#include <Database/Global/BuildOptions.h>
#include <Database/Single/Data.hpp>
#include <Comm/Utils/StringTool.hpp>
#include <Comm/OAL/DateTime.hpp>


namespace Database {
    namespace Single {

        
        Data::Data(std::shared_ptr<Column> column) :
            _IsEnable(false)
            ,_Column(column)
        {

            _Value = new unsigned char[_Column->GetMaxDataByteSize()];
            assert(_Value);
            memset(_Value, 0x00, _Column->GetMaxDataByteSize());

            if (_Column->IsAutoIncrement()) {

                switch (_Column->GetSqlVarType()) {

                    case Comm::VarType::SQL::Int:
                    {
                        int value = 0;
                        this->SetValue(value);
                        break;
                    }

                    case Comm::VarType::SQL::Uint:
                    {
                        unsigned int value = 0;
                        this->SetValue(value);
                        break;
                    }

                    default:
                        assert(0);
                        break;
                }
            }
        }

        Data::Data(std::shared_ptr<Data> obj) 
        {
            _IsEnable = obj->_IsEnable;
            _Column = std::make_shared<Column>(obj->_Column);
            assert(_Column);

            _Value = new unsigned char[_Column->GetMaxDataByteSize()];
            assert(_Value);
            memcpy(_Value, obj->_Value, _Column->GetMaxDataByteSize());
        }

        Data::~Data() {
            
            if (_Value) {
                delete[] _Value;
            }

        }

        bool Data::IsPrimaryKey() {
        
            return _Column->IsPrimaryKey();
        }

        bool Data::IsArtificialKey() {

            return _Column->IsArtificialKey();
        }

        bool Data::IsEnable() {

            return _IsEnable;
        }

        void Data::Enable() {
        
            _IsEnable = true;
        }

        void Data::Disable() {
            
            _IsEnable = false;
        }

        std::string Data::GetTableName() {
            return _Column->GetTableName();
        }

        std::string Data::GetColumnName() {
            return _Column->GetColumnName();
        }

        std::string Data::GetTableDotColumnName() {
            return _Column->GetTableDotColumnName();
        }

        Comm::VarType::SQL Data::GetVarType() {
        
            return _Column->GetSqlVarType();
        }
        
        bool Data::SetValueBigInt(long long value) {
            assert(_Column->GetSqlVarType() == Comm::VarType::SQL::BigInt);
            memcpy(_Value, &value, sizeof(unsigned long long));
            _IsEnable = true;
            return true;
        }

        bool Data::SetValueBigUint(unsigned long long value) {
            assert(_Column->GetSqlVarType() == Comm::VarType::SQL::BigUint);
            memcpy(_Value, &value, sizeof(unsigned long long));
            _IsEnable = true;
            return true;
        }

        bool Data::SetValue(unsigned int value) {
            assert(_Column->GetSqlVarType() == Comm::VarType::SQL::Uint);
            memcpy(_Value, &value, sizeof(unsigned int));
            _IsEnable = true;
            return true;
        }

        bool Data::SetValue(int value) {
            assert(_Column->GetSqlVarType() == Comm::VarType::SQL::Int);
            memcpy(_Value, &value, sizeof(int));
            _IsEnable = true;
            return true;
        }

        bool Data::SetValueIntKstDate(time_t timeValue) {
            int value = Comm::OAL::DateTime::GetKstYYYYMMDD(timeValue);
            return this->SetValue(value);
        }

        bool Data::AddValueInt(int value) {
            int curValue = this->GetValueInt();
            curValue += value;
            return this->SetValue(curValue);
        }

        bool Data::SetValue(unsigned short value) {
            assert(_Column->GetSqlVarType() == Comm::VarType::SQL::SmallUint);
            memcpy(_Value, &value, sizeof(unsigned short));
            _IsEnable = true;
            return true;
        }

        bool Data::SetValue(unsigned char value) {

            if (_Column->GetSqlVarType() == Comm::VarType::SQL::Int) {

                int v = (int)value & 0xFF;
                memcpy(_Value, &v, sizeof(int));
            }
            else {
                assert(0);
            }

            _IsEnable = true;

            return true;
        }

        bool Data::SetValue(float value) {
            assert(_Column->GetSqlVarType() == Comm::VarType::SQL::Float);
            memcpy(_Value, &value, sizeof(float));
            _IsEnable = true;
            return true;
        }

        bool Data::SetValueTime(time_t value) {

            assert( ( _Column->GetSqlVarType() == Comm::VarType::SQL::DateTime)
                 || (_Column->GetSqlVarType() == Comm::VarType::SQL::Date)
            );
            memcpy(_Value, &value, sizeof(value));
            _IsEnable = true;
            return true;
        }

        bool Data::SetValue(std::string value) {

            assert(_Column->GetSqlVarType() == Comm::VarType::SQL::VarChar);
            assert( value.size() < (size_t)(_Column->GetMaxDataByteSize() - 1));

            strcpy((char*)_Value, value.c_str());
            _IsEnable = true;
            return true;
        }
                
        bool Data::GetValue(short* value) {
            assert(_IsEnable);
            assert(_Column->GetSqlVarType() == Comm::VarType::SQL::SmallInt);
            memcpy(value, _Value, sizeof(short));
            return true;
        }

        bool Data::GetValue(unsigned short* value) {
            assert(_IsEnable);
            assert(_Column->GetSqlVarType() == Comm::VarType::SQL::SmallUint);
            memcpy(value, _Value, sizeof(unsigned short));
            return true;
        }

        bool Data::GetValue(int* value) {
            assert(_IsEnable);
            assert(_Column->GetSqlVarType() == Comm::VarType::SQL::Int);
            memcpy(value, _Value, sizeof(int));
            return true;
        }

        bool Data::GetValue(unsigned int* value) {
            assert(_IsEnable);
            assert(_Column->GetSqlVarType() == Comm::VarType::SQL::Uint);
            memcpy(value, _Value, sizeof(unsigned int));
            return true;
        }

        bool Data::GetValueBigInt(long long* value) {
            assert(_IsEnable);
            assert(_Column->GetSqlVarType() == Comm::VarType::SQL::BigInt);
            memcpy(value, _Value, sizeof(long long));
            return true;
        }

        bool Data::GetValueBigUint(unsigned long long* value) {
            assert(_IsEnable);
            assert(_Column->GetSqlVarType() == Comm::VarType::SQL::BigUint);
            memcpy(value, _Value, sizeof(unsigned long long));
            return true;
        }

        bool Data::GetValue(float* value) {
            assert(_IsEnable);
            assert(_Column->GetSqlVarType() == Comm::VarType::SQL::Float);
            memcpy(value, _Value, sizeof(float));
            return true;
        }

        bool Data::GetValueTime(time_t* value) {

            assert(_IsEnable);
            
            assert((_Column->GetSqlVarType() == Comm::VarType::SQL::DateTime)
                || (_Column->GetSqlVarType() == Comm::VarType::SQL::Date)
            );
         
            memcpy(value, _Value, sizeof(*value));
            return true;
        }

        bool Data::GetValue(unsigned char* value) {

            assert(_IsEnable);

            if (_Column->GetSqlVarType() == Comm::VarType::SQL::Int) {
            
                int v;
                memcpy(&v, _Value, sizeof(v));
                *value = (unsigned char)v;
            }
            else {
                assert(0);
            }
            memcpy(value, _Value, sizeof(*value));
            return true;
        }
        
        short Data::GetValueSmallInt() {
            short value;
            this->GetValue(&value);
            return value;
        }

        unsigned short Data::GetValueSmallUint() {
            unsigned short value;
            this->GetValue(&value);
            return value;
        }


        int Data::GetValueInt() {
            int value;
            this->GetValue(&value);
            return value;
        }

        unsigned int Data::GetValueUint() {
            unsigned int value;
            this->GetValue(&value);
            return value;
        }

        long long Data::GetValueBigInt() {
            long long value;
            this->GetValueBigInt(&value);
            return value;
        }

        unsigned long long Data::GetValueBigUint() {
            unsigned long long value;
            this->GetValueBigUint(&value);
            return value;
        }

        
        float Data::GetValueFloat() {
            float value;
            this->GetValue(&value);
            return value;
        }
        
        time_t Data::GetValueTime() {
            time_t value;
            this->GetValueTime(&value);
            return value;
        }

        std::string Data::GetValueString() {

            std::string str;
            assert(_IsEnable);
            assert(_Column->GetSqlVarType() == Comm::VarType::SQL::VarChar);
            str = (char*)_Value;
            
            return str;
        }

        std::string Data::ToString() {
        
            std::string str;

            switch (_Column->GetSqlVarType()) {
                            
                case Comm::VarType::SQL::SmallInt:
                {
                    short v;
                    this->GetValue(&v);
                    str = Comm::Utils::StringFormat("%d", (int)v & 0xFFFF);
                    break;
                }

                case Comm::VarType::SQL::SmallUint:
                {
                    unsigned short v;
                    this->GetValue(&v);
                    str = Comm::Utils::StringFormat("%d", (int)v & 0xFFFF);
                    break;
                }

                case Comm::VarType::SQL::Int:
                {
                    int v;
                    this->GetValue(&v);
                    str = Comm::Utils::StringFormat("%d", v);
                    break;
                }

                case Comm::VarType::SQL::Uint:
                {
                    unsigned int v;
                    this->GetValue(&v);
                    str = Comm::Utils::StringFormat("%d", v);
                    break;
                }


                case Comm::VarType::SQL::BigInt:
                {
                    long long v;
                    this->GetValueBigInt(&v);
                    str = Comm::Utils::StringFormat("%lld", v);
                    break;
                }

                case Comm::VarType::SQL::BigUint:
                {
                    unsigned long long v;
                    this->GetValueBigUint(&v);
                    str = Comm::Utils::StringFormat("%llu", v);
                    break;
                }


                case Comm::VarType::SQL::Float:
                {
                    float v;
                    this->GetValue(&v);
                    str = Comm::Utils::StringFormat("%f", v);
                    break;
                }

                case Comm::VarType::SQL::DateTime:
                {
                    time_t t;
                    memcpy(&t, _Value, sizeof(t));
                    str = Comm::OAL::DateTime::GetKstDateTimeString(t);
                    break;
                }

                case Comm::VarType::SQL::Date:
                {
                    time_t t;
                    memcpy(&t, _Value, sizeof(t));
                    str = Comm::OAL::DateTime::GetKstDateString(t);
                    break;
                }

                case Comm::VarType::SQL::VarChar:
                {
                    str = (char*)_Value;
                    break;
                }

                default:
                    assert(0);
            
            }

            return str;
        }

        bool Data::IsEqualData(std::shared_ptr<Data> d1) {
        
            bool isEqu = false;

            if (_Column->GetSqlVarType() == d1->_Column->GetSqlVarType()) {
            
                switch (_Column->GetSqlVarType()) {

                case Comm::VarType::SQL::Uint:
                {
                    unsigned int v0, v1;
                    this->GetValue(&v0);
                    d1->GetValue(&v1);

                    if (v0 == v1) {
                        isEqu = true;
                    }
                    break;
                }

                case Comm::VarType::SQL::Int:
                {
                    int v0, v1;
                    this->GetValue(&v0);
                    d1->GetValue(&v1);
                    
                    if (v0 == v1) {
                        isEqu = true;
                    }
                    break;
                }

                case Comm::VarType::SQL::BigInt:
                {
                    long long v0, v1;
                    this->GetValueBigInt(&v0);
                    d1->GetValueBigInt(&v1);

                    if (v0 == v1) {
                        isEqu = true;
                    }
                    break;
                }

                case Comm::VarType::SQL::DateTime:
                {
                    time_t t0, t1;
                    this->GetValueTime(&t0);
                    d1->GetValueTime(&t1);
                    if (t0 == t1) {
                        isEqu = true;
                    }
                    break;
                }

                case Comm::VarType::SQL::VarChar:
                {
                    std::string str0, str1;
                    str0 = this->GetValueString();
                    str1 = d1->GetValueString();
                    if (str0 == str1) {
                        isEqu = true;
                    }
                    break;
                }

                default:
                    assert(0);

                }
            }

            return isEqu;
        }

        bool Data::IsThisTableDotColumnName(std::string tableDotColumnName) {
        
            return _Column->IsThisTableDotColumnName(tableDotColumnName);
        }

    }; //namespace SQL 
}; //namespace Database

