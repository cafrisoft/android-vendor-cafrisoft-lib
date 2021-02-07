#include <Comm/OAL/LogWin.hpp>
#include <Comm/OAL/LogLinux.hpp>
#include <Comm/OAL/LogAndroid.hpp>

namespace Comm {
    namespace OAL {

        std::shared_ptr<Log> Log::_Instance;

        
        std::shared_ptr<Log> Log::Inst() {

            if (Log::_Instance == NULL) {
#if (CommOS==CommOS_WIN)
                Log::_Instance = std::make_shared<LogWin>();
#elif (CommOS==CommOS_LINUX)
                Log::_Instance = std::make_shared<LogLinux>();
#elif (CommOS==CommOS_ANDROID)
                Log::_Instance = std::make_shared<LogAndroid>();
#else
#error "Select OS"
#endif
            }
            assert(Log::_Instance);

            return Log::_Instance;
        }

        Log::Log(bool isOutDevConsole, bool isOutDevSyslog, bool isDebug) {
        
            _IsEnableOutDevice[(int)OutDevice::Console] = isOutDevConsole;
            _IsEnableOutDevice[(int)OutDevice::Syslog] = isOutDevSyslog;
            _IsEnableDebug = isDebug;
        }

        void Log::__EnableOutDevice(OutDevice outDev) {
            _IsEnableOutDevice[(int)outDev] = true;
        }

        void Log::__DisableOutDevice(OutDevice outDev) {
            _IsEnableOutDevice[(int)outDev] = false;
        }
        
        bool Log::__IsEnableOutDevice(OutDevice outDev) {
        
            return _IsEnableOutDevice[(int)outDev];
        }
          
        void Log::__EnableDebug() {
            _IsEnableDebug = true;
        }

        void Log::__DisableDebug() {
            _IsEnableDebug = false;
        }

        bool Log::__IsEnableDebug() {
            return _IsEnableDebug;
        }

        void Log::__SysLogOpen(const char* /*logTag*/) {
            
        }

        void Log::__SysLogClose() {
        
        }

        /*
            static function
        */
        void Log::EnableOutDevice(OutDevice outDev) {
            Log::Inst()->__EnableOutDevice(outDev);
        }

        void Log::DisableOutDevice(OutDevice outDev) {
            Log::Inst()->__DisableOutDevice(outDev);
        }

        bool Log::IsEnableOutDevice(OutDevice outDev) {
            return Log::Inst()->__IsEnableOutDevice(outDev);
        }

        void Log::EnableDebug() {
            Log::Inst()->__EnableDebug();
        }

        void Log::DisableDebug() {
            Log::Inst()->__DisableDebug();
        }

        bool Log::IsEnableDebug() {
            return Log::Inst()->__IsEnableDebug();
        }

        void Log::SysLogOpen(const char* logTag) {
            Log::Inst()->__SysLogOpen(logTag);
        }

        void Log::SysLogClose() {
            Log::Inst()->__SysLogClose();
        }


    }; //end of namespace OAL
}; //end of namespace Comm


