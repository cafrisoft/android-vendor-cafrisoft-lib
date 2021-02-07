#include "AppDefine.hpp"
#include "Cmd.hpp"
#include <TESys/DB/Single/Job.hpp>

using namespace AppDatabaseMySQL;


static bool ArgParsingExample(int argc, const char** argv) {

    printf("argument parsing example\n");

    int force = 0;
    int test = 0;
    int int_num = 0;
    float flt_num = 0.f;
    const char* path = NULL;
    int perms = 0;

#define PERM_READ  (1<<0)
#define PERM_WRITE (1<<1)
#define PERM_EXEC  (1<<2)


    static const char* const usages[] = {
        "test_argparse [options] [[--] args]",
        "test_argparse [options]",
        NULL,
    };

    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BOOLEAN('f', "force", &force, "force to do", NULL, 0, 0),
        OPT_BOOLEAN('t', "test", &test, "test only", NULL, 0, 0),
        OPT_STRING('p', "path", &path, "path to read", NULL, 0, 0),
        OPT_INTEGER('i', "int", &int_num, "selected integer", NULL, 0, 0),
        OPT_FLOAT('s', "float", &flt_num, "selected float", NULL, 0, 0),
        OPT_GROUP("Bits options"),
        OPT_BIT(0, "read", &perms, "read perm", NULL, PERM_READ, OPT_NONEG),
        OPT_BIT(0, "write", &perms, "write perm", NULL, PERM_WRITE, 0),
        OPT_BIT(0, "exec", &perms, "exec perm", NULL, PERM_EXEC, 0),
        OPT_END(),
    };

    struct argparse argparse;
    argparse_init(&argparse, options, usages, 0);
    argparse_describe(&argparse, "\nA brief description of what the program does and how it works.", "\nAdditional description of the program after the description of the arguments.");
    argc = argparse_parse(&argparse, argc, argv);

    if (force != 0)
        printf("force: %d\n", force);
    if (test != 0)
        printf("test: %d\n", test);
    if (path != NULL)
        printf("path: %s\n", path);
    if (int_num != 0)
        printf("int_num: %d\n", int_num);
    if (flt_num != 0)
        printf("flt_num: %g\n", flt_num);
    if (argc != 0) {
        printf("argc: %d\n", argc);
        int i;
        for (i = 0; i < argc; i++) {
            printf("argv[%d]: %s\n", i, *(argv + i));
        }
    }
    if (perms) {
        printf("perms: %d\n", perms);
    }
    return true;
}


int main(int argc, const char* argv[]) {
    
    Comm::OAL::Log::SysLogOpen(CLOG_TAG);
    Comm::OAL::Log::EnableDebug();

    TESysDB::Connect();

    //CmdSet Test
    std::shared_ptr<Comm::Shell::CmdSet> cmdTest = std::make_shared<Comm::Shell::CmdSet>("test", "test functions");
    assert(cmdTest);
    cmdTest->AddItem("argparsingexam", "argument parsing example", ArgParsingExample);

    //CmdSet Insert
    std::shared_ptr<Comm::Shell::CmdSet> cmdInsert = std::make_shared<Comm::Shell::CmdSet>("insert", "insert functions");
    assert(cmdInsert);
    cmdInsert->AddItem("basic", "basic", Cmd::Insert::BasicTable);
    cmdInsert->AddItem("rawdata", "insert rawdata to database", Cmd::Insert::RawData);
    
    //CmdSet Export
    std::shared_ptr<Comm::Shell::CmdSet> cmdExport = std::make_shared<Comm::Shell::CmdSet>("export", "export functions");
    assert(cmdExport);
    cmdExport->AddItem("csv", "export to CSV", Cmd::Export::ToCSV);

    //CmdSet Verify
    std::shared_ptr<Comm::Shell::CmdSet> cmdVerify = std::make_shared<Comm::Shell::CmdSet>("verify", "verify functions");
    assert(cmdVerify);
    cmdVerify->AddItem("csv", "verify with exported csv", Cmd::Verify::CSV);

    //CmdSet Main
    std::shared_ptr<Comm::Shell::Main> shellMain = std::make_shared<Comm::Shell::Main>("TESysDB");
    assert(shellMain);

    shellMain->AddSubSet(cmdTest);
    shellMain->AddSubSet(cmdInsert);
    shellMain->AddSubSet(cmdExport);
    shellMain->AddSubSet(cmdVerify);

    bool bSearchCmd = false;
    if (argc >= 3) {
        bSearchCmd = shellMain->Run(argc - 1, &argv[1]);
    }

    if (bSearchCmd == false) {
        shellMain->RunEx1();
    }

    TESysDB::Disconnect();


    Comm::OAL::Log::SysLogClose();

    return 0;
}

int main_test(int argc, char* argv[]) {

    Comm::OAL::Log::SysLogOpen(CLOG_TAG);
    Comm::OAL::Log::EnableDebug();

    //std::string configPathFileName = TESys::Property::Path::ControlShell::GetConfigRoot();
    //configPathFileName += Comm::Property::Path::GetFilePathDelimChar();
    //configPathFileName += "Export_RawDBFileVector.txt";

#if (CommOS==CommOS_WIN)

    std::vector<std::string> rawDBFileVector = {
                 "C:\\MyTESys\\opt\\TESys\\DataAcq\\BackupRawData\\JOB_0013-tesys.dataacq.rawdata-2020-11-19",
                 "C:\\MyTESys\\opt\\TESys\\DataAcq\\BackupRawData\\JOB_0013-tesys.dataacq.rawdata-2020-11-20",
                 "C:\\MyTESys\\opt\\TESys\\DataAcq\\BackupRawData\\JOB_0013-tesys.dataacq.rawdata-2020-11-21",
                 "C:\\MyTESys\\opt\\TESys\\DataAcq\\BackupRawData\\JOB_0013-tesys.dataacq.rawdata-2020-11-22",
    };

#elif (CommOS==CommOS_LINUX)
    std::vector<std::string> rawDBFileVector = {
                 "/home/hthwang/TESysRawData/RawData/JOB_0013-tesys.dataacq.rawdata-2020-11-19",
                 "/home/hthwang/TESysRawData/RawData/JOB_0013-tesys.dataacq.rawdata-2020-11-20",
                 "/home/hthwang/TESysRawData/RawData/JOB_0013-tesys.dataacq.rawdata-2020-11-21",
                 "/home/hthwang/TESysRawData/RawData/JOB_0013-tesys.dataacq.rawdata-2020-11-22",
    };
#endif

    

    //std::shared_ptr<TESys::DB::Single::Job> tableJob = std::make_shared< TESys::DB::Single::Job>(mysql);
    //int jobID = tableJob->GetID(13);
    //PRINTF("jobid=%d \n", jobID);

    //MySQLConnect();

 
    
    //InsertMain(rawDBFileVector);

    //MySQLDisconnect();

    
    Comm::OAL::Log::SysLogClose();
    
    return 0;
}
