#include <Comm/Global/BuildOptions.h>
#include <Comm/Property/Path.hpp>

namespace Comm {
    namespace Property {

        namespace Path {

            std::string GetTmpRoot()  //휘발성 데이타 저장소 
            {
                #if (CommOS==CommOS_ANDROID)
                    return "/tmp";
                #elif (CommOS==CommOS_LINUX)
                    return  "/opt/TESys/tmp";
                #elif (CommOS==CommOS_WIN)
                    return "C:\\Temp";
                #else
                #error "Select OS"
                #endif  
            }

#if (CommOS==CommOS_WIN)
#define FILE_PATH_DELIM_CHAR   '\\'
#define FILE_PATH_DELIM_STRING "\\"
#else
#define FILE_PATH_DELIM_CHAR   '/'
#define FILE_PATH_DELIM_STRING "/"
#endif

            char GetFilePathDelimChar() {
                return FILE_PATH_DELIM_CHAR;
            }

            std::string GetFilePathDelimString() {
                return FILE_PATH_DELIM_STRING;
            }
        };
        

    }; //namespace Net {
}; // namespace Comm {


