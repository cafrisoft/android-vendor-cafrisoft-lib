#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/FileSys.hpp>
#include <Comm/Utils/StringTool.hpp>
#include <Comm/OAL/Log.hpp>

#if (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)

#include <sys/stat.h>

namespace Comm {
    namespace OAL {

        bool FileSys::MakeDir(std::string dirName) {
            //_mkdir(dirName);
            char buf[256];
            sprintf(buf, "mkdir -p %s", dirName.c_str());
            system(buf);
            return true;
        }

        bool FileSys::ChangeOwner(std::string dirName, std::string ownerName) {
            
#if (CommOS == CommOS_ANDROID)
            char buf[256];
            sprintf(buf, "chown %s:%s %s", ownerName.c_str(), ownerName.c_str(), dirName.c_str());
            system(buf);

            //PRINTF("---------------------------- buf : %s \n", buf);
#endif

            return true;
        }

        bool FileSys::ChangeMode(std::string dirName, std::string modeName) {

#if (CommOS == CommOS_ANDROID)
            char buf[256];
            sprintf(buf, "chmod %s %s", modeName.c_str(), dirName.c_str());
            system(buf);

            //PRINTF("---------------------------- buf : %s \n", buf);
#endif
            return true;
        }

        bool FileSys::IsThisFileExist(std::string fileName) {

            struct stat st;
            bool bRet = false;

            if (stat(fileName.c_str(), &st) == 0) {

                if (st.st_mode & S_IFREG) {
                    bRet = true;
                }
            }

            return bRet;
        }

        bool FileSys::IsThisDirExist(std::string dirName) {

            struct stat st;
            bool bRet = false;

            if (stat(dirName.c_str(), &st) == 0) {

                if (st.st_mode & S_IFDIR) {
                    bRet = true;
                }
            }

            return bRet;
        }



        std::vector<std::shared_ptr<FileSys::File>> FileSys::GetFileVector(std::string strDirName) {

            std::vector<std::shared_ptr<FileSys::File>> vecFile;

            DIR* dir;
            struct dirent* p_file;

            char* szPath = new char[1024 * 8];
            char* szFileName = new char[1024 * 8];
            assert(szPath);
            assert(szFileName);

            strcpy(szPath, strDirName.c_str());
            Utils::StringTool::RemoveCharInStringFromBack(szPath);
                        
            dir = ::opendir(szPath);
            if (dir != NULL) {

                p_file = readdir(dir);
                while(p_file) {

                    struct stat st;

                    sprintf(szFileName, "%s/%s", szPath, p_file->d_name);
                    stat(szFileName, &st);

                    if (st.st_mode & S_IFDIR) {
                        /* Nothing to do */
                    }
                    else {

                        //FileSys::File f;

                        //f.Path = strDirName;
                        //f.Name = p_file->d_name;
                        //f.ByteSize = st.st_size;

                        struct tm tmLastAccessTime;
                        struct tm tmLastWriteTime;
                        gmtime_r(&st.st_atim.tv_sec, &tmLastAccessTime);
                        //f.LastAccessGmtTime = mktime(&tm); 

                        gmtime_r(&st.st_mtim.tv_sec, &tmLastWriteTime);
                        //f.LastWriteGmtTime = mktime(&tm);

                        std::shared_ptr<FileSys::File>  file = std::make_shared<FileSys::File>(strDirName,
                            p_file->d_name,
                            mktime(&tmLastAccessTime),
                            mktime(&tmLastWriteTime),
                            st.st_size);

                        vecFile.push_back(file);
                    }

                    p_file = readdir(dir);
                }
            }

            delete[] szPath;
            delete[] szFileName;

            return vecFile;
        }

        bool FileSys::RenameFile(std::string oldFileName, std::string newFileName) // ¨¡AAIAI¢¬¡× ©öU©÷U¡¾a 
        {
            //return ::MoveFile(oldFileName.c_str(), newFileName.c_str());
            ::rename(oldFileName.c_str(), newFileName.c_str());

            return true;
        }

    }; //end of namespace OAL
}; //end of namespace Comm

#endif //#if (CommOS==CommOS_LINUX)
