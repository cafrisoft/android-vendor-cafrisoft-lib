#include <Comm/Socket/Utils.hpp>

namespace Comm {
    namespace Socket {
        namespace Utils {

            std::string ConvetIPAddrI32ToString(unsigned int ipAddrI32) {
            
                std::string strIP;
                struct sockaddr_in addr;
                addr.sin_addr.s_addr = ipAddrI32;

                strIP = inet_ntoa(addr.sin_addr);

                return strIP;
            }

        };
    }; //namespace Socket {
}; // namespace Comm {


