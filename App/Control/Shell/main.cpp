#include "AppDefine.hpp"
#include "Cmd.hpp"

using namespace AppControlShell;

int main(int argc, const char* argv[]) {

    //CmdSet Hub
    std::shared_ptr<Shell::CmdSet> cmdSetHub = std::make_shared<Shell::CmdSet>(Cmd::Hub::CMD_TESTER, "util cmd about Tester");
    assert(cmdSetHub);
    cmdSetHub->AddItem(Cmd::Hub::CMD_DISPLAY_INFO, "display info", Cmd::Hub::DisplayInfo);
    cmdSetHub->AddItem("setipaddr", "set new hub ip addr", Cmd::Hub::ChangeIPAddr);
    cmdSetHub->AddItem("clripaddr", "clear hub ip addr", Cmd::Hub::ClearIPAddr);

    //CmdSet Tester
    std::shared_ptr<Shell::CmdSet> cmdSetTester = std::make_shared<Shell::CmdSet>(Cmd::Tester::CMD_TESTER, "util cmd about Tester");
    assert(cmdSetTester);
    cmdSetTester->AddItem("boardid", "read tester board id", Cmd::Tester::GetBoardID);
    cmdSetTester->AddItem(Cmd::Tester::CMD_GEN_FACTORY_DATA, "generate factory data", Cmd::Tester::GenFactoryData);
    cmdSetTester->AddItem("info", "info", Cmd::Tester::DisplayBoardInfo);
    cmdSetTester->AddItem("killpy", "killpy", Cmd::Tester::KillPython);
    cmdSetTester->AddItem("pypid", "display py pid", Cmd::Tester::PythonPID);
    cmdSetTester->AddItem("fwupgrade", "android fw upgrade", Cmd::Tester::FWUpgrade);

    //CmdSet System
    std::shared_ptr<Shell::CmdSet> cmdSetSysTest = std::make_shared<Shell::CmdSet>("sys", "util cmd about Tester");
    assert(cmdSetSysTest);
    cmdSetSysTest->AddItem(Cmd::SysTest::CMD_TEST_1, "test1", Cmd::SysTest::Test1);
    cmdSetSysTest->AddItem("srvstorage", "srvstorage", Cmd::SysTest::ServerStorageCal);

    //CmdSet OAL
    std::shared_ptr<Shell::CmdSet> cmdSetOALTest = std::make_shared<Shell::CmdSet>("oal", "util cmd about Tester");
    assert(cmdSetOALTest);
    cmdSetOALTest->AddItem("procmutex_read", "procmutex_read", Cmd::OALTest::ProcessMutexRead);
    cmdSetOALTest->AddItem("procmutex_write", "procmutex_write", Cmd::OALTest::ProcessMutexWrite);
    cmdSetOALTest->AddItem("is_filesync_run", "is_filesync_run", Cmd::OALTest::IsFileSyncRun);

    //CmdSet FileSync
    std::shared_ptr<Shell::CmdSet> cmdSetFileSync = std::make_shared<Shell::CmdSet>("filesync", "FileSync Util");
    assert(cmdSetFileSync);
    cmdSetFileSync->AddItem("info", "info", Cmd::FileSync::DisplayInfo);
    cmdSetFileSync->AddItem("crc", "cal crc", Cmd::FileSync::CalCRC);

    //CmdSet Android
    std::shared_ptr<Shell::CmdSet> cmdSetAndroid = std::make_shared<Shell::CmdSet>("android", "Android Tool");
    assert(cmdSetAndroid);
    cmdSetAndroid->AddItem("update_package", "update android system package", Cmd::Android::UpdatePackage);
    cmdSetAndroid->AddItem("chkpatterndraw", "chkpatterndraw", Cmd::Android::CheckPatternDrawApp);
    cmdSetAndroid->AddItem("dispinfo", "dispinfo", Cmd::Android::DisplayInfo);
    cmdSetAndroid->AddItem("getpropint", "get properyt int type", Cmd::Android::GetPropInt);

    //CmdSet StringTest
    std::shared_ptr<Shell::CmdSet> cmdSetString = std::make_shared<Shell::CmdSet>("string", "String Test");
    assert(cmdSetString);
    cmdSetString->AddItem("format_test", "format_test", Cmd::StringTest::StringFormatTest);

    //CmdSet TED
    std::shared_ptr<Shell::CmdSet> cmdSetTED = std::make_shared<Shell::CmdSet>("ted", "String Test");
    assert(cmdSetTED);
    //cmdSetTED->AddItem("ldoadc", "ldoadc", Cmd::TED::LdoAdc);
    cmdSetTED->AddItem("chipid", "chipid", Cmd::TED::ChipID);
    cmdSetTED->AddItem("ptrn_c", "ptrn_connect", Cmd::TED::PatternDrawConnect);
    cmdSetTED->AddItem("ptrn_d", "ptrn_disconnect", Cmd::TED::PatternDrawDisconnect);
    cmdSetTED->AddItem("ptrn_s", "ptrn_sendcommand", Cmd::TED::PatternDrawSendCommand);
    cmdSetTED->AddItem("ptrn_screen_verify", "screen capture and verify", Cmd::TED::PatternScreenVerify);
    cmdSetTED->AddItem("measure", "measure", Cmd::TED::AgingMeasureADC);
    cmdSetTED->AddItem("ext_curr", "vlin1", Cmd::TED::MonitorEXTCurrent);
    cmdSetTED->AddItem("test2", "test2", Cmd::TED::Test2);
    cmdSetTED->AddItem("setfr", "set frame rate", Cmd::TED::SetFrameRate);
    cmdSetTED->AddItem("getfr", "get frame rate", Cmd::TED::GetFrameRate);

    //CmdSet DBVerify
    std::shared_ptr<Shell::CmdSet> cmdSetDBVerify = std::make_shared<Shell::CmdSet>("db", "database");
    assert(cmdSetDBVerify);
    cmdSetDBVerify->AddItem("picktester", "picktester", Cmd::Database::PickTester);

    //CmdSet Socket
    std::shared_ptr<Shell::CmdSet> cmdSetSocket = std::make_shared<Shell::CmdSet>("socket", "socket");
    assert(cmdSetSocket);
    cmdSetSocket->AddItem("chkbuf", "chkbuf", Cmd::Socket::ChkBufSize);
    cmdSetSocket->AddItem("analy_dataacq", "analy_dataacq", Cmd::Socket::TESysNetDataAcqPacketAnalysis);
    cmdSetSocket->AddItem("display_info", "display netwrok info", Cmd::Socket::DisplayInfo);

#if (CommOS==CommOS_WIN) 
    //CmdSet Draw2D
    std::shared_ptr<Shell::CmdSet> cmdSetDraw2D = std::make_shared<Shell::CmdSet>("draw2d", "draw2d");
    assert(cmdSetDraw2D);
    cmdSetDraw2D->AddItem("genbmptxt", "genbmptxt", Cmd::Draw2D::GenBmpWithText);

#endif

    //CmdSet Export
    std::shared_ptr<Shell::CmdSet> cmdExport = std::make_shared<Shell::CmdSet>("export", "export");
    assert(cmdExport);
    cmdExport->AddItem("rawdata2csv", "export RawData to 1 CSV File", Cmd::Export::RawDataToOneCSVFile);
    cmdExport->AddItem("job2csv", "job2csv", Cmd::Export::JobToCSV);
    cmdExport->AddItem("tc2csv", "tc2csv", Cmd::Export::TcToCSV);
    cmdExport->AddItem("csvmerge", "csvmerge", Cmd::Export::CSVMerge);
    cmdExport->AddItem("st", "statistics", Cmd::Export::StatisticsData);
    cmdExport->AddItem("analy_job_sc_tc", "analy job/sc/tc", Cmd::Export::Analysis_Job_Sc_Tc);
    cmdExport->AddItem("analy_job_sc", "analy job/sc", Cmd::Export::Analysis_Job_Sc);
    cmdExport->AddItem("emul_aging", "emulate aging test with rawdata", Cmd::Export::EmulAgingWithRawData);

    //CmdSet Verify
    std::shared_ptr<Shell::CmdSet> cmdVerify = std::make_shared<Shell::CmdSet>("verify", "verify system");
    assert(cmdVerify);
    cmdVerify->AddItem("all", "All Test Run", Cmd::Verify::All);
    cmdVerify->AddItem("chipid", "read chipid", Cmd::Verify::ChipID);
    cmdVerify->AddItem("flash", "TED Flash writer verify", Cmd::Verify::Flash);
    cmdVerify->AddItem("patternapp", "Pattern DrawApp Verify", Cmd::Verify::PatternApp);
    cmdVerify->AddItem("adcregvreg1", "adc regulator VREG1", Cmd::Verify::AdcRegulatorVREG1);
    cmdVerify->AddItem("adc_static_current", "adc static current", Cmd::Verify::AdcStaticCurrent);

    //CmdSet Emulator
    std::shared_ptr<Shell::CmdSet> cmdEmulator = std::make_shared<Shell::CmdSet>("emul", "emulator");
    assert(cmdEmulator);
    cmdEmulator->AddItem("disp", "display status", Cmd::Emulator::DisplayCommand);
    cmdEmulator->AddItem("mipierr", "set ted mipi err", Cmd::Emulator::TedMipiErrSet);
    cmdEmulator->AddItem("t2merr", "set ted t2m err", Cmd::Emulator::TedT2MErrSet);
    cmdEmulator->AddItem("esderr", "set ted esd err", Cmd::Emulator::TedESDErrSet);

#if (CommOS==CommOS_WIN)
    //CmdSet MySQL
    std::shared_ptr<Shell::CmdSet> cmdMySQL = std::make_shared<Shell::CmdSet>("mysql", "mysql");
    assert(cmdEmulator);
    cmdEmulator->AddItem("insert_board", "insert board data", Cmd::MySQL::InsertBoard);

#endif

    //CmdSet Main
    std::shared_ptr<Shell::Main> shellMain = std::make_shared<Shell::Main>("TESysShell");
    assert(shellMain);

    shellMain->AddSubSet(cmdSetHub);
    shellMain->AddSubSet(cmdSetTester);
    shellMain->AddSubSet(cmdSetSysTest);
    shellMain->AddSubSet(cmdSetOALTest);
    shellMain->AddSubSet(cmdSetFileSync);
    shellMain->AddSubSet(cmdSetAndroid);
    shellMain->AddSubSet(cmdSetString);
    shellMain->AddSubSet(cmdSetTED);
    shellMain->AddSubSet(cmdSetDBVerify);
    shellMain->AddSubSet(cmdSetSocket);
#if (CommOS==CommOS_WIN) 
    shellMain->AddSubSet(cmdSetDraw2D);
#endif
    shellMain->AddSubSet(cmdExport);
    shellMain->AddSubSet(cmdVerify);
    shellMain->AddSubSet(cmdEmulator);

    bool bSearchCmd = false;
    if (argc >= 3) {
        bSearchCmd = shellMain->Run((const char*)argv[1], argc - 2, &argv[2]);
    }

    if (bSearchCmd == false) {
        shellMain->Run();
    }
    

    return 0;
}