#ifndef DATABASE_SINGLE_RECORD_HPP__
#define DATABASE_SINGLE_RECORD_HPP__

#include <Database/Single/Data.hpp>
#include <Database/Single/Header.hpp>

namespace Database {
    namespace Single {

        class Table;

        class Record : public Comm::Base::Object {

        private:
            int _ColumnCount;
            std::shared_ptr<Data>* _DataArray;

        public:
            Record(Table* pTable);
            Record(std::string tableName, const struct Column::Property columnPropVec[], int propCnt);
            Record(std::shared_ptr<Record> obj);
            virtual ~Record();
        
        public:
            int GetColumnCount();

            void EnableOnlyAllPK();  //Primary Key 만 Enable한다. 
            void EnableOnlyAK();  //Artificial Key 만 Enable한다. 
            int GetAKIdx();  //Aritifical Key Index return
            void EnableAll();
            bool IsEnableAll();
            bool IsEnable(int dIdx);

            void DisbleAll();

            void Enable(int dIdx);
            void Disble(int dIdx);
            
            std::string GetColumnName(int dIdx);
            std::string GetTableDotColumnName(int dIdx);
            Comm::VarType::SQL GetDataType(int dIdx);
            
            bool SetValue(int dIdx, int value);
            bool SetValueIntKstDate(int dIdx, time_t timeValue);
            bool SetValue(int dIdx, unsigned int value);
            bool SetValue(int dIdx, unsigned short value);
            bool SetValueBigInt(int dIdx, long long value);
            bool SetValueBigUint(int dIdx, unsigned long long value);
            bool SetValue(int dIdx, unsigned char value);
            bool SetValue(int dIdx, float value);
            bool SetValueTime(int dIdx, time_t value);
            bool SetValue(int dIdx, std::string value);
            
            bool AddValueInt(int dIdx, int value);

            bool GetValueBigUint(int dIdx, unsigned long long* value);
            bool GetValue(int dIdx, unsigned int* value);
            bool GetValue(int dIdx, int* value);
            bool GetValue(int dIdx, unsigned short* value);
            bool GetValue(int dIdx, unsigned char* value);
            bool GetValueTime(int dIdx, time_t* value);
            
            short GetValueSmallInt(int dIdx);
            unsigned short GetValueSmallUint(int dIdx);
            int GetValueInt(int dIdx);
            unsigned int GetValueUint(int dIdx);
            long long  GetValueBigInt(int dIdx);
            unsigned long long GetValueBigUint(int dIdx);
            float GetValueFloat(int dIdx);
            std::string GetValueString(int dIdx);
            time_t GetValueTime(int dIdx);
            

            std::string ToString(int dIdx);

            std::vector<std::string> ToStringVector();
            std::vector<std::string> GetEnabledColumnNameStringVector();
            
            std::string GetEnabledColumnNameSqlArgString();  // Col1,Col2,Col3...
            std::string GetEnabledColumnValueSqlWhereString(); // Col1=1 and col2=2 and ...
            std::string GetEnabledColumnValueSqlUpdateString(); // Col1=1 ,col2=2, ...
            
            std::vector<int> GetEnabledColumnIdxVector();
            std::vector<std::shared_ptr<Database::Single::Data>> GetEnabledColumnDataVector();

            bool IsEqualData(std::shared_ptr<Record> record);
            int GetDataIndex(std::string tableDotColumnName);
        };

    }; //namespace Table
}; //namespace Database


#endif

