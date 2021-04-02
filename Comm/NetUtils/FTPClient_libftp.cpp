#include <Comm/Global/BuildOptions.h>
#define CLOG_TAG "FTPClient_libftp"
#include <Comm/OAL/HeaderFiles.hpp>
#include <Comm/NetUtils/FTPClient_libftp.hpp>
#include <Comm/Utils/HeaderFiles.hpp>
#include <Comm/Property/Path.hpp>


#define REMOVE_FRONT_SPACE(a) \
    while (a) { \
       char c = *a;   \
       if (c != ' ') break; \
       a++;  \
    }


namespace Comm {
    namespace NetUtils {

        FTPClient_libftp::FTPClient_libftp() {
            FtpInit();
        }

        FTPClient_libftp::~FTPClient_libftp() {

        }

        
        bool FTPClient_libftp::Connect(const char* serverIPAddr, int portNum) {

            bool bRet;

            bRet = (bool)FtpConnect(serverIPAddr, portNum, &_NetBuf);
            
            return bRet;
        }

        bool FTPClient_libftp::Login(const char* id, const char* pw) {

            bool bRet;

            bRet = (bool)FtpLogin(id, pw, _NetBuf);

            return bRet;
        }

        bool FTPClient_libftp::Quit() {

            
            FtpQuit(_NetBuf);

            return true;
        }

        bool FTPClient_libftp::Close() {

            FtpClose(_NetBuf);

            return true;
        }

#if 0
        bool FTPClient_libftp::Dir(const char* dir, /*OUT*/ char* dirRespBuf, int bufMaxByteSize) {

            const char* localFile = FTP_DATA_FILE_DIR"ftpdir-232239.txt";
            bool bRet = (bool)FtpDir(localFile, dir, _NetBuf);

            dirRespBuf[0] = '\0';

            if (bRet) {
                FILE* fp = fopen(localFile, "r");
                if (fp) {
                    char buf[512];
                    while (1) {
                        char* s = fgets(buf, 512, fp);
                        if (s) {
                            strcat(dirRespBuf, s);
                        }
                        else {
                            break;
                        }
                    }
                    fclose(fp);
                }
            }

            return bRet;
        }
#endif

        std::vector<std::shared_ptr<Comm::OAL::FileSys::File>> FTPClient_libftp::Dir(std::string dir, int appID) {
        
            bool bRet;
            std::vector<std::shared_ptr<Comm::OAL::FileSys::File>> vecFile;
            char* fileName = new char[1024*8];
            assert(fileName);

            char szTmp[128];
            
            std::string strLocalFile;
            strLocalFile = Comm::Property::Path::GetTmpRoot();
            strLocalFile += Comm::Property::Path::GetFilePathDelimChar();
            sprintf(szTmp, "ftpdir-%d-%d", Comm::OAL::System::GetTickCount32(), appID);
            strLocalFile += szTmp;

            bRet = FtpNlst(strLocalFile.c_str(), dir.c_str(), _NetBuf);
            if (bRet) {
                FILE* fp = fopen(strLocalFile.c_str(), "r");
                if (fp) {
                    char buf[512];
                    while (1) {
                        char* s = fgets(buf, 512, fp);
                        if (s) {
                            char szDate[32];
                            unsigned int fileSize;
                            
                            strcpy(fileName, s);
                            Comm::Utils::StringTool::RemoveCharInStringFromBack(fileName);

                            bRet=(bool)FtpSize(fileName, &fileSize, FTPLIB_ASCII, _NetBuf);
                            if (bRet) {
                                //CLOGI("bRet=%d File[%s] Size[%d] ", bRet, fileName, fileSize);
                                szDate[0] = '\0';
                                bRet = (bool)FtpModDate(fileName, szDate, sizeof(szDate), _NetBuf);
                                if (bRet) {
                                 
                                    std::string strFileName;
                                    long long fileByteSize = -1;
                                    time_t lastAccessGmtTime;
                                    time_t lastWriteGmtTime;


                                    //파일 이름 설정 
                                    bRet = false;
                                    for (int i = (int)strlen(fileName) - 1; i >= 0; i--) {
                                        char c = fileName[i];
                                        if (c == '/') {
                                            strFileName = (const char*)&fileName[i + 1];
                                            bRet = true;
                                            break;
                                        }
                                    }

                                    if (bRet) {
                                        //파일 크기 설정 
                                        fileByteSize = (long long)fileSize & UINT_MAX;

                                        //파일 날짜 설정 , Ftp서버는 Gmt(UTC) Time을 보낸다고 가정한다. 
                                        //
                                        // 20200624141441
                                        // 2020 06 24 14 14 41
                                        int year, month, day, hour, min, sec;
                                        int idx=0, w;
                                        char sztmp[32];

                                        w = 4; 
                                        memcpy(sztmp, &szDate[idx], w); sztmp[w] = '\0';
                                        year = atoi(sztmp);  idx += w;

                                        w = 2;
                                        memcpy(sztmp, &szDate[idx], w); sztmp[w] = '\0';
                                        month = atoi(sztmp);  idx += w;

                                        w = 2;
                                        memcpy(sztmp, &szDate[idx], w); sztmp[w] = '\0';
                                        day = atoi(sztmp);  idx += w;

                                        w = 2;
                                        memcpy(sztmp, &szDate[idx], w); sztmp[w] = '\0';
                                        hour = atoi(sztmp);  idx += w;

                                        w = 2;
                                        memcpy(sztmp, &szDate[idx], w); sztmp[w] = '\0';
                                        min = atoi(sztmp);  idx += w;

                                        w = 2;
                                        memcpy(sztmp, &szDate[idx], w); sztmp[w] = '\0';
                                        sec = atoi(sztmp);  idx += w;

                                        lastAccessGmtTime = 0;
                                        lastWriteGmtTime = Comm::OAL::DateTime::GetUtcTime(year, month, day, hour, min, sec);

                                        std::shared_ptr<OAL::FileSys::File> file = std::make_shared< OAL::FileSys::File>(dir, strFileName, lastAccessGmtTime, lastWriteGmtTime, fileByteSize);
                                        vecFile.push_back(file);
                                    }
                                }
                            }

                            
                        }
                        else {
                            break;
                        }
                    }
                }
            }

            delete[] fileName;
            Comm::OAL::FileSys::RemoveFile(strLocalFile);

            return vecFile;
        }

        bool FTPClient_libftp::Get(std::string strFtpFileName, std::string strLocalFileName, void* cbArg, Comm_NetUtils_FtpGetCallback cbfunc) {
        
            bool bRet = FtpGetWithCB(strLocalFileName.c_str(), /*const char* output*/
                                    strFtpFileName.c_str(),  /*const char* path*/
                                     FTPLIB_IMAGE /*char mode*/,
                                     _NetBuf /*netbuf * nControl*/, 
                                     cbArg, cbfunc);
            return bRet;
        }

    }; //namespace Socket {
}; // namespace Comm {

