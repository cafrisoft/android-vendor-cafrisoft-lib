#define CLOG_TAG "TESysHubCalCRC"
#include <TESys/Property/FileSync.hpp>
#include <TESys/Property/Hub.hpp>

using namespace Comm;
using namespace TESys;

static long long s_TotalLocaFileByteSize = 0;
static long long s_CurCheckDoneByteSize = 0;

static void FtpStorageCalCRC_CheckDone_Callback(void* arg,
    std::shared_ptr<Comm::OAL::FileSys::File> file,
    int crc,   // 현재 CRC값 
    long long checkDoneByteSize, //현재 CRC값을 계산하는데 사용한 byte
    long long checkDoneFileByteSize //현재 파일에서 체크 완료한 File ByteSize
)
{
    s_CurCheckDoneByteSize += checkDoneByteSize;
    TESys::Property::Hub::FtpServer::SetFtpStorageCurCalculatedCRCByteSize(s_CurCheckDoneByteSize);
}

int main(int argc, char* argv[]) {

    int crc = 0;
    int crcSum = 0;

    Comm::OAL::Log::SysLogOpen(CLOG_TAG);
    Comm::OAL::Log::EnableOutDevice(Comm::OAL::Log::OutDevice::Console);
    Comm::OAL::Log::EnableOutDevice(Comm::OAL::Log::OutDevice::Syslog);

    TESys::Property::Hub::FtpServer::SetHubCalCRCAppStatus(TESys::Property::Hub::FtpServer::HubCalCRCAppStatus::Begin);

    const int crcBufMaxByteSize = 1024 * 512;
    unsigned char* crcBuf = new unsigned char[crcBufMaxByteSize];
    assert(crcBuf);

    TESys::Property::Hub::FtpServer::SetHubCalCRCAppStatus(TESys::Property::Hub::FtpServer::HubCalCRCAppStatus::CalFileSize);
    //전체 파일 크기 계산 
    for (int dirID = 0; dirID < (int)TESys::Property::FileSync::Ftp::DirID::MaxCount; dirID++) {
        
        std::string strFtpStoragePathName = TESys::Property::FileSync::Ftp::FtpStoragePathName((TESys::Property::FileSync::Ftp::DirID)dirID);
        std::vector<std::shared_ptr<OAL::FileSys::File>> fileVector = OAL::FileSys::GetFileVector(strFtpStoragePathName);

        for (std::vector< std::shared_ptr<OAL::FileSys::File>>::const_iterator it = fileVector.cbegin(); it != fileVector.cend(); ++it) {
            std::shared_ptr<OAL::FileSys::File> file = *it;
            s_TotalLocaFileByteSize += file->GetByteSize();
        }
    }
    TESys::Property::Hub::FtpServer::SetFtpStorageTotalFileByteSize(s_TotalLocaFileByteSize);
    
    CLOGI("s_TotalLocaFileByteSize=%d", s_TotalLocaFileByteSize);

    //CRC 계산 
    TESys::Property::Hub::FtpServer::SetFtpStorageLatestCRC(999999); /* FileSync시작시, Board의 FileSync초기값과 다르게 하기위해 999999를 설정*/
    TESys::Property::Hub::FtpServer::SetHubCalCRCAppStatus(TESys::Property::Hub::FtpServer::HubCalCRCAppStatus::CalCRC);
    for (int dirID = 0; dirID < (int)TESys::Property::FileSync::Ftp::DirID::MaxCount; dirID++) {

        std::string strFtpStoragePathName = TESys::Property::FileSync::Ftp::FtpStoragePathName((TESys::Property::FileSync::Ftp::DirID)dirID);
        std::vector<std::shared_ptr<OAL::FileSys::File>> fileVector = OAL::FileSys::GetFileVector(strFtpStoragePathName);

        for (std::vector< std::shared_ptr<OAL::FileSys::File>>::const_iterator it = fileVector.cbegin(); it != fileVector.cend(); ++it) {
            std::shared_ptr<OAL::FileSys::File> file = *it;
            
            crc = Comm::Utils::CRC16(file, 0/*crc*/, crcBuf, crcBufMaxByteSize, NULL, FtpStorageCalCRC_CheckDone_Callback);
            crcSum += crc;
            TESys::Property::Hub::FtpServer::SetFtpStorageLatestCRC(crcSum);
            CLOGI("crc=%d crcSum=%d file=%s", crc, crcSum, file->GetPathFileName().c_str());
        }
    }
    TESys::Property::Hub::FtpServer::SetFtpStorageLatestCRC(crcSum);

    delete[] crcBuf;

    TESys::Property::Hub::FtpServer::SetHubCalCRCAppStatus(TESys::Property::Hub::FtpServer::HubCalCRCAppStatus::End);

    CLOGI("CRC-SUM=%d\n", crcSum);

    Comm::OAL::Log::SysLogClose();
    return 0;
}