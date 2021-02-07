#include <Comm/OAL/LogLinux.hpp>

#if (CommOS==CommOS_LINUX)

namespace Comm {
    namespace OAL {

        LogLinux::LogLinux() : Log(true /*isOutDevConsole*/, true /*isOutDevSyslog*/, false /*isDebug*/) {

        }

        void LogLinux::__SysLogOpen(const char* logTag) {

            setlogmask(LOG_UPTO(LOG_INFO | LOG_ERR | LOG_DEBUG));
            openlog(logTag, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
        }

        void LogLinux::__SysLogClose() {
            closelog();
        }


        void Log::Printf(const char* lpszFormat, ...) {
        
            va_list args;
            char* szBuffer = new char[1024 * 16];
            assert(szBuffer);

            va_start(args, lpszFormat);
            vsprintf(szBuffer, lpszFormat, args);
            va_end(args);
            printf("%s", szBuffer);
            
            delete[] szBuffer;

            //printf("[%s ln=%d] \n", __func__, __LINE__);
#if 0
            FILE* fp = NULL;
            if (fp == NULL) {
                fp = fopen("d:\\my_mme.log", "a");
            }
            if (fp != NULL) {
                fprintf(fp, "%s\n", szBuffer);
                fclose(fp);
            }
#endif
        }


        void Log::Info(const char* logTag, const char* lpszFormat, ...) {

            va_list args;
            char* szBuffer = new char[1024 * 16];
            assert(szBuffer);

            va_start(args, lpszFormat);
            vsprintf(szBuffer, lpszFormat, args);
            va_end(args);

            if (Log::IsEnableOutDevice(OutDevice::Syslog)) {
                syslog(LOG_INFO, "[INFO] %s", szBuffer);
            }


            if (Log::IsEnableOutDevice(OutDevice::Console)) {
                printf("[INFO] %s\n", szBuffer);
            }

            delete[] szBuffer;
        }

        void Log::Debug(const char* logTag, const char* funcName, int line, const char* lpszFormat, ...) {

            if (Log::IsEnableDebug()) {

                va_list args;
                char* szBuffer = new char[1024 * 16];
                int i;

                sprintf(szBuffer, "[%s ln=%d] ", funcName, line);
                i = (int)strlen(szBuffer);

                va_start(args, lpszFormat);
                vsprintf(&szBuffer[i], lpszFormat, args);
                va_end(args);

                if (Log::IsEnableOutDevice(OutDevice::Syslog)) {
                    syslog(LOG_DEBUG, "[DEBUG] %s", szBuffer);
                }


                if (Log::IsEnableOutDevice(OutDevice::Console)) {
                    printf("[DEBUG] %s\n", szBuffer);
                }


                delete[] szBuffer;
            }
        }

        void Log::Error(const char* logTag, const char* funcName, int line, const char* lpszFormat, ...) {

            va_list args;
            char* szBuffer = new char[1024 * 16];
            int i;

            sprintf(szBuffer, "[%s ln=%d]", funcName, line);
            i = (int)strlen(szBuffer);

            va_start(args, lpszFormat);
            vsprintf(&szBuffer[i], lpszFormat, args);
            va_end(args);

            if (Log::IsEnableOutDevice(OutDevice::Syslog)) {
                syslog(LOG_ERR, "[ERROR] %s", szBuffer);
            }


            if (Log::IsEnableOutDevice(OutDevice::Console)) {
                printf("[ERROR] %s\n", szBuffer);
            }

            delete[] szBuffer;

        }


    }; //end of namespace OAL
}; //end of namespace Comm

#endif //#if (CommOS==CommOS_LINUX)
