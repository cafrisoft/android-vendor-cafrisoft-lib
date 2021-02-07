#ifndef COMM_OAL_LOG_HPP
#define COMM_OAL_LOG_HPP

#include <Comm/Base/Object.hpp>

namespace Comm {
    namespace OAL {

        class Log : public Base::Object {

        public:
            enum class OutDevice {
                Console,
                Syslog,  //if android, logcat
                MaxCount
            };

        private:
            static std::shared_ptr<Log> _Instance;
        private:
            static std::shared_ptr<Log> Inst();

        private:
            bool _IsEnableOutDevice[(int)Log::OutDevice::MaxCount];  // 출력장치 
            bool _IsEnableDebug;   //DebugMode Enable

        protected:
            Log(bool isOutDevConsole, bool isOutDevSyslog, bool isDebug);
        
        protected:
            virtual void __EnableOutDevice(OutDevice outDev);
            virtual void __DisableOutDevice(OutDevice outDev);
            virtual bool __IsEnableOutDevice(OutDevice outDev);

            virtual void __EnableDebug();
            virtual void __DisableDebug();
            virtual bool __IsEnableDebug();

            virtual void __SysLogOpen(const char* logTag);
            virtual void __SysLogClose();


        public:
            static void EnableOutDevice(OutDevice outDev);
            static void DisableOutDevice(OutDevice outDev);
            static bool IsEnableOutDevice(OutDevice outDev);

            static void EnableDebug();
            static void DisableDebug();
            static bool IsEnableDebug();

            static void SysLogOpen(const char* logTag);
            static void SysLogClose();

            static void Printf(const char* lpszFormat, ...);
            static void Info(const char* logTag, const char* lpszFormat, ...);
            static void Debug(const char* logTag, const char* funcName, int line, const char* lpszFormat, ...);
            static void Error(const char* logTag, const char* funcName, int line, const char* lpszFormat, ...);
        };

    }; //end of namespace OAL
}; //end of namespace Comm

#endif // #ifndef COMM_OAL_LOG_HPP

