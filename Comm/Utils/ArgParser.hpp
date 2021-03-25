#ifndef COMM_UTILS_ARGPARSER_HPP__
#define COMM_UTILS_ARGPARSER_HPP__

#include <Comm/Base/Object.hpp>

namespace Comm {
    namespace Utils {
        namespace ArgParser {

            bool GetValue(int argc, const char** argv, const char* parName, bool* retValue,  bool defaultValue);
            bool GetValue(int argc, const char** argv, int* retInt0, const char* parName);
        
            

        }; //namespace ArgParser
    };//namespace Utils
};//namespace Comm

#endif
