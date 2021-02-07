#include <Comm/OAL/FileSys.hpp>
#include <Comm/OAL/DateTime.hpp>
#include <Comm/Utils/StringTool.hpp>
#include <Comm/Property/Path.hpp>

namespace Comm {
    namespace OAL {

        FileSys::File::File(std::string strPath, std::string strFile,
            time_t lastAccessGmtTime,
            time_t lastWriteGmtTime,
            long long fileByteSize) :
        
             _LastAccessGmtTime(lastAccessGmtTime)
            , _LastWriteGmtTime(lastWriteGmtTime)
            , _ByteSize(fileByteSize)
            ,_Path(strPath)
            ,_Name(strFile)
            
        {
        
        
        }

        std::string FileSys::File::GetPath() {
            return _Path;
        }

        std::string FileSys::File::GetName() {
        
            return _Name;
        }

        std::string FileSys::File::GetPathFileName() {
        
            std::string strPathFile = _Path;
            strPathFile += Comm::Property::Path::GetFilePathDelimChar();
            strPathFile += _Name;
            return strPathFile;
        }
        
        long long FileSys::File::GetByteSize() {
            return _ByteSize;
        }

        time_t FileSys::File::GetLastAccessUtcTime() {
            return _LastAccessGmtTime;
        }

        time_t FileSys::File::GetLastWriteUtcTime() {
            return _LastWriteGmtTime;
        }

        bool FileSys::RemoveFile(std::string strFileName) {

            int iret;
            bool bRet = false;

            iret = remove(strFileName.c_str());
            if (iret == 0) {
                bRet = true;
            }
            return bRet;
        }

        

    }; //end of namespace OAL
}; //end of namespace Comm


