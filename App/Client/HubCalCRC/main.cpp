#define CLOG_TAG "TESysHubCalCRC"
#include <TESys/Property/FileSync.hpp>
#include <TESys/Property/Hub.hpp>

using namespace Comm;
using namespace TESys;

static long long s_TotalLocaFileByteSize = 0;
static long long s_CurCheckDoneByteSize = 0;

static void FtpStorageCalCRC_CheckDone_Callback(void* arg,
    std::shared_ptr<Comm::OAL::FileSys::File> file,
    int crc,   // ���� CRC�� 
    long long checkDoneByteSize, //���� CRC���� ����ϴµ� ����� byte
    long long checkDoneFileByteSize //���� ���Ͽ��� üũ �Ϸ��� File ByteSize
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
    //��ü ���� ũ�� ��� 
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

    //CRC ��� 
    TESys::Property::Hub::FtpServer::SetFtpStorageLatestCRC(999999); /* FileSync���۽�, Board�� FileSync�ʱⰪ�� �ٸ��� �ϱ����� 999999�� ����*/
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