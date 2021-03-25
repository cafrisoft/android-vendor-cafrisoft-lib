#ifndef MMPSTRINGPARSER_HPP__
#define MMPSTRINGPARSER_HPP__

#include <Comm/Base/Object.hpp>

namespace Comm {
    namespace Utils {

        template<typename ... Args>
        std::string StringFormat(const std::string& format, Args ... args)
        {
            size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
            //if (size <= 0) { 
                //throw std::runtime_error("Error during formatting."); 
            //}
            assert(size > 0);
            std::unique_ptr<char[]> buf(new char[size]);
            snprintf(buf.get(), size, format.c_str(), args ...);
            return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
        }


        class StringTool {

        public:
            static bool MakeUpper(char* wszName);
            static bool MakeLower(char* wszName);

            static bool RemoveCharInString(const char* strOrg,
                /*OUT*/ char* strNew, int newStrMaxLen,
                const char* rmCharArr, int rmCharCnt); // 주어진 문자열에서 , Char배열에 등록된 문자를 모두 제거해서 새 문자열로 리턴한다. 

            static bool RemoveCharInString(char* str,
                const char* rmCharArr, int rmCharCnt); // 주어진 문자열에서 , Char배열에 등록된 문자를 모두 제거해서 새 문자열로 리턴한다. 
            static bool RemoveCharInString(char* str, char rmChar);
            static std::string RemoveCharInString(const char* sz, const char* rmCharArr = " \n\r\t\\"); //문장에서 rmCharArr에 포함된 문자열은 모두 제거해서  std::string으로 리턴 

            static bool RemoveCharInStringFromBack(char* str, const char* rmCharArr=" \n\r\t\\"); //문장 뒤쪽의 주어진 문자를 제거한다.
            static bool RemoveCharInStringFromBack(char* str, char rmChar);
            
            static bool RemoveCharForParsingInString(const char* strOrg, /*OUT*/ char* strNew, int newStrMaxLen); // 주어진 문자열에서 , 문자열 파싱을 위해 불필요한  문자를 모두 제거해서 새 문자열로 리턴한다. 
            static bool RemoveCharForParsingInString(char* str); // 주어진 문자열에서 , 문자열 파싱을 위해 불필요한  문자를 모두 제거해서 새 문자열로 리턴한다. 

#if 0
            static bool RemoveBackCharInString(const char* strOrg,
                /*OUT*/ char* strNew, int newStrMaxLen,
                const char* rmCharArr, int rmCharCnt); // 주어진 문자열 뒷부분에서 , Char배열에 등록된 문자를 모두 제거해서 새 문자열로 리턴한다. 
            static bool RemoveBackCharForParsingInString(const char* strOrg, /*OUT*/ char* strNew, int newStrMaxLen); // 주어진 문자열에서 , 문자열 파싱을 위해 불필요한  문자를 모두 제거해서 새 문자열로 리턴한다. 
#endif
            
          
            // "0x01, 0xAb, ..." 16진수만 숫자배열로 변환함  
            static bool ConvertHexStringToHexArray(const char* strHexString, char delim, unsigned char* hexArrary, int reqArrCnt, int* retArrCnt);

            // "3, 0xAb, ..." 등  10진수/16진수 혼용된 문자열을 숫자 배열로 변환함
            static bool ConvertNumberStringToIntArray(const char* strNumberString, char delim, int* numberArrary, int maxNumberArrCnt, int* retArrCnt);
                                    
            static bool ConvertHexArrayToHexString(const unsigned char* hexArrary, int arrCount, /*OUT*/char* strHexString, char delim);
            
            static bool ConvertIntStringToIntArray(const char* strIntString, char delim, int* intArrary, int reqArrCnt, int* retArrCnt);

            static int ConvertNumberStringToInt(const char* strNumberString);
            static bool ConvertIntArrayToDecimalString(int* valueArr, int arrCount, char delim, /*OUT*/ char *szIntArr);
            static bool ConvertIntArrayToHexString(int* valueArr, int arrCount, char delim, int hexDispFmtCnt, /*OUT*/ char* szIntArr);

            // A->1  B->2 ...     AA->(26+1),     0보다 같거나 작으면 에러 
            static int ConvertExcelColumnToNumber(const char* str);

            /*

            */
            static bool TEDGetChipIDInDummyString(const char* str, /*OUT*/ unsigned char* chipid); // 혼재된 문자열 속에서  TED Chip ID 5자리 분리 

            static bool ReplaceCharInString(char* str, char old, char new_);

            static bool IsDecimalNumber(const char* str);
            static bool IsHexNumber(const char* str);
          
            /*
                ToString
            */
            static std::string ToStringHex(std::vector<unsigned char> vec, char delim=',');


            /*
              Ansi => Utf8
            */
            static std::string AnsiToUtf8(std::string strIn);
            static std::string Utf8ToAnsi(std::string strIn);
            static std::string  SplitFileName(std::string strPathFileName); // 입력된 전체 파일명에서 파일이름만 뽑아낸다. ex) "c:\mylib\aa.dat" => "aa"
        };

    };  //namespace Utils
};  // namespace Comm

#endif

