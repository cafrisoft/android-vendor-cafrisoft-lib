#ifndef APPCONTROLSHELL_CMD_HPP__
#define APPCONTROLSHELL_CMD_HPP__

#include "AppDefine.hpp"

namespace AppControlShell {

    namespace Cmd {

        class Hub {

        public:
            static const char* CMD_TESTER;
            static const char* CMD_DISPLAY_INFO;

        public:
            static  bool DisplayInfo(int argc, const char** argv);
            
            static  bool ChangeIPAddr(int argc, const char** argv);
            static  bool ClearIPAddr(int argc, const char** argv);
        };


        class Tester {

        public: 
            static const char* CMD_TESTER;
            static const char* CMD_GEN_FACTORY_DATA;
                
        public:
            static  bool GetBoardID(int argc, const char** argv);
            static  bool GenFactoryData(int argc, const char** argv);
            static  bool DisplayBoardInfo(int argc, const char** argv);
            static  bool KillPython(int argc, const char** argv);
            static  bool PythonPID(int argc, const char** argv);
            static  bool FWUpgrade(int argc, const char** argv);
        };

        class FileSync {

        public:
            static  bool DisplayInfo(int argc, const char** argv);
            static  bool CalCRC(int argc, const char** argv);
        };

        class SysTest {

        public:
            static const char* CMD_TESTER;
            static const char* CMD_TEST_1;

        public:
            static  bool Test1(int argc, const char** argv);
            static  bool ProcessMutexRead(int argc, const char** argv);
            static  bool ProcessMutexWrite(int argc, const char** argv);
            static  bool ServerStorageCal(int argc, const char** argv);
        };

        class OALTest {

        public:
            static  bool ProcessMutexRead(int argc, const char** argv);
            static  bool ProcessMutexWrite(int argc, const char** argv);
            static  bool IsFileSyncRun(int argc, const char** argv);
        };

        class Android {

        public:
            static  bool PrintCommandList(int argc, const char** argv);
            static  bool UpdatePackage(int argc, const char** argv);
            static  bool RebootRecovery(int argc, const char** argv);
            static  bool CheckPatternDrawApp(int argc, const char** argv);
            static  bool DisplayInfo(int argc, const char** argv);
            static  bool GetPropInt(int argc, const char** argv);
        };

        class StringTest {

        public:
            static  bool StringFormatTest(int argc, const char** argv);
        };

        class TED {

        public:
           // static  bool LdoAdc(int argc, const char** argv);
            static  bool Test1(int argc, const char** argv);
            static  bool Test2(int argc, const char** argv);
            static  bool ChipID(int argc, const char** argv);

            static  bool PatternDrawConnect(int argc, const char** argv);
            static  bool PatternDrawDisconnect(int argc, const char** argv);
            static  bool PatternDrawSendCommand(int argc, const char** argv);
            static  bool PatternScreenVerify(int argc, const char** argv);

            static  bool AgingMeasureADC(int argc, const char** argv);

            static  bool MonitorEXTCurrent(int argc, const char** argv);

            //TED내부에 있는 Flash메모리 접근, 확인 
            // http://aits.anapass.com:8090/display/SI/ANA6707+HLPM+Mode
            static bool FlashVerify(int argc, const char** argv);

            static bool SetFrameRate(int argc, const char** argv);
            static bool GetFrameRate(int argc, const char** argv);
        };

        class Database {

        public:
            static  bool PickTester(int argc, const char** argv);
        };

        class Socket {

        public:
            static  bool ChkBufSize(int argc, const char** argv);
            static  bool TESysNetDataAcqPacketAnalysis(int argc, const char** argv);  // TESys::Net::DataAcq Packet 분석
            static  bool DisplayInfo(int argc, const char** argv);
        };


#if (CommOS == CommOS_WIN)

        class Draw2D {

        public:
            static  bool GenBmpWithText(int argc, const char** argv);
        };

#endif

        class Export {
        public:
            static  bool JobToCSV(int argc, const char** argv);
            static  bool TcToCSV(int argc, const char** argv);
            static  bool CSVMerge(int argc, const char** argv);
            static  bool StatisticsData(int argc, const char** argv);

            static  bool ScToCSV(int argc, const char** argv);
            static  bool RawDataToOneCSVFile(int argc, const char** argv); //CSV파일 1개에 모두 모은다.

            static  bool Analysis_Job_Sc_Tc(int argc, const char** argv);
            static  bool Analysis_Job_Sc(int argc, const char** argv);

            static bool EmulAgingWithRawData(int argc, const char** argv);
        };

        class Verify {
        public:
            static  bool All(int argc, const char** argv);
            static  bool ChipID(int argc, const char** argv);
            static  bool Flash(int argc, const char** argv);
            static  bool PatternApp(int argc, const char** argv);
            static  bool AdcRegulatorVREG1(int argc, const char** argv); // Regulaotr VREG1 전
            static  bool AdcStaticCurrent(int argc, const char** argv); // Regulaotr VREG1 전
        };

        class Emulator {
        public:
            static bool DisplayCommand(int argc, const char** argv);
            static bool TedMipiErrSet(int argc, const char** argv);
            static bool TedT2MErrSet(int argc, const char** argv);
            static bool TedESDErrSet(int argc, const char** argv);
        };

        #if (CommOS==CommOS_WIN || CommOS==CommOS_LINUX)
        class MySQL {
        public:
            static bool InsertBoard(int argc, const char** argv);
            
        };
        #endif

    };
};

#endif
