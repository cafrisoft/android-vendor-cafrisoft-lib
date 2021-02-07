
#include "App.hpp"
#include <TESys/Property/Tester.hpp>
#include <TESys/TED/VerifyBoard.hpp>

#if (CommOS==CommOS_ANDROID)
#include <cutils/properties.h>
#endif

using namespace ControlTester;

void android_system_init() {

    system("source /system/etc/python/conf/config_python.sh");
}

void android_system_dvfs_config() {

    #define CPUFREQ_PATH "/sys/devices/system/cpu/cpu%d/cpufreq/"
    #define CPUFREQ_SCALING_scaling_governor         CPUFREQ_PATH "scaling_governor"
    #define CPUFREQ_SCALING_scaling_setspeed CPUFREQ_PATH "scaling_setspeed"
    #define CPUFREQ_SCALING_scaling_cur_freq CPUFREQ_PATH "scaling_cur_freq"
    #define CPUFREQ_SCALING_scaling_min_freq CPUFREQ_PATH "scaling_min_freq"

    char cmd[128];
    char nodeName[128];
    char buf[128];
    FILE* fp;
    int curFreq;
    int minFreq;
    const int NR_CPU = 8;

    for(int i = 0; i < 30; i++) {

        int cpuFreqSetOk = 0;

        for (int icpu = 0; icpu < NR_CPU; icpu++) {

            //Userspace
            sprintf(nodeName, CPUFREQ_SCALING_scaling_governor, icpu);

            fp = fopen(nodeName, "r");
            fgets(buf, 255, fp);
            fclose(fp);
            if (strncmp(buf, "userspace", strlen("userspace")) != 0) {
                sprintf(cmd, "echo \"userspace\" > %s", nodeName);
                system(cmd);
                CLOGI("Send Cmd : [%s]", cmd);
            }
            else {
                CLOGI("CPU%d DVFS is userspace", icpu);
            }

            //Read MinFreq
            sprintf(nodeName, CPUFREQ_SCALING_scaling_min_freq, icpu);
            fp = fopen(nodeName, "r");
            fscanf(fp, "%d", &minFreq);
            fclose(fp);

            //SetFreq
            sprintf(nodeName, CPUFREQ_SCALING_scaling_cur_freq, icpu);
            fp = fopen(nodeName, "r");
            fscanf(fp, "%d", &curFreq);
            fclose(fp);

            if (curFreq != minFreq) {
                sprintf(nodeName, CPUFREQ_SCALING_scaling_setspeed, icpu);
                sprintf(cmd, "echo %d > %s", minFreq, nodeName);
                system(cmd);
                CLOGI("Send Cmd : [%s]  (curFreq:%d minFreq:%d)", cmd, curFreq, minFreq);
            }
            else {
                CLOGI("CPU%d Freq is %d (minFreq:%d)", icpu, curFreq, minFreq);
                cpuFreqSetOk++;
            }
        }

        if (cpuFreqSetOk == NR_CPU) {
            CLOGI("DVFS, Set MinFreq Complete !!!!!!!!!!!!!^^");
            break;
        }

        Comm::OAL::Thread::Sleep(3000);
    }
}

int main(int argc, char* argv[]) {

    int testerCount = 1;
    int boardID = -1;

#if (CommOS==CommOS_ANDROID)
    android_system_init();
#endif

    Comm::OAL::System::SocketInit();

    Comm::OAL::Log::SysLogOpen(CLOG_TAG);
    Comm::OAL::Log::EnableDebug();

#if (CommOS==CommOS_ANDROID)    
    for(int i = 0; i < 10; i++) {
        int boot_complete = 0;
        char boot_complete_prop[PROPERTY_VALUE_MAX];
        property_get("sys.boot_completed", boot_complete_prop, "0");
        if (sscanf(boot_complete_prop, "%d", &boot_complete) == 1 && boot_complete == 1) {
            CLOGI("Boot Complet!!");
            break;
        }
        CLOGI("Wait boot complte......  boot_complete_prop=%s  boot_complete=%d", boot_complete_prop, boot_complete);
        Comm::OAL::Thread::Sleep(1000);
    }
#endif

#if (CommOS==CommOS_ANDROID)

    testerCount = 1;
    boardID = TESys::Property::Tester::Board::GetID();
    if (boardID > 0) {
        int port;
        char prop_port[PROPERTY_VALUE_MAX];
        property_get("persist.adb.tcp.port", prop_port, "");
        if (sscanf(prop_port, "%d", &port) == 1 && port > 0) {
            property_set("tesysdbg.adb.tcp.port", "55555");
        }
        else {
            property_set("persist.adb.tcp.port", "55555");
        }
    }
    else {
        property_set("tesysdbg.adb.tcp.port", "-1");
        property_set("persist.adb.tcp.port", "-1");
        while (1) {
            sleep(100);
        }
    }

#elif (CommOS==CommOS_WIN)
    testerCount = 1;
    boardID = 400;// TESys::Property::Tester::Board::GetID();

#elif (CommOS==CommOS_LINUX)
    if (argc == 3) {
        boardID = atoi(argv[1]);
        testerCount = atoi(argv[2]);
    }
    else {
        //testerCount = 1;
        //boardID = TESys::Property::Tester::Board::GetID();
        printf("ERRROR: argument error \n");
        printf("\tusage) TESysControlTester  [boardID] [testerCount]");
        return -1;
    }
    
#endif

    CLOGI("AppControlTester Run.....  Start-BoardID=%d TesterCount=%d", boardID, testerCount);

    TESys::TED::VerifyBoard::Inst()->SysLedSetRGB(0, 0, 0);

    std::shared_ptr<TESys::Control::Tester> testerArray[1024];

    for (int idx = 0; idx < testerCount; idx++) {

        int testerID = idx + boardID;
        testerArray[idx] = std::make_shared<TESys::Control::Tester>(testerID);
        assert(testerArray[idx]);

        OAL::Thread::Sleep(100);
    }

#if (CommOS==CommOS_ANDROID)
    android_system_dvfs_config();
#endif

    while (true) {
        OAL::Thread::Sleep(1000*3600*24*10);
    }


#if 1
    //App::Init(testerCount);
    //App::Inst()->Run();
#else
    int iloop = 0;
    while (true) {
        CLOGI("%d. AppControlTester Run.....  TesterCount=%d", iloop++, testerCount);
        OAL::Thread::Sleep(1000);
    }

#endif   

    Comm::OAL::Log::SysLogClose();


    return 0;
}
