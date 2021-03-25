#include <Comm/Utils/TxtFile.hpp>
#include <Comm/Utils/StringTool.hpp>

namespace Comm {
    namespace Utils {
        namespace TxtFile {

            std::vector<std::string> ReadLineString(std::string strFileName) {
            
                std::vector<std::string> lineVec;
                FILE* fp;

                fp = fopen(strFileName.c_str(), "r");
                if (fp) {
                    const int BUFSIZE = 1024 * 16;
                    char* buf = new char[BUFSIZE];
                    assert(buf);

                    while (true) {
                        memset(buf, 0x00, BUFSIZE);
                        char* p = fgets(buf, BUFSIZE, fp);
                        if (p) {
                            //문자열 뒤 , 특수문자를 제거한다. 
                            Comm::Utils::StringTool::RemoveCharInStringFromBack(p, " \n\r\t\\");
                            if (strlen(p) > 0) {
                                lineVec.push_back(p);
                            }
                        }
                        else {
                            break;
                        }
                    }
                
                    fclose(fp);
                    delete[] buf;
                }

                
                return lineVec;
            }

            bool WriteInt(std::string strFileName, int value) {
            
                bool bRet = false;
                FILE* fp = fopen(strFileName.c_str(), "w");
                if (fp) {
                    fprintf(fp, "%d", value);
                    fclose(fp);
                    bRet = true;
                }
                return bRet;
            }

            int ReadInt(std::string strFileName, /*OUT*/int* err) {

                int value = -1;

                if (err != NULL) {
                    *err = 1;
                }

                FILE* fp = fopen(strFileName.c_str(), "r");
                if (fp) {
                    char szTmp[128+1];
                    char* p=fgets(szTmp, 128, fp);
                    if (p) {
                        Comm::Utils::StringTool::RemoveCharInStringFromBack(p);
                        if (Comm::Utils::StringTool::IsDecimalNumber(p) == true) {
                            value = atoi(p);
                            if (err != NULL) {
                                *err = 0;
                            }
                        }
                    }
                    fclose(fp);
                }

                return value;
            }


            int ReadInt(std::string strFileName, const char* propName, char delim, /*OUT*/int* err) {

                int value = -1;

                if (err != NULL) {
                    *err = 1;
                }

                FILE* fp = fopen(strFileName.c_str(), "r");
                if (fp) {
                    char szTmp[128 + 1];
                    char* p = fgets(szTmp, 128, fp);
                    if (p) {
                        
                        Comm::Utils::StringTool::RemoveCharInStringFromBack(p);

                        char* a, * b;
                        a = p;
                        b = strstr(a, propName);
                        if (b) {

                            a = b + strlen(propName);
                            b = strchr(a, delim);
                            if (b) {
                                a = b + 1;
                                if (Comm::Utils::StringTool::IsDecimalNumber(a) == true) {
                                    value = atoi(a);
                                    if (err != NULL) {
                                        *err = 0;
                                    }
                                }
                            }
                        }
                    }
                    fclose(fp);
                }

                return value;
            }



        }; //namespace TxtFile
    }; //namespace Utils
}; //namespace Comm



