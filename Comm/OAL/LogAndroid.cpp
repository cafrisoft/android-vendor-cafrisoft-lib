#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/LogAndroid.hpp>

#if (CommOS==CommOS_ANDROID)

#include <utils/Log.h>
#include <cutils/klog.h>

namespace Comm {
    namespace OAL {

        LogAndroid::LogAndroid() : Log(false /*isOutDevConsole*/, true /*isOutDevSyslog*/, false /*isDebug*/) {

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
        }

        void Log::Info(const char* logTag,  const char* lpszFormat, ...) {
        
            va_list args;
            char* szBuffer = new char[1024 * 16];
            assert(szBuffer);

            va_start(args, lpszFormat);
            vsprintf(szBuffer, lpszFormat, args);
            va_end(args);

            if (Log::IsEnableOutDevice(OutDevice::Syslog)) {
                __android_log_buf_write(LOG_ID_RADIO, ANDROID_LOG_INFO, logTag, szBuffer);
            }
            
            if (Log::IsEnableOutDevice(OutDevice::Console)) {
                printf("%s\n", szBuffer);
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

                __android_log_buf_write(LOG_ID_RADIO, ANDROID_LOG_DEBUG, logTag, szBuffer);
                
                if (Log::IsEnableOutDevice(OutDevice::Console)) {
                    printf("%s\n", szBuffer);
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

            __android_log_buf_write(LOG_ID_RADIO, ANDROID_LOG_ERROR, logTag, szBuffer);
            
            if (Log::IsEnableOutDevice(OutDevice::Console)) {
                printf("%s\n", szBuffer);
            }
            
            delete[] szBuffer;

        }

    }; //end of namespace OAL
}; //end of namespace Comm

#endif //#if (CommOS==CommOS_LINUX)
