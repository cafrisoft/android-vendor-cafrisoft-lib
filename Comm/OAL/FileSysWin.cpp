#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/FileSys.hpp>
#include <Comm/OAL/DateTime.hpp>
#include <Comm/Utils/StringTool.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
    namespace OAL {

        bool FileSys::IsThisDirExist(std::string dirName) {
        
            struct _stat64i32 stat;
            bool bRet = false;

            if (_stat(dirName.c_str(), &stat) == 0) {
                
                if (stat.st_mode & _S_IFDIR) {
                    bRet = true;
                }
            }

            return bRet;
        }
         
        bool FileSys::IsThisFileExist(std::string fileName) {

            struct _stat64i32 stat;
            bool bRet = false;

            if (_stat(fileName.c_str(), &stat) == 0) {

                if (stat.st_mode & _S_IFREG) {
                    bRet = true;
                }
            }

            return bRet;
        }

        bool FileSys::MakeDir(std::string dirName) {
            //_mkdir(dirName);
            char buf[256];
            sprintf(buf, "md %s", dirName.c_str());
            system(buf);
            return true;
        }

        bool FileSys::ChangeOwner(std::string dirName, std::string ownerName) {
        
            return true;
        }

        bool FileSys::ChangeMode(std::string dirName, std::string modeName) {
        
            return true;
        }
                
#if 0
        time_t FileSys::Convert_FILETIME_To_time_t(FILETIME ft) {
        
            long long unixTime;
            const long long SECS_BETWEEN_EPOCHS = 11644473600;
            const long long SECS_TO_100NS = 10000000; // 10^7 

            assert(sizeof(time_t) == sizeof(long long));

            /* get th full win32 value, in 100ns */
            unixTime = ((long long)ft.dwHighDateTime << 32) & 0xFFFFFFFF00000000;
            unixTime |= (long long)ft.dwHighDateTime & UINT_MAX;

            /* Convert to the Unix epoch */
            unixTime -= SECS_BETWEEN_EPOCHS * SECS_TO_100NS;

            unixTime /= SECS_TO_100NS;  /* now convert to seconds */

            return (time_t)unixTime;
        }
#else

        time_t FileSys::Convert_FILETIME_To_time_t(FILETIME ft) {

            /* NTFS File System은  UTC로 시간이 저장된다. */

            SYSTEMTIME syst;
            ::FileTimeToSystemTime(&ft, &syst);
            
            return (time_t)DateTime::GetUtcTime(syst.wYear, syst.wMonth, syst.wDay, syst.wHour, syst.wMinute, syst.wSecond);
        }

#endif

        std::vector<std::shared_ptr<FileSys::File>> FileSys::GetFileVector(std::string strDirName) {
        
            std::vector<std::shared_ptr<FileSys::File>> vecFile;

            HANDLE hList;
            WIN32_FIND_DATA FileData;

            char* szPath = new char[1024 * 8];
            assert(szPath);

            strcpy(szPath, strDirName.c_str());
            Utils::StringTool::RemoveCharInStringFromBack(szPath, " \n\r\\");
            strcat(szPath, "\\*");

            //hList = ::FindFirstFile((LPCSTR)dirName, &FileData);
            hList = ::FindFirstFile((LPCSTR)szPath, &FileData);
            if (hList != INVALID_HANDLE_VALUE) {

                do {
                    if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        /* Nothing to do */
                    }
                    else {

                        long long byteSize;
                        std::shared_ptr<FileSys::File> f;

                        byteSize = ((long long)FileData.nFileSizeHigh << 32) & 0xFFFFFFFF00000000;
                        byteSize |= (long long)FileData.nFileSizeLow & 0xFFFFFFFF;

                        f = std::make_shared<FileSys::File>(strDirName,
                            FileData.cFileName,
                            FileSys::Convert_FILETIME_To_time_t(FileData.ftLastAccessTime),
                            FileSys::Convert_FILETIME_To_time_t(FileData.ftLastWriteTime),
                            byteSize);

#if 0
                        f.Path = strDirName;
                        f.Name = FileData.cFileName;
                        f.ByteSize = ((long long)FileData.nFileSizeHigh << 32) & 0xFFFFFFFF00000000;
                        f.ByteSize |= (long long)FileData.nFileSizeLow & 0xFFFFFFFF;
                        f.LastAccessGmtTime = FileSys::Convert_FILETIME_To_time_t(FileData.ftLastAccessTime);
                        f.LastWriteGmtTime = FileSys::Convert_FILETIME_To_time_t(FileData.ftLastWriteTime);
#endif

                        vecFile.push_back(f);
                    }

                } while (::FindNextFile(hList, &FileData) == TRUE);
            }

            ::FindClose(hList);

            delete[] szPath;

            return vecFile;
        }


        bool FileSys::RenameFile(std::string oldFileName, std::string newFileName) // ÆAAIAI¸§ ¹U²U±a 
        {
            return ::MoveFile(oldFileName.c_str(), newFileName.c_str());
        }

    }; //end of namespace OAL
}; //end of namespace Comm

#endif //#if (CommOS==CommOS_LINUX)
