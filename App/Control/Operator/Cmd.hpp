#ifndef APP_TESYSOPERATOR_CMD_HPP__
#define APP_TESYSOPERATOR_CMD_HPP__

#include "AppDefine.hpp"

namespace TESysOperator {

    namespace Cmd {

        int ParseBoardID(int argc, const char** argv);

        class Hub {

        public:
            static  bool DisplayStatus(int argc, const char** argv);
        };

        class Tester {

        public:
            static  bool DisplayStatus(int argc, const char** argv);
            static  bool FWUpgrade(int argc, const char** argv);
            static  bool Reboot(int argc, const char** argv);
            static  bool Shutdown(int argc, const char** argv);
            static  bool RunTC(int argc, const char** argv);
            static  bool RunJOB(int argc, const char** argv);
            static  bool FileSync(int argc, const char** argv);
            static  bool FlashWriter(int argc, const char** argv);
            
            static  bool GetFlashWriterError(int argc, const char** argv);
            static  bool RunAdbTEsysUpgrade(int argc, const char** argv);

            static  bool KillTESysTester(int argc, const char** argv);
            static  bool SendLinuxCommand(int argc, const char** argv);
            static  bool SendLinuxCommandWithResponse(int argc, const char** argv);

            static  bool Test1(int argc, const char** argv);
            static  bool KillPython(int argc, const char** argv);
            static  bool PythonPID(int argc, const char** argv);
            
        };

        class FileSync {

        public:
            static  bool RunHubCalCRC(int argc, const char** argv);
            static  bool RunFileSync(int argc, const char** argv);
            static  bool CalRemoteStorageCRC(int argc, const char** argv);
            static  bool DirAgingPythonFile(int argc, const char** argv);
        };

        class TED {
        public:
            static bool FrameRate_HS1_120Hz(int argc, const char** argv);
            static bool FrameRate_Normal_60Hz(int argc, const char** argv);
            static bool FrameRate_HLPM_ON(int argc, const char** argv);
            static bool FrameRate_HLPM_OFF(int argc, const char** argv);
            static bool FrameRate_TE_Time(int argc, const char** argv);
            static bool DD_FB_Blank_Enter(int argc, const char** argv);
            static bool DD_FB_Blank_Leave(int argc, const char** argv);
            static bool PatternDrawRed(int argc, const char** argv);
            static bool PatternDrawGreen(int argc, const char** argv);
            static bool PatternDrawBlue(int argc, const char** argv);
            static bool PatternDrawWhite(int argc, const char** argv);
            static bool PatternDrawBlack(int argc, const char** argv);
            static bool PatternScreenVerify(int argc, const char** argv);
            static bool FlashWriter(int argc, const char** argv);
            
            static bool Verify_Flash(int argc, const char** argv);
            static bool Verify_AdcRegVREG1(int argc, const char** argv);
        };
      
        class Verify {
        public:
            //static  bool All(int argc, const char** argv);
            static  bool ChipID(int argc, const char** argv);
            static  bool Flash(int argc, const char** argv);
            static  bool PatternApp(int argc, const char** argv);
            static  bool AdcRegulatorVREG1(int argc, const char** argv); // Regulaotr VREG1 Àü
            static  bool AdcStaticCurrent(int argc, const char** argv); // Regulaotr VREG1 Àü
        };


    };
};

#endif
