#ifndef COMM_NETUTILS_FTPClient_HPP__
#define COMM_NETUTILS_FTPClient_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/OAL/FileSys.hpp>
#include <Comm/NetUtils/FTPDefine.h>

namespace Comm {
    namespace NetUtils {

        class FTPClient : public Base::Object {
        
        public:
            static std::shared_ptr<FTPClient> CreateObject();

        protected:
            FTPClient();
            virtual ~FTPClient();

        public:
            virtual bool Connect(const char* serverIPAddr, int portNum) = 0;
            virtual bool Login(const char* id, const char* pw) = 0;
            virtual bool Quit() = 0;
            virtual bool Close() = 0;

            //virtual bool Dir(const char* dir, /*OUT*/ char* dirRespBuf, int bufMaxByteSize) = 0;
            virtual std::vector<std::shared_ptr<Comm::OAL::FileSys::File>> Dir(std::string dir, int appID) = 0;

            virtual bool Get(std::string strFtpFileName, std::string strLocalFileName, void* cbArg=NULL, Comm_NetUtils_FtpGetCallback cbfunc=NULL) = 0;
        };


    }; //namespace Socket {
}; // namespace Comm {

#endif //COMM_DATAEX_PRODUCER_HPP__
