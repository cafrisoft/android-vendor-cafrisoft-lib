#include <Comm/Utils/Property.hpp>

namespace Comm {
    namespace Utils {

        namespace Property {


            CLASS_SINGLETON_PATTERN_IMPLEMENT_C1(CS);

            CS::CS() {
                _Mutex = OAL::Mutex::CreateObject(0x98299829);
                assert(_Mutex);
            }

            bool CS::Lock() {
                _Mutex->Lock();
                return true;
            }

            bool CS::Unlock() {
                _Mutex->Unlock();
                return true;
            }

            bool SaveData(std::string strFileName, /*In*/const void* dataBuf, int dataSize) {
            
                bool bRet = false;
                FILE* fp = fopen(strFileName.c_str(), "wb");
                if (fp) {
                    int wrsz = 0, verifyWrsz = 0;
                    verifyWrsz += (int)fwrite(&dataSize, 1, sizeof(int), fp);  wrsz += sizeof(int);
                    verifyWrsz += (int)fwrite(dataBuf, 1, dataSize, fp); wrsz += dataSize;
                    fclose(fp);
                    if (verifyWrsz == wrsz) {
                        bRet = true;
                    }
                }
                return bRet;
            }

            bool LoadData(std::string strFileName, /*Out*/unsigned char* dataBuf, int dataBufMaxByteSize, /*OUT*/ int* dataSize) {
            
                bool bRet = false;
                int retDataSize = 0;

                assert(dataBuf);

                FILE* fp = fopen(strFileName.c_str(), "rb");
                if (fp) {
                    int dsz = 0;
                    int rdsz = 0, verifyRdsz = 0;
                    
                    //데이타 길이 읽기 
                    verifyRdsz += (int)fread(&dsz, 1, sizeof(int), fp); rdsz += sizeof(int);
                    if ( (dsz > 0) && (dsz <= dataBufMaxByteSize) ) {
                        verifyRdsz += (int)fread((void*)dataBuf, 1, dsz, fp); rdsz += dsz;
                    }
                    else {
                        dsz = 0;
                        memset(dataBuf, 0x00, dataBufMaxByteSize);
                    }
                    fclose(fp);

                    if (rdsz == verifyRdsz) {
                        bRet = true;
                        retDataSize = dsz;
                    }
                }

                if (dataSize) *dataSize = retDataSize;

                return bRet;
            }

            bool SaveString(std::string strFileName, std::string strValue) {

                return SaveData(strFileName, (const void*)strValue.c_str(), (int)strValue.size());
            }

            std::string LoadString(std::string strFileName) {
                
                bool bRet;
                int dataSize;
                std::string strValue;
                char* szBuf = new char[4096];
                assert(szBuf);

                bRet = LoadData(strFileName, (unsigned char*)szBuf, 4096, &dataSize);
                if (bRet) {
                    szBuf[dataSize] = '\0';
                    strValue = szBuf;
                }

                delete[] szBuf;
                return strValue;
            }
        }


    };
};