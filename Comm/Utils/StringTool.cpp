#include <Comm/Utils/StringTool.hpp>
#include <Comm/Property/Path.hpp>

namespace Comm {
    namespace Utils {


        bool StringTool::MakeUpper(char* wszName)
        {
            char ch;
            int i;
            int strLength;

            strLength = (int)strlen(wszName);
            for (i = strLength - 1; i >= 0; i--)
            {
                ch = wszName[i];
                if (ch >= 'a' && ch <= 'z')
                {
                    ch -= 'a';
                    ch += 'A';
                    wszName[i] = ch;
                }
            }

            return true;
        }

        bool StringTool::MakeLower(char* wszName)
        {
            char ch;
            int i;
            int strLength;

            strLength = (int)strlen(wszName);
            for (i = strLength - 1; i >= 0; i--)
            {
                ch = wszName[i];
                if (ch >= 'A' && ch <= 'Z')
                {
                    ch -= 'A';
                    ch += 'a';
                    wszName[i] = ch;
                }
            }

            return true;
        }

        // 주어진 문자열에서 , Char배열에 등록된 문자를 모두 제거해서 새 문자열로 리턴한다. 
        bool StringTool::RemoveCharInString(const char* strOrg,
            /*OUT*/ char* strNew, int newStrMaxLen,
            const char* rmCharArr, int rmCharCnt) {
            int orgStrLen = (int)strlen(strOrg);
            int i, ic;
            char c;
            char* n;
            bool bSkip;

            n = strNew;
            for (i = 0; i < orgStrLen; i++) {

                c = strOrg[i];
                bSkip = false;
                for (ic = 0; ic < rmCharCnt; ic++) {
                    if (c == rmCharArr[ic]) {
                        bSkip = true;
                        break;
                    }
                }

                if (bSkip == false) {
                    if ((n - strNew) < (newStrMaxLen - 1)) {
                        *n = c;
                        n++;
                    }
                }
            }
            *n = '\0';

            return true;
        }


        // 주어진 문자열에서 , Char배열에 등록된 문자를 모두 제거해서 새 문자열로 리턴한다. 
        bool StringTool::RemoveCharInString(char* str, const char* rmCharArr, int /*rmCharCnt*/) {

            bool mmpResult = false;
            int szNewLen = (int)(strlen(str) + 16);
            char* strNew = new char[szNewLen];

            if (strNew != NULL) {
                mmpResult = StringTool::RemoveCharInString(str, strNew, szNewLen, rmCharArr, sizeof(rmCharArr));
                if (mmpResult == true) {
                    strcpy(str, strNew);
                }
                delete [] strNew;
            }

            return mmpResult;
        }

        bool StringTool::RemoveCharInString(char* str, char rmChar) {

            return StringTool::RemoveCharInString(str, &rmChar, 1);
        }

        //문장에서 rmCharArr에 포함된 문자열은 모두 제거해서  std::string으로 리턴 
        std::string StringTool::RemoveCharInString(const char* sz, const char* rmCharArr) {
        
            std::string str = "";

            int szLen = (int)strlen(sz);
            int rmCharLen = (int)strlen(rmCharArr);

            for (int i = 0; i < szLen; i++) {
                
                char c = sz[i];
                bool isSkip = false;

                for (int j = 0; j < rmCharLen; j++) {
                    char r = rmCharArr[j];
                    if (r == c) {
                        isSkip = true;  // 문자 c 는  제거목록에 있는 문자이므로,  복사하지 않는다. 
                        break;
                    }
                }

                if (isSkip == false) {
                    str += c;
                }
            }

            return str;
        }

        //문장 뒤쪽의 주어진 문자를 제거한다.
        bool StringTool::RemoveCharInStringFromBack(char* str, const char* rmCharArr) {
        
            int i, j;
            int slen = (int)strlen(str);
            int rmCharCnt = (int)strlen(rmCharArr);

            for (i = slen - 1; i >= 0; i--) {
                char c = str[i];

                //rmchar중 같은 문자가 있는지 찾는다.
                for (j = 0; j < rmCharCnt; j++) {
                    if (c == rmCharArr[j]) {
                        break;
                    }
                }

                if (j < rmCharCnt) {
                    //rmchar중 같은 문자가 있으면,  NULL입력
                    str[i] = '\0';
                }
                else {
                    //rmchar중 같은 문자가 없으면, 비교 중지, 함수 종료
                    break;
                }

            }

            return true;
        }

        //문장 뒤쪽의 주어진 문자를 제거한다.
        bool StringTool::RemoveCharInStringFromBack(char* str, char rmChar) {

            int i;
            int slen = (int)strlen(str);
            for (i = slen - 1; i >= 0; i--) {
                char c = str[i];

                if (c == rmChar) {
                    //rmchar중 같은 문자가 있으면,  NULL입력
                    str[i] = '\0';
                }
                else {
                    //rmchar중 같은 문자가 없으면, 비교 중지, 함수 종료
                    break;
                }

            }

            return true;
        }

        // 주어진 문자열에서 , 문자열 파싱을 위해 불필요한  문자를 모두 제거해서 새 문자열로 리턴한다.   [   Space  TAN \n \r
        bool StringTool::RemoveCharForParsingInString(const char* strOrg, /*OUT*/ char* strNew, int newStrMaxLen) {

            char rmCharArr[] = { ' ', '\n', '\r', '\t' };

            return StringTool::RemoveCharInString(strOrg, strNew, newStrMaxLen, rmCharArr, sizeof(rmCharArr));
        }


        // 주어진 문자열에서 , 문자열 파싱을 위해 불필요한  문자를 모두 제거해서 새 문자열로 리턴한다. 
        bool StringTool::RemoveCharForParsingInString(char* str) {

            bool mmpResult = false;
            int szNewLen = (int)(strlen(str) + 16);
            char* strNew = new char[szNewLen];

            if (strNew != NULL) {
                mmpResult = StringTool::RemoveCharForParsingInString(str, strNew, szNewLen);
                if (mmpResult == true) {
                    strcpy(str, strNew);
                }
                delete[] strNew;
            }

            return mmpResult;
        }

#if 0
        // 주어진 문자열 뒷부분에서 , Char배열에 등록된 문자를 모두 제거해서 새 문자열로 리턴한다. 
        bool StringTool::RemoveBackCharInString(const char* strOrg,
            /*OUT*/ char* strNew, int newStrMaxLen,
            const char* rmCharArr, int rmCharCnt) {
            int orgStrLen = (int)strlen(strOrg);
            int i, ic;
            char c;

            strcpy(strNew, strOrg);
            for (i = orgStrLen - 1; i >= 0; i--) {

                c = strNew[i];
                for (ic = 0; ic < rmCharCnt; ic++) {
                    if (c == rmCharArr[ic]) {
                        strNew[i] = '\0';
                        break;
                    }
                }
                if (ic == rmCharCnt) {
                    break;
                }

            }

            return true;
        }
#endif
        
        
        bool StringTool::ConvertHexStringToHexArray(const char* strHexString, char delim, unsigned char* hexArray, int reqArrCnt, int* retArrCnt) {

            char* a, * b;
            char* szSrc = new char[strlen(strHexString) + 16];
            int hexArrCnt = 0;

            if (szSrc != NULL) {
                strcpy(szSrc, strHexString);
            }

            a = szSrc;
            while (a != NULL) {
                b = strchr(a, delim);
                if (b != NULL) {
                    *b = '\0';
                    b++;
                }

                if (hexArrCnt < reqArrCnt) {
                    hexArray[hexArrCnt] = (char)strtol(a, NULL, 16);
                    hexArrCnt++;
                }

                a = b;
            }

            if (retArrCnt) *retArrCnt = hexArrCnt;
            if (szSrc) delete[] szSrc;

            return true;
        }

        // "0x01, 0xAb, ..." 16진수만 숫자배열로 변환함  
        bool StringTool::ConvertNumberStringToIntArray(const char* strNumberString, char delim, int* numberArrary, int maxNumberArrCnt, int* retArrCnt) {
        
            bool bRet = false;
            char* a, * b;
            char* szSrc = new char[strlen(strNumberString) + 16];
            int numArrCnt = 0;
            int errCnt = 0;

            if (szSrc != NULL) {
                strcpy(szSrc, strNumberString);
            }

            a = szSrc;
            while (a != NULL) {
                b = strchr(a, delim);
                if (b != NULL) {
                    *b = '\0';
                    b++;
                }

                if (numArrCnt < maxNumberArrCnt) {

                    if (StringTool::IsDecimalNumber(a)) {
                        if(numberArrary) numberArrary[numArrCnt] = strtol(a, NULL, 10);
                        numArrCnt++;
                    }
                    else if (StringTool::IsHexNumber(a)) {
                        if (numberArrary) numberArrary[numArrCnt] = strtol(a, NULL, 16);
                        numArrCnt++;
                    }
                    else {

                        int slen = (int)strlen(a);
                        for (int i = 0; i < slen; i++) {
                            char c = a[i];
                            if ((c == ' ') || (c == '\n') || (c == '\r')) {
                            
                            }
                            else {
                                errCnt++;
                            }
                        }
                        break;
                    }
                }

                a = b;
            }

            if (retArrCnt) *retArrCnt = numArrCnt;
            if (szSrc) delete[] szSrc;

            if ( (errCnt == 0) && (numArrCnt > 0)) {
                bRet = true;
            }
            else {
                bRet = false;
            }

            return bRet;
        }

        int StringTool::ConvertNumberStringToInt(const char* strNumberString) {
        
            int num = 0;

            if (StringTool::IsHexNumber(strNumberString)) {
                num = strtol(strNumberString, NULL, 16);
            }
            else if (StringTool::IsDecimalNumber(strNumberString)) {
                num = strtol(strNumberString, NULL, 10);
            }
            else {
                assert(1);
            }

            return num;

        }

        bool StringTool::ConvertIntArrayToDecimalString(int* valueArr, int arrCount, char delim, /*OUT*/ char* szIntArr) {
        
            char szTmp[64];

            szIntArr[0] = '\0';
            for (int i = 0; i < arrCount; i++) {
                if (i == (arrCount - 1)) {
                    sprintf(szTmp, "%d", valueArr[i]);
                }
                else {
                    sprintf(szTmp, "%d%c", valueArr[i], delim);
                }
                strcat(szIntArr, szTmp);
            }

            return true;
        }

        bool StringTool::ConvertIntArrayToHexString(int* valueArr, int arrCount, char delim, int hexDispFmtCnt, /*OUT*/ char* szIntArr) {

            char szTmp[64];
            char szFmt[32];
            char szFmtEnd[32];

            sprintf(szFmt, "0x%c0%dX%cc", '%', hexDispFmtCnt, '%');
            sprintf(szFmtEnd, "0x%c0%dX", '%', hexDispFmtCnt);

            szIntArr[0] = '\0';
            for (int i = 0; i < arrCount; i++) {
                if (i == (arrCount - 1)) {
                    sprintf(szTmp, szFmtEnd, valueArr[i]);
                }
                else {
                    sprintf(szTmp, szFmt, valueArr[i], delim);
                }
                strcat(szIntArr, szTmp);
            }

            return true;
        }

        bool StringTool::ConvertHexArrayToHexString(const unsigned char* hexArrary, int arrCount, /*OUT*/char* strHexString, char delim) {
        
            char szTmp[32];
            
            strHexString[0] = '\0';
            for (int i = 0; i < arrCount; i++) {
                if (i == (arrCount - 1)) {
                    sprintf(szTmp, "0x%02X0x", hexArrary[i]);
                }
                else {
                    sprintf(szTmp, "0x%02X0x%c", hexArrary[i], delim);
                }
                strcat(strHexString, szTmp);
            }

            return true;
        }

        bool StringTool::ConvertIntStringToIntArray(const char* strIntString, char delim, int* intArray, int reqArrCnt, int* retArrCnt) {
        
            char* a, * b;
            char* szSrc = new char[strlen(strIntString) + 16];
            int intArrCnt = 0;

            assert(szSrc);
            
            if (szSrc != NULL) {
                strcpy(szSrc, strIntString);
            }

            a = szSrc;
            while (a != NULL) {

                int slen = (int)strlen(a);
                for (int i = 0; i < slen; i++) {
                    char c = *a;
                    if ((c == ' ') || (c == '\n')) {
                        a++;
                    }
                    else {
                        break;
                    }
                }


                b = strchr(a, delim);
                if (b != NULL) {
                    *b = '\0';
                    b++;
                }

                if (intArrCnt < reqArrCnt) {
                    intArray[intArrCnt] = atoi(a); 
                    intArrCnt++;
                }

                a = b;
            }

            if (retArrCnt) *retArrCnt = intArrCnt;
            
            delete[] szSrc;

            return true;
        }

        // 혼재된 문자열 속에서  TED Chip ID 5자리 분리 
        bool StringTool::TEDGetChipIDInDummyString(const char* str, /*OUT*/ unsigned char* chipid) {

            int err = 0;
            char* strContents = new char[strlen(str) + 16];
            bool mmpResult = false;

            if (strContents == NULL) {
                err++;
            }
            else {
                strcpy(strContents, str);
            }


            if (err == 0) {
                // remove 'space' \n \r \t
                StringTool::RemoveCharForParsingInString(strContents);
                StringTool::MakeLower(strContents);


                int szlen = (int)strlen(strContents);
                char* szChipID = NULL;
                char c0, c1;
                const int hexStringByteSize = 5 * 4 + 4; //24   5개 (0xAA,) x 4개 +  4개(0xBB)

                for (int ic = 0; ic < szlen - hexStringByteSize + 2; ic++) {
                    c0 = strContents[ic];
                    c1 = strContents[ic + 1];
                    if (c0 == '0' && c1 == 'x') {

                        char* a = &strContents[ic];
                        int kk;
                        for (kk = 0; kk < 5; kk++) {

                            if (a[0] != '0') break;
                            if (a[1] != 'x') break;

                            if (a[2] >= 'a' && a[2] <= 'f') {
                                /* Nothing to do */
                            }
                            else if (a[2] >= '0' && a[2] <= '9') {
                                /* Nothing to do */
                            }
                            else {
                                break;
                            }

                            if (a[3] >= 'a' && a[3] <= 'f') {
                                /* Nothing to do */
                            }
                            else if (a[3] >= '0' && a[3] <= '9') {
                                /* Nothing to do */
                            }
                            else {
                                break;
                            }

                            if (kk < 4) {
                                if (a[4] != ',') break;
                            }

                            a += 5;
                        } // end of for (int kk = 0; kk < 5; kk++) {

                        if (kk == 5) {
                            szChipID = &strContents[ic];
                            szChipID[hexStringByteSize] = '\0';
                            break;
                        }

                    } // end of if (c0 == '0' && c1 == 'x') {

                }  // end of for (int ic = 0; ic < szlen - hexStringByteSize; ic++) {

                if (szChipID != NULL) {
                    int cnt;
                    StringTool::ConvertHexStringToHexArray(szChipID, ',', chipid, 5, &cnt);
                    if (cnt == 5) {
                        mmpResult = true;
                    }
                }

            }

            if (strContents) delete[] strContents;

            return mmpResult;
        }

        int StringTool::ConvertExcelColumnToNumber(const char* str) {

            int  num;
            int szlen = (int)strlen(str);
            int i, p;

            char c;
            int  a;

            num = 0;
            for (i = szlen - 1, p = 0; i >= 0; i--, p++) {

                c = str[i];
                if ((c >= 'A') && (c <= 'Z')) {
                    c -= 'A';
                    c++;
                    a = ((int)c) & 0xFF;
                }
                else if ((c >= 'a') && (c <= 'z')) {
                    c -= 'a';
                    c++;
                    a = ((int)c) & 0xFF;
                }
                else {
                    //ERROR
                    num = -1;
                    break;
                }

                num += a * pow(26, p);
            }

            return num;
        }


        bool StringTool::ReplaceCharInString(char* str, char old, char new_) {

            int i, szlen = (int)strlen(str);
            char c;
            for (i = 0; i < szlen; i++) {
                c = str[i];
                if (c == old) {
                    str[i] = new_;
                }
            }

            return true;
        }

        bool StringTool::IsDecimalNumber(const char* str) {
        
            bool bRet;
            int slen = (int)strlen(str);
            int strIdx = 0;
            int numCnt = 0;
            int errCnt = 0;
            
            //문자열 앞의 공백은 허용한다. 
            for (; strIdx < slen; strIdx++) {
                char c = str[strIdx];
                if (c==' ') {
                    //Nothin to do 
                }
                else {
                    break;
                }
            }

            //공백이 끝난다음 마이너스 기호는 허용된다.
            if (1) {
                char c = str[strIdx];
                if (c == '-') {
                    strIdx++;
                }
            }

            
            //문자열 중간은 연속된 10진수 숫자만 있어야 한다. 
            for (; strIdx < slen; strIdx++) {
                char c = str[strIdx];
                if ( (c >= '0') && (c <= '9') ) {
                    numCnt++;
                }
                else if ( (c == ' ') || (c == '\n') || (c == '\r') ) {

                    //공백이므로 끝까지 공백만 있어야 한다.
                    strIdx++;
                    for (; strIdx < slen; strIdx++) {
                        c = str[strIdx];
                        if ((c == ' ') || (c == '\n') || (c == '\r')) {
                            /* Nothing to do */
                        }
                        else {
                            errCnt++;  // 공백이 아닌 문자가 섞여 있으므로 ERR
                            break;
                        }
                    }

                    break;
                }
                else {
                    errCnt++;  // 공백이 아닌 문자가 섞여 있으므로 ERR
                    break;
                }
            }

            if ( (errCnt==0)  && (numCnt>0) ) {
                bRet = true;
            }
            else {
                bRet = false;
            }

            return bRet;
        }

        bool StringTool::IsHexNumber(const char* str) {
        
            bool bRet = true;
            int slen = (int)strlen(str);
            int strIdx = 0;
            int numCnt = 0;
            int errCnt = 0;

            //문자열 앞의 공백은 허용한다. 
            for (; strIdx < slen; strIdx++) {
                char c = str[strIdx];
                if (c == ' ') {
                    //Nothin to do 
                }
                else {
                    break;
                }
            }

            //0x 로 시작해야 한다.
            if ( (str[strIdx] == '0') && (str[strIdx + 1] == 'x' || str[strIdx + 1] == 'X') ) {
                
                strIdx += 2;
            }
            else {
                errCnt++;
            }


            //문자열 중간은 연속된 10진수 숫자만 있어야 한다. 
            for (; strIdx < slen; strIdx++) {
                char c = str[strIdx];
                if ( ((c >= '0') && (c <= '9'))  
                    || ((c >= 'A') && (c <= 'F')) 
                    || ((c >= 'a') && (c <= 'f'))
                    ) {
                    numCnt++;
                }
                else if ((c == ' ') || (c == '\n') || (c == '\r')) {

                    //공백이므로 끝까지 공백만 있어야 한다.
                    strIdx++;
                    for (; strIdx < slen; strIdx++) {
                        c = str[strIdx];
                        if ((c == ' ') || (c == '\n') || (c == '\r')) {
                            /* Nothing to do */
                        }
                        else {
                            errCnt++;  // 공백이 아닌 문자가 섞여 있으므로 ERR
                            break;
                        }
                    }

                    break;
                }
                else {
                    errCnt++;
                    break;
                }
            }

            if ((errCnt == 0) && (numCnt > 0)) {
                bRet = true;
            }
            else {
                bRet = false;
            }


            return bRet;
        }

        std::string StringTool::ToStringHex(std::vector<unsigned char> vec, char delim) {

            int idx = 0;
            int cnt = (int)vec.size();
            std::string strValue;

            for (std::vector<unsigned char>::const_iterator it = vec.cbegin();
                it != vec.cend();
                it++) {
            
                unsigned char value = *it;
                char sztmp[32];
                if (idx == 0) {
                    sprintf(sztmp, "0x%02X", (int)value & 0xFF);
                }
                else {
                    sprintf(sztmp, "%c 0x%02X", delim, (int)value & 0xFF);
                }
                strValue += sztmp;

                idx++;
            }

            return strValue;
        }

#if (CommOS==CommOS_WIN)
        std::string StringTool::AnsiToUTF8(std::string strIn) {
      
            std::string strUTF8;
            int nLenOfUni =0, nLenOfUTF=0;
            wchar_t* us = NULL;
            char* pszOut = NULL;

            if ((nLenOfUni = MultiByteToWideChar(CP_ACP, 0, strIn.c_str(), (int)strIn.length(), NULL, 0)) <= 0) {
                
                /*Nothing to do */

            }
            else {

                us = new wchar_t[nLenOfUni + 1];
                memset(us, 0x00, sizeof(wchar_t) * (nLenOfUni + 1));

                // ansi ---> unicode
                nLenOfUni = MultiByteToWideChar(CP_ACP, 0, strIn.c_str(), (int)strIn.length(), us, nLenOfUni);

                if ((nLenOfUTF = WideCharToMultiByte(CP_UTF8, 0, us, nLenOfUni, NULL, 0, NULL, NULL)) <= 0)
                {
                    /*Nothing to do */
                }
                else {
                    pszOut = new char[nLenOfUTF + 1];
                    memset(pszOut, 0x00, sizeof(char) * (nLenOfUTF + 1));

                    // unicode ---> utf8
                    nLenOfUTF = WideCharToMultiByte(CP_UTF8, 0, us, nLenOfUni, pszOut, nLenOfUTF, NULL, NULL);
                    pszOut[nLenOfUTF] = 0;
                    strUTF8 = pszOut;
                }
            }

            if(us) delete[] us;
            if(pszOut) delete[] pszOut;

            return strUTF8;
        }
#else

        std::string StringTool::AnsiToUTF8(std::string strIn) {
            return strIn;
        }

#endif


        // 입력된 전체 파일명에서 파일이름만 뽑아낸다. ex) "c:\mylib\aa.dat" => "aa"
        std::string  StringTool::SplitFileName(std::string strPathFileName) {
         
            std::string retStr;
            int  pos;
            char delim = Comm::Property::Path::GetFilePathDelimChar();
            char* szPathFileName = new char[strPathFileName.size() + 1024];
            assert(szPathFileName);

            strcpy(szPathFileName, strPathFileName.c_str());
            int strLength = (int)strlen(szPathFileName);

            for (pos = strLength - 1; pos >= 0; pos--) {
                char ch = szPathFileName[pos];
                if (ch == delim) {
                    break;
                }
            }
            retStr = &szPathFileName[pos + 1];
            
            delete[] szPathFileName;

            return retStr;
        }

    }; //namespace Utils
}; //namespace Comm

