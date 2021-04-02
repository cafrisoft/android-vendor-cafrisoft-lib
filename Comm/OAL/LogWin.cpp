#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/LogWin.hpp>

#if (CommOS==CommOS_WIN)

namespace Comm {
    namespace OAL {

        LogWin::LogWin() : Log(true /*isOutDevConsole*/, true /*isOutDevSyslog*/, true /*isDebug*/) {
        
        }

        void Log::Printf(const char* lpszFormat, ... ) {
        
            char* szBuffer;
            size_t bufAllocByteSize;
            va_list args;

            va_start(args, lpszFormat);

            bufAllocByteSize = vsnprintf(nullptr, 0, lpszFormat, args) + 1; // Extra space for '\0'
            szBuffer = new char[bufAllocByteSize];
            assert(szBuffer);
            _vstprintf(szBuffer, lpszFormat, args);
            va_end(args);

            OutputDebugString(szBuffer);
            printf("%s", szBuffer);

            delete[] szBuffer;
        }

        void Log::Info(const char* logTag, const char* lpszFormat, ...) {

            char* szBuffer;
            size_t bufAllocByteSize;
            va_list args;

            va_start(args, lpszFormat);
            bufAllocByteSize = vsnprintf(nullptr, 0, lpszFormat, args) + 1; // Extra space for '\0'
            szBuffer = new char[bufAllocByteSize];
            assert(szBuffer);
            _vstprintf(szBuffer, lpszFormat, args);
            va_end(args);

            OutputDebugString(szBuffer);
            OutputDebugString("\n");

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

                sprintf(szBuffer, "[%s][%s ln=%d] ", logTag, funcName, line);
                i = (int)strlen(szBuffer);

                va_start(args, lpszFormat);
                _vstprintf(&szBuffer[i], lpszFormat, args);
                va_end(args);

                OutputDebugString(szBuffer);
                OutputDebugString("\n");

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

            sprintf(szBuffer, "ERR: [%s][%s ln=%d] ", logTag, funcName, line);
            i = (int)strlen(szBuffer);

            va_start(args, lpszFormat);
            _vstprintf(&szBuffer[i], lpszFormat, args);
            va_end(args);

            OutputDebugString(szBuffer);
            OutputDebugString("\n");

            if (Log::IsEnableOutDevice(OutDevice::Console)) {
                printf("%s\n", szBuffer);
            }

            delete[] szBuffer;
            
        }

    }; //end of namespace OAL
}; //end of namespace Comm


#endif //#if (CommOS==CommOS_WIN)