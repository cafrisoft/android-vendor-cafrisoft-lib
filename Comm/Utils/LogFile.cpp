
#include <Comm/Utils/LogFile.hpp>

namespace Comm {
    namespace Utils {

        LogFile::LogFile(std::string logPathFileName)
        {
            _LineFmtBuffer = new char[_LineFmtBufByteSize];
            assert(_LineFmtBuffer);

            _Cs = Comm::OAL::CriticalSection::CreateObject();
            assert(_Cs);

            _Fp = fopen(logPathFileName.c_str(), "w");
            assert(_Fp);

            _LogPathFileName = logPathFileName;
        }
            
        LogFile::~LogFile() {
        
            this->Flush();

            if (_Fp) {
                fclose(_Fp);
            }

            if (_LineFmtBuffer) {
                delete[] _LineFmtBuffer;
            }
        }

        std::string LogFile::GetLogPathFileName() {
            return _LogPathFileName;
        }

        void LogFile::AddStringToCurLine_Internal(std::string logTxt) {

            if (_CurLine.size() > 0) {
                _CurLine += ' ';
            }
            _CurLine += logTxt;
        }


        void LogFile::AddStringToCurLine(std::string logTxt) {

            Comm::OAL::Lock lock(_Cs);
            this->AddStringToCurLine_Internal(logTxt);
        }

        void LogFile::AddFmtTxtToCurLine(const char* lpszFormat, ...) {

            Comm::OAL::Lock lock(_Cs);

            va_list args;

            va_start(args, lpszFormat);
            vsprintf(_LineFmtBuffer, lpszFormat, args);
            this->AddStringToCurLine_Internal(_LineFmtBuffer);
            va_end(args);
        }

        void LogFile::FlushCurLine()  //CurLine의 내용을 LineVec로 이동한다.
        {
            Comm::OAL::Lock lock(_Cs);

            if (_CurLine.size() > 0) {
                _LineVec.push_back(_CurLine);
                _CurLine = "";
            }

        }


        void LogFile::AddString(std::string logTxt) {

            Comm::OAL::Lock lock(_Cs);
            
            _LineVec.push_back(logTxt);
        }

        void LogFile::AddFmtTxt(const char* lpszFormat, ...) {

            Comm::OAL::Lock lock(_Cs);

            va_list args;

            va_start(args, lpszFormat);
            vsnprintf(_LineFmtBuffer, _LineFmtBufByteSize, lpszFormat, args);
            va_end(args);

            std::string strLine(_LineFmtBuffer);
            _LineVec.push_back(strLine);
        }

        void LogFile::Flush() {

            Comm::OAL::Lock lock(_Cs);

            if (_CurLine.size() > 0) {
                _LineVec.push_back(_CurLine);
                _CurLine = "";
            }
        
            for (std::vector<std::string>::const_iterator it = _LineVec.cbegin();
                it != _LineVec.cend();
                it++) {
                //printf("%s\n", (*it).c_str());
                fprintf(_Fp, "%s\n", (*it).c_str());
                fflush(_Fp);
            }

            _LineVec.clear();
            
        }

    }; //namespace Utils
}; //namespace Comm



