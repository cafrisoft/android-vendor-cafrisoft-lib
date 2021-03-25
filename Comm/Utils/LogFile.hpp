#ifndef COMM_UTILS_LOGFILE_HPP__
#define COMM_UTILS_LOGFILE_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/OAL/CriticalSection.hpp>
#include <Comm/OAL/Lock.hpp>

namespace Comm {
    namespace Utils {

        class LogFile : public Comm::Base::Object {

        private:
            std::shared_ptr<Comm::OAL::CriticalSection> _Cs;
            std::string _LogPathFileName;
            FILE* _Fp;
            std::string _CurLine;
            std::vector<std::string> _LineVec;

            const int _LineFmtBufByteSize = 1024 * 32;
            char* _LineFmtBuffer;

        public:
            LogFile(std::string logPathFileName);
            virtual ~LogFile();

        private:
            void AddStringToCurLine_Internal(std::string logTxt);

        public:
            std::string GetLogPathFileName();

            void AddStringToCurLine(std::string logTxt);
            void AddFmtTxtToCurLine(const char* lpszFormat, ...);
            void FlushCurLine();  //CurLine�� ������ LineVec�� �̵��Ѵ�.
                 
            void AddString(std::string logTxt);
            void AddFmtTxt(const char* lpszFormat, ...);
            void Flush();  //lineVector�� ������ ���� ���Ͽ� ����, LineVec, CurLine��� �����.
            

        }; //class LogFile

    }; //namespace Utils
}; //namespace Comm

#endif

