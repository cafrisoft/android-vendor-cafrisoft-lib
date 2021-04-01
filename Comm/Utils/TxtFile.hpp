#ifndef COMM_UTILS_TXTFILE_HPP__
#define COMM_UTILS_TXTFILE_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/OAL/CriticalSection.hpp>

namespace Comm {
    namespace Utils {
        namespace TxtFile {

            std::vector<std::string> ReadLineString(std::string strFileName);
            bool WriteInt(std::string strFileName, int value);
            int ReadInt(std::string strFileName, /*OUT*/int *err = NULL);
            int ReadInt(std::string strFileName, const char* propName, char delim, /*OUT*/int* err = NULL);
        
            bool ReverseTopBottom(std::string strFileName);
            bool ReverseTopBottom(std::string strFileNameFrom, std::string strFileNameTo);

        }; //namespace TxtFile
    }; //namespace Utils
}; //namespace Comm

#endif

