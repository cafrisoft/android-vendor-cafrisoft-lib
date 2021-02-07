#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/HeaderFiles.hpp>
#include <TESys/Utils/Tmd2Py.hpp>

using namespace Comm;
using namespace TESys::Utils;


int main(int argc, char* argv[] ) {
    
#if 0  //Manual Power Seq
    const char* tmdFileName = "D:\\Project_AgingSys\\Develop\\TEDTool\\TMD\\T4\\A2-655UV01-OTP-DEV190904-ANA6705_MAN.TMD";
    const char* pyFileName = "D:\\work\\A2-655UV01-OTP-DEV190904-ANA6705_MAN.py";
    const char* pyTailFileName = "D:\\work\\tmd2py-tail.py";
#endif

#if 0  //Auto Boot R/G/B
    const char* tmdFileName = "D:\\Work\\A2-655UV01-OTP-DEV190904-ANA6705-HHT.TMD";
    const char* pyFileName = "D:\\work\\A2-655UV01-OTP-DEV190904-ANA6705-HHT.py";
    const char* pyTailFileName = "D:\\work\\tmd2py-tail.py";
#endif

#if 0  //ANA6706, 
#define TMD_FILENAME "D:\\Project_AgingSys\\Develop\\test-system-app\\Doc\\TMD\\ANA6706\\A3-AMB640UP01-M-FMTP-00_ANAPASS_final_190825"
    const char* tmdFileName = TMD_FILENAME".TMD";
    const char* pyFileName = TMD_FILENAME".py";
    const char* pyTailFileName = TMD_FILENAME"-tail.py";
#endif


#if 1  
    //T:\SoC\SoC_SI\업무공유\2. Product\ANA6706\3. EEPROM\TMD\T5\KDH\OPPO\1218 FINAL
    //A3-AMB678UW01-MTP(FT)-DEV-190904_ManualSeq_Normal.TMD
#define TMD_FILE_PATH "D:\\Project_AgingSys\\Develop\\test-system-app\\Doc\\TMD\\ANA6706\\"
#define TMD_FILENAME "A3-AMB678UW01-MTP(FT)-DEV-190904_ManualSeq_Normal"
#define TMD_FILE_FULL_NAME TMD_FILE_PATH TMD_FILENAME 
    const char* tmdFileName = TMD_FILE_FULL_NAME".TMD";
    const char* pyFileName = TMD_FILE_FULL_NAME".py";
    const char* pyTailFileName = TMD_FILE_FULL_NAME"-tail.py";
#endif


    //const char* pyFileName = "D:\\Project_AgingSys\\Develop\\anapass-python\\TEDApp\\TESys\\TestCase\\A2_655UV01_OTP_DEV190904_ANA6705_MAN.py";
    //const char* pyFileName = "D:\\Project_AgingSys\\Develop\\anapass-python\\TEDApp\\TESys\\TestCase\\A2_655UV01_OTP_DEV190904_ANA6705_MAN.py";

    int slen;
    bool isFuncIn = false;
    char *s, *a, *b;
    FILE* fpTmd, * fpPy;
    
    int funcLineCnt = 0;
    char szLastFuncType[128];
    char szLastFuncName[128];

    const int BUF_SIZE = 1024 * 16;

    char* buf = new char[BUF_SIZE];
    char* szPy = new char[BUF_SIZE];
    char* szTMDCmdArranged = new char[BUF_SIZE];
    char* szPyCmd = new char[BUF_SIZE];
    assert(buf);
    assert(szPy);
    assert(szTMDCmdArranged);
    assert(szPyCmd);

    fpTmd = fopen(tmdFileName, "r");
    assert(fpTmd);

    fpPy = fopen(pyFileName, "w");
    assert(fpTmd);

    Tmd2Py::WriteHeaderToPyFile(fpPy);

    while (1) {

        s = fgets(buf, 1024 * 16, fpTmd);
        if (s == NULL) {
            break;
        }

        //문장끝 \n,\r, ' ' 제거 
        slen = (int)strlen(s);
        for (int i = slen - 1; i >= 0; i--) {
            if (s[i] == '\n') s[i] = '\0';
            else if (s[i] == '\r') s[i] = '\0';
            else if (s[i] == ' ') s[i] = '\0';
            else break;
        }

        //문장내 \t 제거 
        slen = (int)strlen(s);
        for (int i = 0; i < slen; i++) {
            if (s[i] == '\t') s[i] = ' ';
        }

        //문장앞 ' ' 제거 
        slen = (int)strlen(s);
        for (int i = 0; i < slen; i++) {
            if (s[i] != ' ') {
                s = &s[i];
                break;
            }
        }


        if (strncmp(s, "[INIT]", 6) == 0) {

            //if (isFuncIn && funcLineCnt == 0) Tmd2Py::WriteFuncPassToPyFile(fpPy);
            if (isFuncIn) Tmd2Py::WriteFuncEndToPyFile(fpPy, szLastFuncType, szLastFuncName);
            
            isFuncIn = false;
            a = &s[1];
            b = strchr(a, ']');

            //함수를 찾았다. 다음 함수( "[" 로 시작하는 구문...) 가 나올때까지 device.SendTxtCmd 로 만든다. 
            if (b != NULL) {
                Tmd2Py::WriteFuncTitleToPyFile(fpPy, NULL, "INIT");
                
                strcpy(szLastFuncType, "");
                strcpy(szLastFuncName, "INIT");
                funcLineCnt = 0;
                isFuncIn = true;
            }
            else {
                isFuncIn = false;
                assert(1);
            }

        }
        else if (strncmp(s, "[FUN/", 5) == 0)   {

            //if (isFuncIn && funcLineCnt == 0) Tmd2Py::WriteFuncPassToPyFile(fpPy);
            if (isFuncIn) Tmd2Py::WriteFuncEndToPyFile(fpPy, szLastFuncType, szLastFuncName);

            isFuncIn = false;
            a = &s[5];
            b = strchr(a, ']');
            //함수를 찾았다. 다음 함수( "[" 로 시작하는 구문...) 가 나올때까지 device.SendTxtCmd 로 만든다. 
            if (b != NULL) {
                *b = '\0';
                char* funcName = a;
                Tmd2Py::WriteFuncTitleToPyFile(fpPy, "FUN", funcName);
                
                strcpy(szLastFuncType, "FUN");
                strcpy(szLastFuncName, funcName);
                funcLineCnt = 0;
                isFuncIn = true;
            }
            else {
                isFuncIn = false;
                assert(1);
            }
        }
        else if (strncmp(s, "[ACT/", 5) == 0) {

            //if (isFuncIn && funcLineCnt == 0) Tmd2Py::WriteFuncPassToPyFile(fpPy);
            if (isFuncIn) Tmd2Py::WriteFuncEndToPyFile(fpPy, szLastFuncType, szLastFuncName);

            isFuncIn = false;
            a = &s[5];
            b = strchr(a, ']');
            //함수를 찾았다. 다음 함수( "[" 로 시작하는 구문...) 가 나올때까지 device.SendTxtCmd 로 만든다. 
            if (b != NULL) {
                *b = '\0';
                char* funcName = a;
                Tmd2Py::WriteFuncTitleToPyFile(fpPy, "ACT", funcName);
                
                strcpy(szLastFuncType, "ACT");
                strcpy(szLastFuncName, funcName);
                funcLineCnt = 0;
                isFuncIn = true;
            }
            else {
                isFuncIn = false;
                assert(1);
            }
        }
        else if (strncmp(s, "[INFO]", 6) == 0) {

            //if (isFuncIn && funcLineCnt == 0) Tmd2Py::WriteFuncPassToPyFile(fpPy);
            if (isFuncIn) Tmd2Py::WriteFuncEndToPyFile(fpPy, szLastFuncType, szLastFuncName);

            // [INFO]
            //PRINTF("%s", s);
            
            isFuncIn = false;
        }
        else if (strncmp(s, "[QUIT]", 6) == 0) {

            //if(isFuncIn && funcLineCnt==0) Tmd2Py::WriteFuncPassToPyFile(fpPy);
            if (isFuncIn) Tmd2Py::WriteFuncEndToPyFile(fpPy, szLastFuncType, szLastFuncName);

            //PRINTF("%s", s);
            isFuncIn = false;
        }
        else if (strncmp(s, "[END]", 5) == 0) {

            //if (isFuncIn && funcLineCnt == 0) Tmd2Py::WriteFuncPassToPyFile(fpPy);
            if (isFuncIn) Tmd2Py::WriteFuncEndToPyFile(fpPy, szLastFuncType, szLastFuncName);

            //PRINTF("%s", s);
            isFuncIn = false;
        }
        else if (strncmp(s, "[", 1) == 0) {
            // [INFO]
            PRINTF("%s", s);
            assert(1);
        }
        else if (isFuncIn) {
        
            const char* tmdCmdOriginal = s;

            //TMD명령을 Python명령으로 변환 
            Tmd2Py::CommandArrange(tmdCmdOriginal, szTMDCmdArranged);
            if (strlen(szTMDCmdArranged) > 0) {

                //const char* tmdCmdDebug = "WREG0=0x39,0xF8,DRD0,DRD1";
                //if (strcmp(tmdCmdDebug, szTMDCmdArranged) == 0) {
                  //  printf("breakPoint");
                //}


                //TMD명령을 Python명령으로 변환
                Tmd2Py::ConvertTmdCmdToPyCmd(tmdCmdOriginal, szTMDCmdArranged, szPyCmd);
                
                //파일에 쓰기
                Tmd2Py::WriteFuncBodyToPyFile(fpPy, szPyCmd, tmdCmdOriginal);
                funcLineCnt++;
            }

        }
    }

    Tmd2Py::WriteTailToPyFile(fpPy, pyTailFileName);

    fclose(fpTmd);
    fclose(fpPy);
    
    delete[] buf;
    delete[] szPy;
    delete[] szTMDCmdArranged;
    delete[] szPyCmd;

    return 0;
}

