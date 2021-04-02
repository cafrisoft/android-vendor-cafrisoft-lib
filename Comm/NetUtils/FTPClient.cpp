#include <Comm/Global/BuildOptions.h>
#include <Comm/NetUtils/FTPClient.hpp>
#include <Comm/NetUtils/FTPClient_libftp.hpp>

namespace Comm {
    namespace NetUtils {

        std::shared_ptr<FTPClient> FTPClient::CreateObject() {
            
            std::shared_ptr<FTPClient> obj;
            obj = std::make_shared<FTPClient_libftp>();
            assert(obj);
            return obj;
        }

        FTPClient::FTPClient() {

        }

        FTPClient::~FTPClient() {

        }

        

    }; //namespace Socket {
}; // namespace Comm {

