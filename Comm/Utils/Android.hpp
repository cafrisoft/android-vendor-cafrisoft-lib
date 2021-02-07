#ifndef COMM_UTILS_ANDROID_HPP__
#define COMM_UTILS_ANDROID_HPP__

#include <Comm/Base/Object.hpp>

namespace Comm {
    namespace Utils {

        class Android {
        public:
            static bool SetRecoveryCommand_UpdatePackage(std::string strPackagePathFileName);  //Android System¿ÃπÃ¡ˆ Updaate
            static bool RebootForRecovery();   // "reboot recovery"

            static bool IsThisPackageActivityTop(std::string packageName);
            static bool RunActivity(std::string packageName, std::string activityName);

            static bool GetDisplayResolution(int* width, int* height, int default_width, int default_height);
            static std::string GetIpAddrString(std::string devName);
            static unsigned int GetIpAddrI32(std::string devName);

            static int GetPropInt(std::string propName);

            //static bool ScreenCapture(int x, int y, int widht, int height, unsigned char* imgBuf);
            static bool ScreenCaptureAndRGBVerify(unsigned char r, unsigned char g, unsigned char b);
        };
    };
};

#endif
