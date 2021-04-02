#include <Comm/Global/BuildOptions.h>
#include <Comm/Property/System.hpp>

namespace Comm {
    
    namespace Property {

        namespace System {

            const char* Get_OS_Name(int osId) {

                const char* osName = "";
                switch (osId) {

                case CommOS_WIN:  osName = "Win"; break;
                case CommOS_LINUX:  osName = "Linux"; break;
                case CommOS_ANDROID:  osName = "Android"; break;
                }

                return osName;
            }

            int Get_OS_ID() {
                return CommOS;
            }

            
        };

    }; //namespace Net {
}; // namespace Comm {


