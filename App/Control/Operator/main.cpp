#include "App.hpp"
#include "Cmd.hpp"
#include "TesterStatus.hpp"
#include <TESys/Property/Tester.hpp>

using namespace Comm;
using namespace TESysOperator;

#define EXTRA_BOARD_COUNT 12
const int c_extra_board_id[EXTRA_BOARD_COUNT] = {
    1, 19, 20, 31, 32,
    36, 38, 40, 41, 56,
    48, 54
};

int GetExtraBoardCount() {
    return EXTRA_BOARD_COUNT;
}

std::vector<int> GetExtraBoardID() {

    std::vector<int> vec;

    for (int i = 0; i < EXTRA_BOARD_COUNT; i++) {
        vec.push_back(c_extra_board_id[i]);
    }

    return vec;
}


static bool CmdInfo(int argc, char* argv[]) {

    int connectedTesterCount;
    //bool bRet;

    if (!App::Oper()->IsConnect()) {
        printf("ERROR : Disconnect Status \n");
        return false;
    }

    connectedTesterCount = App::Oper()->QueryConnectedTesterCount();
    printf("Tester Count (Hub) : %d \n", connectedTesterCount);

    connectedTesterCount = App::Oper()->GetConnectedTesterCount();
    printf("Tester Count (Internal) : %d \n", connectedTesterCount);

    
    return true;
}

static bool CmdRunPythonSC(int argc, char* argv[]) {


    if (!App::Oper()->IsConnect()) {
        printf("ERROR : Disconnect Status \n");
        return false;
    }

    App::Oper()->C_OHT_RunPythonSC(TESys::Property::Tester::Board::GetGeneralID(), 0 /*scNo*/);

    return true;
}

static bool CmdRunPythonJOB(int argc, char* argv[]) {

    if (!App::Oper()->IsConnect()) {
        printf("ERROR : Disconnect Status \n");
        return false;
    }

    App::Oper()->C_OHT_RunPythonJOB(TESys::Property::Tester::Board::GetGeneralID(), 0 /*jobNo*/);

    return true;
}


static bool CmdDataAcqCheckDB(int argc, char* argv[]) {

    std::shared_ptr<TESys::Data::DataAcqDB> db = TESys::Data::DataAcqDB::CreateObject(TESys::Data::DataAcqDB::ID::Raw);
    //db->ExportCSV("d:\\work", Comm::OAL::DateTime::GetUtcTime_KST(2020, 9, 21, 0, 0, 0), Comm::OAL::DateTime::GetUtcTime());
    //db->ExportCSV(101/*BoardID*/, 0 /*DutIdx*/, "d:\\work", Comm::OAL::DateTime::GetUtcTime_KST(2020, 9, 21, 0, 0, 0), Comm::OAL::DateTime::GetUtcTime());

    return true;
}



static bool CmdAging(int argc, char* argv[]) {

    
    if (!App::Oper()->IsConnect()) {
        printf("ERROR : Disconnect Status \n");
        return false;
    }

    while (true) {
        App::Oper()->C_OHT_RunPythonJOB(TESys::Property::Tester::Board::GetGeneralID(), 0 /*jobNo*/);
        Comm::OAL::Thread::Sleep(1000 * 10);
    }


    return true;
}


int main(int argc, char* argv[]) {

    assert(sizeof(struct TESys::Data::Status::Tester) <= TESys::Net::PacketControl::GetMaxDataByteSize());

    Comm::OAL::Log::SysLogOpen(CLOG_TAG);
    Comm::OAL::Log::EnableDebug();
    Comm::OAL::Log::DisableOutDevice(Comm::OAL::Log::OutDevice::Console);

    App::Init();

    //CmdSet Tester
    std::shared_ptr<Shell::CmdSet> cmdSetTesterStatus = std::make_shared<Shell::CmdSet>("tester", "testerstatus");
    assert(cmdSetTesterStatus);
    cmdSetTesterStatus->AddItem("test1", "test1 function", Cmd::Tester::Test1);
    cmdSetTesterStatus->AddItem("status", "display tester status", Cmd::Tester::DisplayStatus);
    cmdSetTesterStatus->AddItem("fwupgrade", "send fwupgrade command", Cmd::Tester::FWUpgrade);
    cmdSetTesterStatus->AddItem("reboot", "reboot", Cmd::Tester::Reboot);
    cmdSetTesterStatus->AddItem("shutdown", "reboot", Cmd::Tester::Shutdown);
    cmdSetTesterStatus->AddItem("tc", "run tc", Cmd::Tester::RunTC);
    cmdSetTesterStatus->AddItem("job", "run job", Cmd::Tester::RunJOB);
    cmdSetTesterStatus->AddItem("filesync", "filesync", Cmd::Tester::FileSync);
    cmdSetTesterStatus->AddItem("flashwriter", "run flashwriter", Cmd::Tester::FlashWriter);
    cmdSetTesterStatus->AddItem("flashws", "display flashwriter status", Cmd::Tester::GetFlashWriterError);
    cmdSetTesterStatus->AddItem("adbtesysupgrade", "run tesys upgrade via ADB", Cmd::Tester::RunAdbTEsysUpgrade);
    cmdSetTesterStatus->AddItem("killtesystester", "kill TESys Tester", Cmd::Tester::KillTESysTester);
    cmdSetTesterStatus->AddItem("killpy", "kill TESys Tester", Cmd::Tester::KillPython);
    cmdSetTesterStatus->AddItem("pypid", "display python pid", Cmd::Tester::PythonPID);
    cmdSetTesterStatus->AddItem("linuxcmd1", "linuxcmd , no respose", Cmd::Tester::SendLinuxCommand);
    cmdSetTesterStatus->AddItem("linuxcmd2", "linuxcmd with respose", Cmd::Tester::SendLinuxCommandWithResponse);
    
    //CmdSet TED
    std::shared_ptr<Shell::CmdSet> cmdSetTED = std::make_shared<Shell::CmdSet>("ted", "ted");
    assert(cmdSetTED);
    cmdSetTED->AddItem("hs1_120hz", "hs1_120hz", Cmd::TED::FrameRate_HS1_120Hz);
    cmdSetTED->AddItem("normal_60hz", "normal_60hz", Cmd::TED::FrameRate_Normal_60Hz);
    cmdSetTED->AddItem("hlpm_on", "hlpm_on", Cmd::TED::FrameRate_HLPM_ON);
    cmdSetTED->AddItem("hlpm_off", "hlpm_off", Cmd::TED::FrameRate_HLPM_OFF);
    cmdSetTED->AddItem("te_time", "te_time", Cmd::TED::FrameRate_TE_Time);
    cmdSetTED->AddItem("dd_fb_blank_1", "enter to DD Black Mode(Display Off)", Cmd::TED::DD_FB_Blank_Enter);
    cmdSetTED->AddItem("dd_fb_blank_0", "leave to DD Black Mode(Display Off)", Cmd::TED::DD_FB_Blank_Leave);
    cmdSetTED->AddItem("ptrn_red", "patterndraw app write RED", Cmd::TED::PatternDrawRed);
    cmdSetTED->AddItem("ptrn_green", "patterndraw app write Green", Cmd::TED::PatternDrawGreen);
    cmdSetTED->AddItem("ptrn_blue", "patterndraw app write Blue", Cmd::TED::PatternDrawBlue);
    cmdSetTED->AddItem("ptrn_white", "patterndraw app write WHITE", Cmd::TED::PatternDrawWhite);
    cmdSetTED->AddItem("ptrn_black", "patterndraw app write BLACK", Cmd::TED::PatternDrawBlack);
    cmdSetTED->AddItem("flashwriter", "flash image write", Cmd::TED::FlashWriter);
    //cmdSetTED->AddItem("flashverify", "flash image verify", Cmd::TED::FlashVerify);
    //cmdSetTED->AddItem("adcregvreg1", "ADC Reg VREG1 Verify", Cmd::TED::AdcRegVREG1);

    //CmdSet TED
    std::shared_ptr<Shell::CmdSet> cmdSetVerify = std::make_shared<Shell::CmdSet>("verify", "verify ted");
    assert(cmdSetVerify);
    cmdSetVerify->AddItem("chipid", "read chipid", Cmd::Verify::ChipID);
    cmdSetVerify->AddItem("flash", "TED Flash writer verify", Cmd::Verify::Flash);
    cmdSetVerify->AddItem("patternapp", "Pattern DrawApp Verify", Cmd::Verify::PatternApp);
    cmdSetVerify->AddItem("adcregvreg1", "adc regulator VREG1", Cmd::Verify::AdcRegulatorVREG1);
    cmdSetVerify->AddItem("adc_static_current", "adc static current", Cmd::Verify::AdcStaticCurrent);



    //CmdSet Hub
    std::shared_ptr<Shell::CmdSet> cmdSetHubStatus = std::make_shared<Shell::CmdSet>("hub", "hubstatus");
    assert(cmdSetHubStatus);
    cmdSetHubStatus->AddItem("status", "display tester status", Cmd::Hub::DisplayStatus);


    //CmdSet FileSync
    std::shared_ptr<Shell::CmdSet> cmdSetFileSync = std::make_shared<Shell::CmdSet>("filesync", "filesync");
    assert(cmdSetFileSync);
    cmdSetFileSync->AddItem("run_filesync", "filesync app run", Cmd::FileSync::RunFileSync);
    cmdSetFileSync->AddItem("run_hubcalcrc", "filesync app run", Cmd::FileSync::RunHubCalCRC);
    cmdSetFileSync->AddItem("dir_python", "filesync app run", Cmd::FileSync::DirAgingPythonFile);

    //Shell Main
    std::shared_ptr<Comm::Shell::Main> shellMain = std::make_shared<Comm::Shell::Main>("oper");

    //shellMain->AddItem("info", "disconnect from control hub", CmdInfo);
    //shellMain->AddItem("sc", "Run SC", CmdRunPythonSC);
    //shellMain->AddItem("job", "Run JOB", CmdRunPythonJOB);
    //shellMain->AddItem("status", "Run JOB", CmdDisplayStatus);
    //shellMain->AddItem("export", "Exporyt DataAcqRawData ", CmdDataAcqRawDataExport);
    //shellMain->AddItem("chkdb", "chkdb ", CmdDataAcqCheckDB);
    //shellMain->AddItem("aging", "aging ", CmdAging);
    shellMain->AddItem("stat", "Display Tester Status", Cmd::Tester::DisplayStatus);
    
    shellMain->AddSubSet(cmdSetHubStatus);
    shellMain->AddSubSet(cmdSetTesterStatus);
    shellMain->AddSubSet(cmdSetTED);
    shellMain->AddSubSet(cmdSetVerify);
    shellMain->AddSubSet(cmdSetFileSync);

    shellMain->Run();

    CLOGD("");
    App::Deinit();

    CLOGD("");
    Comm::OAL::Log::SysLogClose();

    CLOGD("");
}


