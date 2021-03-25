#ifndef DATABASE_SINGLE_DATA_HPP__
#define DATABASE_SINGLE_DATA_HPP__

#include <Comm/Base/Object.hpp>
#include <Database/Single/Column.hpp>

namespace Database {
    namespace Single {

        class Data : public Comm::Base::Object {

        private:
            bool _IsEnable;
            std::shared_ptr<Column> _Column;
            unsigned char* _Value;
            
        public:
            Data(std::shared_ptr<Column> column);
            Data(std::shared_ptr<Data> obj);
            virtual ~Data();

        public:
            bool IsPrimaryKey();
            bool IsArtificialKey();
            bool IsEnable();
            void Enable();
            void Disable();

            std::string GetTableName();
            std::string GetColumnName();
            std::string GetTableDotColumnName();
            Comm::VarType::SQL GetVarType();
            
            bool SetValueBigUint(unsigned long long value);
            bool SetValueBigInt(long long value);
            bool SetValue(unsigned int value);
            bool SetValue(int value);
            bool SetValueIntKstDate(time_t timeValue);
            bool SetValue(unsigned short value);
            bool SetValue(unsigned char value);
            bool SetValue(float value);
            bool SetValueTime(time_t value);
            bool SetValue(std::string value);

            bool AddValueInt(int value);
            
            bool GetValue(unsigned char* value);
            bool GetValue(short* value);
            bool GetValue(unsigned short* value);
            bool GetValue(int* value);
            bool GetValue(unsigned int* value);
            bool GetValueBigInt(long long* value);
            bool GetValueBigUint(unsigned long long* value);
            
            bool GetValue(float* value);
            bool GetValueTime(time_t* value);
            

            short GetValueSmallInt();
            unsigned short GetValueSmallUint();
            int GetValueInt();
            unsigned int GetValueUint();
            long long GetValueBigInt();
            unsigned long long GetValueBigUint();
            
            float GetValueFloat();
            time_t GetValueTime();
            std::string GetValueString();
            
            std::string ToString();

            bool IsEqualData(std::shared_ptr<Data> d);
            bool IsThisTableDotColumnName(std::string tableDotColumnName);
        };

    }; //namespace Table
}; //namespace Database


#endif

