#define CLOG_TAG "CommUtilsAndroid"
#include <Comm/Utils/Android.hpp>
#include <Comm/OAL/Log.hpp>
#include <Comm/OAL/Thread.hpp>
#include <Comm/OAL/FileSys.hpp>

#if (CommOS==CommOS_ANDROID)
#include <netutils/ifc.h>
#include <cutils/properties.h>

#elif (CommOS==CommOS_LINUX)
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#endif


namespace Comm {
    namespace Utils {

        bool Android::SetRecoveryCommand_UpdatePackage(std::string strPackagePathFileName) {
            FILE* fp_cmd;
            fp_cmd = fopen("/cache/recovery/command", "w");
            if (fp_cmd) {
                fprintf(fp_cmd, "--update_package=%s\n", strPackagePathFileName.c_str());
                fclose(fp_cmd);
            }
            return true;
        }

        // "reboot recovery"
        bool Android::RebootForRecovery() {

            system("reboot recovery");

            return true;
        }


#define ANDROID_TOP_ACTIVITY_CHECK_COMMAND "dumpsys activity | grep top-activity"
#define ANDROID_GET_DISPLAY_RESOLUTION_COMMAND "wm size"

#if (CommOS==CommOS_ANDROID)

#define ANDROID_POPEN  popen
#define ANDROID_PCLOSE  pclose

#elif (CommOS==CommOS_WIN || CommOS==CommOS_LINUX)

#define ANDROID_POPEN  android_popen
#define ANDROID_PCLOSE  android_pclose

#if (CommOS == CommOS_LINUX)
#define LINUX_POPEN_TMP_DIR "/opt/TESys/tmp/ANDROID"
#endif

        static FILE* android_popen(const char* cmd, const char* mode) {

            FILE* fp;
            const char* fileName = "";

            if (strcmp(cmd, ANDROID_TOP_ACTIVITY_CHECK_COMMAND) == 0) {
#if (CommOS==CommOS_WIN)
                fileName = "c:\\Temp\\dumpsys_activity_grep_top_activity.txt";
#else
                //#define LINUX_POPEN_TMP_DIR "/opt/TESys/tmp/ANDROID";
                if (!Comm::OAL::FileSys::IsThisDirExist(LINUX_POPEN_TMP_DIR)) {
                    Comm::OAL::FileSys::MakeDir(LINUX_POPEN_TMP_DIR);
                }

                fileName = LINUX_POPEN_TMP_DIR "/dumpsys_activity_grep_top_activity.txt";
#endif

                if (!Comm::OAL::FileSys::IsThisFileExist(fileName)) {
                    fp = fopen(fileName, "w");
                    if (fp) {
                        fprintf(fp, "Proc # 0: fore  T / A / T trm : 0 4247 : com.anapass.androidcanvasexample / u0a0(top - activity) ");
                        fclose(fp);
                    }
                }

            }
            else if (strcmp(cmd, ANDROID_GET_DISPLAY_RESOLUTION_COMMAND) == 0) {

#if (CommOS==CommOS_WIN)
                fileName = "c:\\Temp\\android_emul_dumpsys.txt";
#else
                //#define LINUX_POPEN_TMP_DIR "/opt/TESys/tmp/ANDROID/"
                if (!Comm::OAL::FileSys::IsThisDirExist(LINUX_POPEN_TMP_DIR)) {
                    Comm::OAL::FileSys::MakeDir(LINUX_POPEN_TMP_DIR);
                }
                fileName = LINUX_POPEN_TMP_DIR "android_emul_dumpsys.txt";
#endif

                if (!Comm::OAL::FileSys::IsThisFileExist(fileName)) {
                    fp = fopen(fileName, "w");
                    if (fp) {
                        fprintf(fp, "Physical size: 1644x3840");
                        fclose(fp);
                    }
                }

            }


            fp = fopen(fileName, mode);
            return fp;
        }

        static void android_pclose(FILE* fp) {
            fclose(fp);
        }
#else
        #eror "ERROR: Select OS"
#endif

            bool Android::IsThisPackageActivityTop(std::string packageName) {

            bool bRet = false;
            FILE* fp = ANDROID_POPEN(ANDROID_TOP_ACTIVITY_CHECK_COMMAND, "r");
            if (fp) {
                char buf[512];
                while (1) {
                    const char* p = fgets(buf, 512, fp);
                    if (p) {
                        // Expected : "Proc # 0: fore  T/A/T trm : 0 4247 : com.anapass.androidcanvasexample / u0a0(top - activity)";
                        const char* b = strstr(p, packageName.c_str());
                        if (b) {
                            bRet = true;
                            break;
                        }
                    }
                    else {
                        break;
                    }
                }
                ANDROID_PCLOSE(fp);
            }

            return bRet;
        }

        bool Android::RunActivity(std::string packageName, std::string activityName) {

            char cmd[512];

            sprintf(cmd, "am start -a android.intent.action.MAIN -n %s/%s", packageName.c_str(), activityName.c_str());
            FILE* fp = ANDROID_POPEN(cmd, "r");
            if (fp) {
                char buf[512];
                while (1) {
                    const char* p = fgets(buf, 512, fp);
                    if (p == NULL) {
                        break;
                    }
                    else {
                        Comm::OAL::Thread::Sleep(1);
                    }
                }
                ANDROID_PCLOSE(fp);
            }

            return true;
        }

        bool Android::GetDisplayResolution(int* width, int* height, int default_width, int default_height) {

            bool bRet = false;
            static int s_DisplayWidth = -1;
            static int s_DisplayHeight = -1;



            if ((s_DisplayWidth == -1)
                || (s_DisplayHeight == -1)) {


                FILE* fp = ANDROID_POPEN(ANDROID_GET_DISPLAY_RESOLUTION_COMMAND, "r");  // expected  'Physical size: 1644x3840'
                if (fp) {
                    char buf[512];
                    while (1) {
                        char* p = fgets(buf, 512, fp);
                        if (p) {
                            // Expected : "Proc # 0: fore  T/A/T trm : 0 4247 : com.anapass.androidcanvasexample / u0a0(top - activity)";
                            char* b = strstr(p, "Physical size:");
                            if (b) {

                                b = strchr(b, ':');
                                if (b) {

                                    char* szW = b + 1;
                                    char* szH;
                                    b = strchr(szW, 'x');
                                    if (b) {
                                        *b = '\0';
                                        szH = b + 1;

                                        int w = atoi(szW);
                                        int h = atoi(szH);

                                        if (((w > 100) && (w < 16440))
                                            && (h > 100 && (h < 38400))) {

                                            s_DisplayWidth = w;
                                            s_DisplayHeight = h;

                                            bRet = true;
                                        }

                                    }
                                    break;
                                }
                            }
                        }
                        else {
                            break;
                        }
                    }
                    ANDROID_PCLOSE(fp);
                }
            }
            else {
                bRet = true;
            }

            if (bRet) {
                if (width) *width = s_DisplayWidth;
                if (height) *height = s_DisplayHeight;
            }
            else {
                if (width) *width = default_width;
                if (height) *height = default_height;
                bRet = true;
            }

            return bRet;
        }

#if (CommOS != CommOS_ANDROID)

        int ifc_init(void) {
        
            return 0;
        }

        int ifc_get_addr(const char* devName, unsigned int* addr) {

            #if (CommOS == CommOS_LINUX)

            /*
                 https://technote.kr/176 [TechNote.kr]
            */

            struct ifreq ifr;
            char ipstr[40];
            int s;
            struct sockaddr_in* aptr;

            s = socket(AF_INET, SOCK_DGRAM, 0);
            if (s > 0) {
                strncpy(ifr.ifr_name, devName, IFNAMSIZ);
                if (ioctl(s, SIOCGIFADDR, &ifr) < 0) {
                    printf("[ifc_get_addr] ERROR : ioctl(s, SIOCGIFADDR, &ifr) \n");
                }
                else {

                    aptr = (struct sockaddr_in*)&ifr.ifr_addr;
                    *addr = aptr->sin_addr.s_addr;
                    //addr.sin_addr.s_addr = addrInt;
                    //strIP = inet_ntoa(addr.sin_addr);

                    //inet_ntop(AF_INET, ifr.ifr_addr.sa_data + 2, ipstr, sizeof(struct sockaddr));
                    //printf("myOwn IP Address is %s\n", ipstr);
                }
                close(s);
            }

            #elif (CommOS == CommOS_WIN)

            //struct sockaddr_in sockAddr;
                        //inet_aton("222.111.0.0", &sockAddr.sin_addr);

                * addr = 0x01020304;
            #else   
            #error "Select OS"
            #endif
            
            return 0;
        }

#endif
        std::string Android::GetIpAddrString(std::string devName) {

            std::string strIP="0.0.0.0";
            unsigned int addrInt;
            struct sockaddr_in addr;

            ifc_init();

            if (ifc_get_addr(devName.c_str(), &addrInt) == 0) {

                //PRINTF("addrInt=0x%08X \n", addrInt);
                addr.sin_addr.s_addr = addrInt;
                strIP = inet_ntoa(addr.sin_addr);
            }
            else {
                //PRINTF("FAIL:  ifc_get_addr  \n");
            }
        

            return strIP;
        }
        
        unsigned int Android::GetIpAddrI32(std::string devName) {

            unsigned int addrInt = 0;
            //struct sockaddr_in addr;

            ifc_init();

            if (ifc_get_addr(devName.c_str(), &addrInt) == 0) {

                //PRINTF("addrInt=0x%08X \n", addrInt);
                //addr.sin_addr.s_addr = addrInt;
                //strIP = inet_ntoa(addr.sin_addr);
            }
            else {
                //PRINTF("FAIL:  ifc_get_addr  \n");
            }


            return addrInt;
        }

        #if (CommOS!=CommOS_ANDROID)
        #define PROPERTY_VALUE_MAX 255
        static int property_get(const char* propName, char* buf, const char* defaultValue) {

            if (strcmp(propName, "sys.boot_completed") == 0) {
                strcpy(buf, "1");
            }
            else {
                strcpy(buf, defaultValue);
            }
            return 1;
        }
        #endif

        int Android::GetPropInt(std::string propName) {
        
            int v;
            int prop_value_int = -1;
            char prop_value_str[PROPERTY_VALUE_MAX];
            property_get(propName.c_str(), prop_value_str, "-1");
            if (sscanf(prop_value_str, "%d", &v) == 1) {
                prop_value_int = v;
            }
            return prop_value_int;
        }

    };
};
