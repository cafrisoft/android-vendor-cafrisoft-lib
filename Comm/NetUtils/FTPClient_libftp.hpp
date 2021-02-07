#ifndef COMM_NETUTILS_FTPClient_libftp_HPP__
#define COMM_NETUTILS_FTPClient_libftp_HPP__

#include <Comm/NetUtils/FTPClient.hpp>
#include <Comm/OpenSource/ftplib-4.0-1/src/ftplib.h>

namespace Comm {
    namespace NetUtils {

        class FTPClient_libftp : public FTPClient {

        private:
            netbuf* _NetBuf;

        public:
            FTPClient_libftp();
            virtual ~FTPClient_libftp();

        public:
            virtual bool Connect(const char* serverIPAddr, int portNum);
            virtual bool Login(const char* id, const char* pw);
            virtual bool Quit();
            virtual bool Close();

            //virtual bool Dir(const char* dir, /*OUT*/ char* dirRespBuf, int bufMaxByteSize);
            virtual std::vector<std::shared_ptr<Comm::OAL::FileSys::File>> Dir(std::string dir, int appID);
            virtual bool Get(std::string strFtpFileName, std::string strLocalFileName, void* cbArg = NULL, Comm_NetUtils_FtpGetCallback cbfunc = NULL);
        };


    }; //namespace Socket {
}; // namespace Comm {

#endif //COMM_DATAEX_PRODUCER_HPP__
