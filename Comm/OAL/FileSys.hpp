#ifndef COMM_OAL_FILESYSTEM_HPP__
#define COMM_OAL_FILESYSTEM_HPP__

#include <Comm/Base/Object.hpp>

namespace Comm {
    namespace OAL {

        class FileSys : public Base::Object {

        public:
            class File {
            private: 
                time_t _LastAccessGmtTime;
                time_t _LastWriteGmtTime;
                long long _ByteSize;
                std::string _Path;
                std::string _Name;

            public:
                File(std::string strPath, std::string strFile,
                    time_t lastAccessGmtTime,
                    time_t lastWriteGmtTime,
                    long long fileByteSize);

                std::string GetPath();
                std::string GetName();
                std::string GetPathFileName();
                long long GetByteSize();
                time_t GetLastAccessUtcTime();
                time_t GetLastWriteUtcTime();
            };

        public:
            static bool MakeDir(std::string dirName);
            static bool ChangeOwner(std::string dirName, std::string ownerName);
            static bool ChangeMode(std::string dirName, std::string modeName);
            static std::vector<std::shared_ptr<File>> GetFileVector(std::string strDirName);
            static bool IsThisDirExist(std::string dirName);
            static bool IsThisFileExist(std::string fileNamedirName);
            static bool RemoveFile(std::string  strFileName);
            static bool RenameFile(std::string oldFileName, std::string newFileName); // ¨¡AAIAI¢¬¡× ©öU©÷U¡¾a 

#if (CommOS==CommOS_WIN)
            static time_t Convert_FILETIME_To_time_t(FILETIME ft);
#endif
        };


    }; //end of namespace Net
}; //end of namespace Comm

#endif // #ifndef TESYSNETCLIENT_HPP

