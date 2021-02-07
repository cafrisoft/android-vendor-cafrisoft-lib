#include "FileSync.hpp"
#include <TESys/Property/FileSync.hpp>
#include <TESys/Property/Tester.hpp>
#include <TESys/Property/Path.hpp>
#include <TESys/Property/Net.hpp>

using namespace Comm;
using namespace TESys;


class FtpDnFile {
public:
    std::string _Title;
    std::string _FtpPathFileName;
    std::string _LocalPathFileName;
    
    long long _FileByteSize;
    long long _FtpDnByteSize;

public:
    FtpDnFile(const char* title, const char* szFtpPathFileName, const char* szLocalPathFileName, long long fileByteSize) :
         _Title(title)
        , _FtpPathFileName(szFtpPathFileName)
        , _LocalPathFileName(szLocalPathFileName)
        , _FileByteSize(fileByteSize)
        , _FtpDnByteSize(0)
    {
    }
};


static std::shared_ptr<NetUtils::FTPClient> s_ftp;
static std::vector<std::shared_ptr<OAL::FileSys::File>> s_vecFtpFile[(int)TESys::Property::FileSync::Ftp::DirID::MaxCount];
static std::vector< std::shared_ptr<OAL::FileSys::File>> s_vecLocalFile[(int)TESys::Property::FileSync::Ftp::DirID::MaxCount];
static std::vector<std::shared_ptr<FtpDnFile>> s_ftpDnFileVector;

std::shared_ptr<FtpDnFile> s_CurFtpDnFile;
static long long s_TotalFtpDnFileByteSize = 0;
static long long s_CurFtpDnFileByteSize = 0;
static long long s_FtpDnStartTick = 0;
static long long s_FtpDnCurTick = 0;


struct FtpGetCallbackArg {
    int boardID;
};

int FtpGetCallback(void* arg, long long readByteSize) {

    //CLOGD("redByte=%d \n", readByteSize);
    //s_LastFtpDownloadFileByteSize += readByteSize;
    struct FtpGetCallbackArg* pArg = (struct FtpGetCallbackArg*)arg;

    s_CurFtpDnFile->_FtpDnByteSize += readByteSize;
    s_CurFtpDnFileByteSize += readByteSize;
    s_FtpDnCurTick = Comm::OAL::System::GetTickCount64();

    TESys::Property::FileSync::Status::SetFtpDnCurFileDownloadingByteSize(pArg->boardID, s_CurFtpDnFile->_FtpDnByteSize);
    TESys::Property::FileSync::Status::SetFtpDnCurDownloadingByteSize(pArg->boardID, s_CurFtpDnFileByteSize);

#if (CommOS==CommOS_WIN)
    PRINTF("%lld/%lld  %lld/%lld(%lld%c) Dur(%d sec)\n", 
        s_CurFtpDnFile->_FtpDnByteSize, s_CurFtpDnFile->_FileByteSize,
        s_CurFtpDnFileByteSize, s_TotalFtpDnFileByteSize, s_CurFtpDnFileByteSize*100LL/s_TotalFtpDnFileByteSize, '%',
        (s_FtpDnCurTick- s_FtpDnStartTick) / 1000
    );
#endif

    return 0;
}

//로칼 디스크 폴더 생성
static void GenLocalDiskDir(int boardID) {

    std::string s = TESys::Property::FileSync::Ftp::LocalRootName();
    if (!Comm::OAL::FileSys::IsThisDirExist(s)) {
        Comm::OAL::FileSys::MakeDir(s);
        OAL::FileSys::ChangeOwner(s, "system");
    }

    for (int iDir = 0; iDir < (int)TESys::Property::FileSync::Ftp::DirID::MaxCount; iDir++) {
        std::string strPathName = TESys::Property::FileSync::Ftp::LocalPathName(boardID, (TESys::Property::FileSync::Ftp::DirID)iDir);
        OAL::FileSys::MakeDir(strPathName);
        OAL::FileSys::ChangeOwner(strPathName, "system");
    }
}

static bool FtpConnectAndLogIn() {
    bool bRet = false;


    bRet = s_ftp->Connect(TESys::Property::Net::GetFtpServerMachIPAddr().c_str(), TESys::Property::FileSync::Ftp::ServerTcpPort());
    if (bRet) {
        bRet = s_ftp->Login(TESys::Property::FileSync::Ftp::ServerID().c_str(), TESys::Property::FileSync::Ftp::ServerPW().c_str());
        if (!bRet) {
            CLOGI("FTP LogIn Fail : ID=%s PW=%d", TESys::Property::FileSync::Ftp::ServerID().c_str(), TESys::Property::FileSync::Ftp::ServerPW().c_str());
        }
    }
    else {
        CLOGI("FTP Connect Fail :  %s:%d", TESys::Property::Net::GetFtpServerMachIPAddr().c_str(), TESys::Property::FileSync::Ftp::ServerTcpPort());
    }
    return bRet;
}

static bool FtpDisconnect() {

    CLOGD("s_ftp->Quit");
    s_ftp->Quit();

    //CLOGD("s_ftp->Close");
    //s_ftp->Close();

    return true;
}

static void FtpDir(int boardID) {

    CLOGI("BoardID(%d) ------------------- FTP File List ---------------------------", boardID);
    for (int iDir = 0; iDir < (int)TESys::Property::FileSync::Ftp::DirID::MaxCount; iDir++) {
        std::string strPathName = TESys::Property::FileSync::Ftp::RemotePathName((TESys::Property::FileSync::Ftp::DirID)iDir);
        s_vecFtpFile[iDir] = s_ftp->Dir(strPathName, boardID);

        CLOGI("BoardID(%d) %s : fileCount=%d ", boardID, strPathName.c_str(), s_vecFtpFile[iDir].size());
        for (std::vector<std::shared_ptr<OAL::FileSys::File>>::const_iterator it = s_vecFtpFile[iDir].cbegin(); it != s_vecFtpFile[iDir].cend(); ++it) {
            std::shared_ptr<OAL::FileSys::File> file = *it;
            CLOGI("BoardID(%d) %s/%s  %d  Gmt(%s)", boardID, strPathName.c_str(), file->GetName().c_str(), file->GetByteSize(), 
                OAL::DateTime::GetUtcTimeString(file->GetLastWriteUtcTime()).c_str());
        }
    }
    CLOGI(" ");

}

static void LocalDiskDir(int boardID) {

    CLOGI("BoardID(%d) ------------------- Local File List ---------------------------", boardID);
    for (int iDir = 0; iDir < (int)TESys::Property::FileSync::Ftp::DirID::MaxCount; iDir++) {
        std::string strPathName = TESys::Property::FileSync::Ftp::LocalPathName(boardID, (TESys::Property::FileSync::Ftp::DirID)iDir);
        s_vecLocalFile[iDir] = OAL::FileSys::GetFileVector(strPathName);

        for (std::vector<std::shared_ptr<OAL::FileSys::File>>::const_iterator it = s_vecLocalFile[iDir].cbegin(); it != s_vecLocalFile[iDir].cend(); ++it) {
            std::shared_ptr<OAL::FileSys::File> file = *it;
            CLOGI("BoardID(%d) %s/%s  %d  GMT(%s)", boardID, strPathName.c_str(), file->GetName().c_str(), file->GetByteSize(), 
                        OAL::DateTime::GetUtcTimeString(file->GetLastWriteUtcTime()).c_str());
        }
    }
    CLOGI(" ");
}


static void FtpDownload(int boardID) {

    int ftpDownloadCount = 0;

    CLOGI("BoardID(%d)------------------- Check & FTP Download ---------------------------", boardID);

    for (int iDir = 0; iDir < (int)TESys::Property::FileSync::Ftp::DirID::MaxCount; iDir++) {

        std::string strLocalPathName = TESys::Property::FileSync::Ftp::LocalPathName(boardID, (TESys::Property::FileSync::Ftp::DirID)iDir);
        std::string strFtpPathName = TESys::Property::FileSync::Ftp::RemotePathName((TESys::Property::FileSync::Ftp::DirID)iDir);

        std::vector<std::shared_ptr<OAL::FileSys::File>>* pFtp = &s_vecFtpFile[iDir];
        std::vector<std::shared_ptr<OAL::FileSys::File>>* pLocal = &s_vecLocalFile[iDir];

        for (std::vector<std::shared_ptr<OAL::FileSys::File>>::const_iterator itftp = pFtp->cbegin(); itftp != pFtp->cend(); ++itftp) {

            std::shared_ptr<OAL::FileSys::File> ftpFile = *itftp;

            bool isDownload = true;  //Local파일이 없는 경우, 다운로드 수행하기 우해 true로 설정 
            bool isLocalExist = false;

            //기 다운받은 localFile이 있는 경우, 다운로드 여부 체크  
            for (std::vector<std::shared_ptr<OAL::FileSys::File>>::const_iterator itlocal = pLocal->cbegin(); itlocal != pLocal->cend(); ++itlocal) {

                std::shared_ptr<OAL::FileSys::File> localFile = *itlocal;

                if (ftpFile->GetName().compare(localFile->GetName()) == 0) {

                    isLocalExist = true;

                    if ((ftpFile->GetByteSize() == localFile->GetByteSize())
                        && (ftpFile->GetLastWriteUtcTime() < localFile->GetLastWriteUtcTime()) // Local파일이 더 Old 하다면 Download받을 필요 없다.
                        )
                    {
                        isDownload = false;
                    }

                    CLOGI("BoardID(%d) %s/%s fsz(ftp[%d] local[%d]) GMT(ftp[%s] local[%s]) isDn(%d)",
                        boardID, 
                        strFtpPathName.c_str(), ftpFile->GetName().c_str(),
                        ftpFile->GetByteSize(), localFile->GetByteSize(),
                        OAL::DateTime::GetUtcTimeString(ftpFile->GetLastWriteUtcTime()).c_str(),
                        OAL::DateTime::GetUtcTimeString(localFile->GetLastWriteUtcTime()).c_str(),
                        isDownload
                    );
                    break;
                }

            }

            if (isLocalExist == false) {
                CLOGI("%s/%s fsz(%d) GMT(%s) IsDn(%d) ",
                    strFtpPathName.c_str(), ftpFile->GetName().c_str(),
                    ftpFile->GetByteSize(),
                    OAL::DateTime::GetUtcTimeString(ftpFile->GetLastWriteUtcTime()).c_str(),
                    isDownload);
            }


            if (isDownload) {

                char* ftpFileName = new char[1024 * 8];
                char* localFileName = new char[1024 * 8];
                assert(ftpFileName);
                assert(localFileName);


                sprintf(ftpFileName, "%s/%s", strFtpPathName.c_str(), ftpFile->GetName().c_str());
                sprintf(localFileName, "%s%c%s", strLocalPathName.c_str(), Comm::Property::Path::GetFilePathDelimChar(), ftpFile->GetName().c_str());

                //CLOGI("FTP Get ..... %s ", ftpFileName);
                //s_ftp->Get(ftpFileName, localFileName, FtpGetCallback);
                    
                std::shared_ptr<FtpDnFile> ftpDnFile = std::make_shared<FtpDnFile>(ftpFile->GetName().c_str(), ftpFileName, localFileName, ftpFile->GetByteSize());
                assert(ftpDnFile);
                s_ftpDnFileVector.push_back(ftpDnFile);

                delete[] ftpFileName;
                delete[] localFileName;

                ftpDownloadCount++;
            }

        }
    }

    //다운로드해야 할 전체 파일 크기 계산 
    for (std::vector<std::shared_ptr<FtpDnFile>>::const_iterator it = s_ftpDnFileVector.cbegin();
        it != s_ftpDnFileVector.cend();
        it++) {
    
        std::shared_ptr<FtpDnFile> ftpDnFile = *it;
        s_TotalFtpDnFileByteSize += ftpDnFile->_FileByteSize;
    }
    TESys::Property::FileSync::Status::SetFtpDnTotalByteSize(boardID, s_TotalFtpDnFileByteSize);

    if (s_TotalFtpDnFileByteSize > 0) {


        //FTP Download 시작
        int ftpDnNo = 1;
        FtpGetCallbackArg ftpCbArg;

        ftpCbArg.boardID = boardID;

        s_FtpDnStartTick = Comm::OAL::System::GetTickCount64();

        for (std::vector<std::shared_ptr<FtpDnFile>>::const_iterator it = s_ftpDnFileVector.cbegin();
            it != s_ftpDnFileVector.cend();
            it++) {

            s_CurFtpDnFile = *it;

            CLOGI("%d. FTP Get %s", ftpDnNo, s_CurFtpDnFile->_FtpPathFileName.c_str());
            CLOGI("\t\t===> %s", s_CurFtpDnFile->_LocalPathFileName.c_str());
            CLOGI("");

            TESys::Property::FileSync::Status::SetFtpDnCurFileName(boardID, s_CurFtpDnFile->_Title);
            TESys::Property::FileSync::Status::SetFtpDnCurFileByteSize(boardID, s_CurFtpDnFile->_FileByteSize);
            TESys::Property::FileSync::Status::SetFtpDnCurFileDownloadingByteSize(boardID, 0);

            s_ftp->Get(s_CurFtpDnFile->_FtpPathFileName.c_str(), s_CurFtpDnFile->_LocalPathFileName.c_str(), (void*)&ftpCbArg, FtpGetCallback);

            ftpDnNo++;

            //파일 소유권을 'system' 으로 변경 
            Comm::OAL::FileSys::ChangeOwner(s_CurFtpDnFile->_LocalPathFileName, "system");
            Comm::OAL::FileSys::ChangeMode(s_CurFtpDnFile->_LocalPathFileName, "666");

        }

    }


    CLOGI("Download File Count : %d", ftpDownloadCount);
    CLOGI("");
}

static void LocalDiskFileDelete(int boardID) {
        
    int delFileCount = 0;
    char* fileName = new char[1024 *8];
    assert(fileName);

    CLOGI("BoardID(%d) ------------------- Chek & Local File Delete ---------------------------", boardID);
    for (int iDir = 0; iDir < (int)TESys::Property::FileSync::Ftp::DirID::MaxCount; iDir++) {

        std::string strLocalPathName = TESys::Property::FileSync::Ftp::LocalPathName(boardID, (TESys::Property::FileSync::Ftp::DirID)iDir);
        std::string strFtpPathName = TESys::Property::FileSync::Ftp::RemotePathName((TESys::Property::FileSync::Ftp::DirID)iDir);

        std::vector<std::shared_ptr<OAL::FileSys::File>>* pFtp = &s_vecFtpFile[iDir];
        std::vector<std::shared_ptr<OAL::FileSys::File>>* pLocal = &s_vecLocalFile[iDir];

        for (std::vector<std::shared_ptr<OAL::FileSys::File>>::const_iterator itlocal = pLocal->cbegin(); itlocal != pLocal->cend(); ++itlocal) {

            std::shared_ptr<OAL::FileSys::File> localFile = *itlocal;
            
            bool isFtpFileExist = false;

            //주어진 로칼파일과 같은 이름의 파일이  FTP폴더에 있는지 확인 
            for (std::vector<std::shared_ptr<OAL::FileSys::File>>::const_iterator itftp = pFtp->cbegin(); itftp != pFtp->cend(); ++itftp) {

                std::shared_ptr<OAL::FileSys::File> ftpFile = *itftp;
                if (ftpFile->GetName().compare(localFile->GetName()) == 0) {
                    isFtpFileExist = true;
                    break;
                }
            }

            //이 Local파일은 FTP목록에 없다.  지워야 한다. 
            if (isFtpFileExist == false) {

                sprintf(fileName, "%s%c%s", strLocalPathName.c_str(), Comm::Property::Path::GetFilePathDelimChar(), localFile->GetName().c_str());
                bool bDelRes = OAL::FileSys::RemoveFile(fileName);
                if (bDelRes) {
                    delFileCount++;
                }

                CLOGI("Delete %s fsz(%d) GMT(%s) ... %s",
                    fileName,
                    localFile->GetByteSize(),
                    OAL::DateTime::GetUtcTimeString(localFile->GetLastWriteUtcTime()).c_str(),
                    bDelRes ?"OK":"Fail"
                   );
            }

        }

    }
    delete[] fileName;
    CLOGI("Delete File Count : %d", delFileCount);
    CLOGI("");
}

static long long s_TotalLocaFileByteSize = 0;
static long long s_CurCheckDoneByteSize = 0;

static void LocalDiskCalCRC_CheckDone_Callback(void* arg,
                                                std::shared_ptr<Comm::OAL::FileSys::File> /*file*/,
                                                int /*crc*/,   // 현재 CRC값 
                                                long long checkDoneByteSize, //현재 CRC값을 계산하는데 사용한 byte
                                                long long /*checkDoneFileByteSize*/ //현재 파일에서 체크 완료한 File ByteSize
                                               ) 
{
    int boardID = *((int*)arg);

    s_CurCheckDoneByteSize += checkDoneByteSize;
    TESys::Property::FileSync::Status::SetLocalCurCalculatedCRCByteSize(boardID, s_CurCheckDoneByteSize);
}

static void LocalDiskCalCRC(int boardID) {

    CLOGI("--------------- Cal All File CRC,  BoardID(%d) ---------------------------", boardID);
    int crc = 0;
    int crcSum = 0;

    const int crcBufMaxByteSize = 1024 * 512;
    unsigned char* crcBuf = new unsigned char[crcBufMaxByteSize];
    assert(crcBuf);

    //전체 파일 크기 계산 
    for (int iDir = 0; iDir < (int)TESys::Property::FileSync::Ftp::DirID::MaxCount; iDir++) {
        std::string strPathName = TESys::Property::FileSync::Ftp::LocalPathName(boardID, (TESys::Property::FileSync::Ftp::DirID)iDir);
        std::vector<std::shared_ptr<OAL::FileSys::File>> fileVector = OAL::FileSys::GetFileVector(strPathName);
        for (std::vector<std::shared_ptr<OAL::FileSys::File>>::const_iterator it = fileVector.cbegin(); it != fileVector.cend(); ++it) {
            std::shared_ptr<OAL::FileSys::File> file = *it;
            s_TotalLocaFileByteSize += file->GetByteSize();
        }
    }
    TESys::Property::FileSync::Status::SetLocalTotalFileByteSize(boardID, s_TotalLocaFileByteSize);
    TESys::Property::FileSync::Status::SetLocalLatestCRC(boardID, crcSum);

    //CRC 계산
    for (int iDir = 0; iDir < (int)TESys::Property::FileSync::Ftp::DirID::MaxCount; iDir++) {
        std::string strPathName = TESys::Property::FileSync::Ftp::LocalPathName(boardID, (TESys::Property::FileSync::Ftp::DirID)iDir);
        std::vector<std::shared_ptr<OAL::FileSys::File>> fileVector = OAL::FileSys::GetFileVector(strPathName);

        for (std::vector<std::shared_ptr<OAL::FileSys::File>>::const_iterator it = fileVector.cbegin(); it != fileVector.cend(); ++it) {
            std::shared_ptr<OAL::FileSys::File> file = *it;

            crc = Comm::Utils::CRC16(file, 0 /*crc*/, crcBuf, crcBufMaxByteSize, (void*)&boardID, LocalDiskCalCRC_CheckDone_Callback);
            crcSum += crc;
            CLOGI("BoardID=%d crc=%d crcSum=%d File=%s Size=%d", boardID, crc, crcSum, file->GetName().c_str(), file->GetByteSize());
            TESys::Property::FileSync::Status::SetLocalLatestCRC(boardID, crcSum);
        }
    }

    TESys::Property::FileSync::Status::SetLocalLatestCRC(boardID, crcSum);
    CLOGI("BoardID=%d CRC-SUM=%d ", boardID, crcSum);

    delete[] crcBuf;
}

int main(int argc, char* argv[]) {

    int iloop;
    bool bRet;
    int boardID = TESys::Property::Tester::Board::GetID();

    if (argc == 2) {
        boardID = atoi(argv[1]);
    }

    if (boardID < 0) {
        PRINTF("ERROR: boardID is not defined!! \n");
        return -1;
    }

    PRINTF("BoardID=%d \n", boardID);

    OAL::Log::SysLogOpen(CLOG_TAG);
    OAL::Log::EnableOutDevice(OAL::Log::OutDevice::Console);
    OAL::Log::EnableDebug();

    s_ftp = NetUtils::FTPClient::CreateObject();
    assert(s_ftp);

    TESys::Property::FileSync::Status::SetAppStatus(boardID, TESys::Property::FileSync::Status::AppStatus::FileSyncAppBegin);


    //로칼 디스크 폴더 생성
    GenLocalDiskDir(boardID);

    //FTP접속 및 로그인 
    TESys::Property::FileSync::Status::SetAppStatus(boardID, TESys::Property::FileSync::Status::AppStatus::FtpConnectAndLogIn);
    for (iloop = 0; iloop < 10; iloop++) {
        bRet = FtpConnectAndLogIn();
        if (bRet) {
            break;
        }
        else {
            Comm::OAL::Thread::Sleep(1000);
        }
    }
    if (iloop == 10) {
        return -1;
    }

#if 1

    //FTPServer 폴더별 디렉토리 목록 
    TESys::Property::FileSync::Status::SetAppStatus(boardID, TESys::Property::FileSync::Status::AppStatus::FtpDir);
    FtpDir(boardID);
    
    //LocalDisk 폴더별 디렉토리 목록 
    TESys::Property::FileSync::Status::SetAppStatus(boardID, TESys::Property::FileSync::Status::AppStatus::LocalDiskDir);
    LocalDiskDir(boardID);
    
    //FTP서버에 존재하지 않는 Local파일은 삭제한다.
    TESys::Property::FileSync::Status::SetAppStatus(boardID, TESys::Property::FileSync::Status::AppStatus::LocalDiskFileDelete);
    LocalDiskFileDelete(boardID);

#if 1
    //FTP서버와 LocalDisk폴더 목록 비교 
    TESys::Property::FileSync::Status::SetAppStatus(boardID, TESys::Property::FileSync::Status::AppStatus::FtpDownload);
    FtpDownload(boardID);
#endif


#endif

    //접속 종료
    TESys::Property::FileSync::Status::SetAppStatus(boardID, TESys::Property::FileSync::Status::AppStatus::FtpDisconnect);
    FtpDisconnect();
        
    //LocalDisck Cal CRC
    TESys::Property::FileSync::Status::SetAppStatus(boardID, TESys::Property::FileSync::Status::AppStatus::LocalDiskCalCRC);
    LocalDiskCalCRC(boardID);
        
    OAL::Log::SysLogClose();
    CLOGD("Bye Bye~~");

    TESys::Property::FileSync::Status::SetAppStatus(boardID, TESys::Property::FileSync::Status::AppStatus::FileSyncAppEnd);

    return 0;
}

