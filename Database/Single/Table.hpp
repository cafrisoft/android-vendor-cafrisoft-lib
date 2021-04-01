#ifndef DATABASE_SINGLE_TABLE_HPP__
#define DATABASE_SINGLE_TABLE_HPP__

#include <Database/Single/Header.hpp>
#include <Database/Single/Record.hpp>
#include <Comm/OAL/Lock.hpp>
#include <Comm/OAL/CriticalSection.hpp>

namespace Database {
    namespace Single {

        class Table : public Comm::Base::Object {

        protected:
            static const int _AkColumnIndex = 0;

        protected:
            std::shared_ptr<Comm::OAL::CriticalSection> _Cs;
            std::shared_ptr<Header> _Header;
            std::string _TableName;
            int _TableID;
                    
        public:
            Table(std::shared_ptr<Header> header);

        public:
            std::string  GetTableName();
            std::shared_ptr<Header> GetHeader();
            std::string GetTableDotColumnName(int colIdx);  // [TableName].[ColumnName]
            int GetColumnCount();
            std::string GetColumnName(int colIdx);          // [ColumnName]
            Comm::VarType::SQL GetColumnSqlVarType(int colIdx);
            long long  GetColumnMaxByteSize(int colIdx);

        protected:
            //bool QueryInsert();
            int QuerySelectInt(int getColID, int whereColID, int whereColValue, int defaultValue =-1 );
            //bool QuerySelect(int getColID, int whereColID);
            
        private:
            virtual bool IsThisPKInternal(std::shared_ptr<Record> whereKeyRecord, bool isDebug=false);
            virtual bool InsertInternal(std::shared_ptr<Record> record, bool isDebug=false);
            virtual bool SelectWithPKInternal(std::shared_ptr<Record> record, std::shared_ptr<Record> whereRecord);
            virtual bool SelectInternal(std::shared_ptr<Record> record, unsigned int ak);
            virtual bool SelectInternal(std::shared_ptr<Record> record, long long ak);
            virtual bool SelectInternal(std::shared_ptr<Record> record, std::shared_ptr<Record> whereRecord, bool isDebug=false);
            virtual std::vector<std::shared_ptr<Record>> SelectRecordVecInternal(std::shared_ptr<Record> record, std::shared_ptr<Record> whereRecord);
            virtual bool UpdateInternal(std::shared_ptr<Record> record, unsigned int ak);
            virtual bool UpdateInternal(std::shared_ptr<Record> record, long long ak);
            virtual bool UpdateInternal(std::shared_ptr<Record> record, std::shared_ptr<Record> whereRecord);

        protected:
            virtual bool IsThisPK(std::shared_ptr<Record> whereKeyRecord); //입력된 whereRecord의 PK값이 같은 Record가 Table안에 존재하는가?
            virtual bool InsertRecord(std::shared_ptr<Record> record, bool isDebug=false);
            
            virtual bool SelectWithPK(std::shared_ptr<Record> record, std::shared_ptr<Record> whereRecord);
            virtual bool SelectRecord(std::shared_ptr<Record> record, unsigned int ak);
            virtual bool SelectRecord(std::shared_ptr<Record> record, long long ak);
            virtual bool SelectRecord(std::shared_ptr<Record> record, std::shared_ptr<Record> whereRecord, bool isDebug = false);

            virtual std::vector<std::shared_ptr<Record>> SelectRecordVec(std::shared_ptr<Record> record, std::shared_ptr<Record> whereRecord);
            virtual bool Update(std::shared_ptr<Record> record, unsigned int ak);
            virtual bool Update(std::shared_ptr<Record> record, long long ak);
            virtual bool UpdateRecord(std::shared_ptr<Record> record, std::shared_ptr<Record> whereRecord);
            virtual long long GetAK_BigInt_ByPK(std::shared_ptr<Record> record, bool isDebug=false);
            virtual int GetAK_Int_ByPK(std::shared_ptr<Record> record, bool isDebug = false);
            
        protected:
            virtual std::shared_ptr<Record> GetRecord();
            virtual std::shared_ptr<Record> GetRecord(int enableColumnIdx);
            virtual std::shared_ptr<Record> GetRecord_EnabledAK();
          
        public :
            virtual void PrintColumnNameForPython();
            virtual void PrintPythonColumnID();
        };

    }; //namespace Table
}; //namespace Database


#endif

