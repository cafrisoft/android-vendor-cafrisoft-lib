#include <Comm/Global/BuildOptions.h>
#include <Comm/Utils/Convert.hpp>

namespace Comm {
    namespace Utils {
        namespace Convert {

            long long Int2ToLongLong(int v0, int v1) {
            
                long long llv0 = (long long)v0 & 0xFFFFFFFF;
                long long llv1 = (long long)v1 & 0xFFFFFFFF;
            
                return ((llv0 << 32) | llv1);
            }


        }; //namespace Convert
    }; //namespace Utils
}; //namespace Comm


