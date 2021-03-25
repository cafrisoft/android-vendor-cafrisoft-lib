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
                const char* rmCharArr, int rmCharCnt); // �־��� ���ڿ����� , Char�迭�� ��ϵ� ���ڸ� ��� �����ؼ� �� ���ڿ��� �����Ѵ�. 

            static bool RemoveCharInString(char* str,
                const char* rmCharArr, int rmCharCnt); // �־��� ���ڿ����� , Char�迭�� ��ϵ� ���ڸ� ��� �����ؼ� �� ���ڿ��� �����Ѵ�. 
            static bool RemoveCharInString(char* str, char rmChar);
            static std::string RemoveCharInString(const char* sz, const char* rmCharArr = " \n\r\t\\"); //���忡�� rmCharArr�� ���Ե� ���ڿ��� ��� �����ؼ�  std::string���� ���� 

            static bool RemoveCharInStringFromBack(char* str, const char* rmCharArr=" \n\r\t\\"); //���� ������ �־��� ���ڸ� �����Ѵ�.
            static bool RemoveCharInStringFromBack(char* str, char rmChar);
            
            static bool RemoveCharForParsingInString(const char* strOrg, /*OUT*/ char* strNew, int newStrMaxLen); // �־��� ���ڿ����� , ���ڿ� �Ľ��� ���� ���ʿ���  ���ڸ� ��� �����ؼ� �� ���ڿ��� �����Ѵ�. 
            static bool RemoveCharForParsingInString(char* str); // �־��� ���ڿ����� , ���ڿ� �Ľ��� ���� ���ʿ���  ���ڸ� ��� �����ؼ� �� ���ڿ��� �����Ѵ�. 

#if 0
            static bool RemoveBackCharInString(const char* strOrg,
                /*OUT*/ char* strNew, int newStrMaxLen,
                const char* rmCharArr, int rmCharCnt); // �־��� ���ڿ� �޺κп��� , Char�迭�� ��ϵ� ���ڸ� ��� �����ؼ� �� ���ڿ��� �����Ѵ�. 
            static bool RemoveBackCharForParsingInString(const char* strOrg, /*OUT*/ char* strNew, int newStrMaxLen); // �־��� ���ڿ����� , ���ڿ� �Ľ��� ���� ���ʿ���  ���ڸ� ��� �����ؼ� �� ���ڿ��� �����Ѵ�. 
#endif
            
          
            // "0x01, 0xAb, ..." 16������ ���ڹ迭�� ��ȯ��  
            static bool ConvertHexStringToHexArray(const char* strHexString, char delim, unsigned char* hexArrary, int reqArrCnt, int* retArrCnt);

            // "3, 0xAb, ..." ��  10����/16���� ȥ��� ���ڿ��� ���� �迭�� ��ȯ��
            static bool ConvertNumberStringToIntArray(const char* strNumberString, char delim, int* numberArrary, int maxNumberArrCnt, int* retArrCnt);
                                    
            static bool ConvertHexArrayToHexString(const unsigned char* hexArrary, int arrCount, /*OUT*/char* strHexString, char delim);
            
            static bool ConvertIntStringToIntArray(const char* strIntString, char delim, int* intArrary, int reqArrCnt, int* retArrCnt);

            static int ConvertNumberStringToInt(const char* strNumberString);
            static bool ConvertIntArrayToDecimalString(int* valueArr, int arrCount, char delim, /*OUT*/ char *szIntArr);
            static bool ConvertIntArrayToHexString(int* valueArr, int arrCount, char delim, int hexDispFmtCnt, /*OUT*/ char* szIntArr);

            // A->1  B->2 ...     AA->(26+1),     0���� ���ų� ������ ���� 
            static int ConvertExcelColumnToNumber(const char* str);

            /*

            */
            static bool TEDGetChipIDInDummyString(const char* str, /*OUT*/ unsigned char* chipid); // ȥ��� ���ڿ� �ӿ���  TED Chip ID 5�ڸ� �и� 

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
            static std::string  SplitFileName(std::string strPathFileName); // �Էµ� ��ü ���ϸ��� �����̸��� �̾Ƴ���. ex) "c:\mylib\aa.dat" => "aa"
        };

    };  //namespace Utils
};  // namespace Comm

#endif

