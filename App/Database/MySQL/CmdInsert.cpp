#include "Cmd.hpp"
#include <Comm/Utils/argparse.h>

namespace AppDatabaseMySQL {
    namespace Cmd {
        namespace Insert {

#if (CommOS==CommOS_WIN)
#define RAWDATA_PATH "Z:\\TESysRawData\\RawData"
#elif (CommOS==CommOS_LINUX)
#define RAWDATA_PATH "/home/hthwang/TESysRawData/RawData"
#else
#error "Select OS"
#endif

#if 0
                | adcerr | OK
                | adcexta | OK
                | adcextv | OK
                | adcldov | OK
                | adcprop | OK
                | adcregv | OK
                | adcsoutv | OK
                | cpu | OK
                | dutpcb | OK
                | hardware | OK
                | job | OK
                | joblist | OK
                | sc | OK
                | sclist | OK
                | socpcb | OK
                | software | OK
                | tc | OK
                | tclist | OK
                | tcstep | OK
                | tcsteplist | OK
                | ted | OK
                | tedlist | OK
#endif


            struct JobRawFileName {
                int ID;
                int fileCount;
                const char* fileName[8];
            };

            static struct JobRawFileName s_JobRawFileTable[] = {
                { 
                    13/*ID*/, 
                    4/*cnt*/,  
                    "JOB_0013-tesys.dataacq.rawdata-2020-11-19", 
                    "JOB_0013-tesys.dataacq.rawdata-2020-11-20",
                    "JOB_0013-tesys.dataacq.rawdata-2020-11-21", 
                    "JOB_0013-tesys.dataacq.rawdata-2020-11-22",
                },

                {   
                    14/*ID*/, 
                    4/*cnt*/,  
                    "JOB_0014-tesys.dataacq.rawdata-2020-11-23",
                    "JOB_0014-tesys.dataacq.rawdata-2020-11-24",
                    "JOB_0014-tesys.dataacq.rawdata-2020-11-25",
                    "JOB_0014-tesys.dataacq.rawdata-2020-11-26"
                },

                {
                    15/*ID*/,
                    4/*cnt*/,
                    "JOB_0015-tesys.dataacq.rawdata-2020-11-26",
                    "JOB_0015-tesys.dataacq.rawdata-2020-11-27",
                    "JOB_0015-tesys.dataacq.rawdata-2020-11-28",
                    "JOB_0015-tesys.dataacq.rawdata-2020-11-29"
                },

                {
                    16/*ID*/,
                    4/*cnt*/,
                    "JOB_0016-tesys.dataacq.rawdata-2020-11-30",
                    "JOB_0016-tesys.dataacq.rawdata-2020-12-01",
                    "JOB_0016-tesys.dataacq.rawdata-2020-12-02",
                    "JOB_0016-tesys.dataacq.rawdata-2020-12-03",
                },

                {
                    17/*ID*/,
                    4/*cnt*/,
                    "JOB_0017-tesys.dataacq.rawdata-2020-12-04",
                    "JOB_0017-tesys.dataacq.rawdata-2020-12-05",
                    "JOB_0017-tesys.dataacq.rawdata-2020-12-06",
                    "JOB_0017-tesys.dataacq.rawdata-2020-12-07",
                },

                {
                    18/*ID*/,
                    4/*cnt*/,
                    "JOB_0018-tesys.dataacq.rawdata-2020-12-07",
                    "JOB_0018-tesys.dataacq.rawdata-2020-12-08",
                    "JOB_0018-tesys.dataacq.rawdata-2020-12-09",
                    "JOB_0018-tesys.dataacq.rawdata-2020-12-10",
                },


                {
                    19/*ID*/,
                    4/*cnt*/,
                    "JOB_0019-tesys.dataacq.rawdata-2020-12-10",
                    "JOB_0019-tesys.dataacq.rawdata-2020-12-11",
                    "JOB_0019-tesys.dataacq.rawdata-2020-12-12",
                    "JOB_0019-tesys.dataacq.rawdata-2020-12-13",

                },

                {
                    20/*ID*/,
                    4/*cnt*/,
                    "JOB_0020-tesys.dataacq.rawdata-2020-12-14",
                    "JOB_0020-tesys.dataacq.rawdata-2020-12-15",
                    "JOB_0020-tesys.dataacq.rawdata-2020-12-16",
                    "JOB_0020-tesys.dataacq.rawdata-2020-12-17",
                },

                {
                    21/*ID*/,
                    4/*cnt*/,
                    "JOB_0021-tesys.dataacq.rawdata-2020-12-17",
                    "JOB_0021-tesys.dataacq.rawdata-2020-12-18",
                    "JOB_0021-tesys.dataacq.rawdata-2020-12-19",
                    "JOB_0021-tesys.dataacq.rawdata-2020-12-20",
                },


                {
                    22/*ID*/,
                    4/*cnt*/,
                    "JOB_0022-tesys.dataacq.rawdata-2020-12-21",
                    "JOB_0022-tesys.dataacq.rawdata-2020-12-22",
                    "JOB_0022-tesys.dataacq.rawdata-2020-12-23",
                    "JOB_0022-tesys.dataacq.rawdata-2020-12-24",
                },

                {
                    23/*ID*/,
                    4/*cnt*/,
                    "JOB_0023-tesys.dataacq.rawdata-2020-12-24",
                    "JOB_0023-tesys.dataacq.rawdata-2020-12-25",
                    "JOB_0023-tesys.dataacq.rawdata-2020-12-26",
                    "JOB_0023-tesys.dataacq.rawdata-2020-12-27",
                },

                {
                    24/*ID*/,
                    7/*cnt*/,
                    "JOB_0024-tesys.dataacq.rawdata-2020-12-28",
                    "JOB_0024-tesys.dataacq.rawdata-2020-12-29",
                    "JOB_0024-tesys.dataacq.rawdata-2020-12-30",
                    "JOB_0024-tesys.dataacq.rawdata-2020-12-31",
                    "JOB_0024-tesys.dataacq.rawdata-2021-01-01",
                    "JOB_0024-tesys.dataacq.rawdata-2021-01-02",
                    "JOB_0024-tesys.dataacq.rawdata-2021-01-03",
                },

                {
                    25/*ID*/,
                    2/*cnt*/,
                    "JOB_0025-tesys.dataacq.rawdata-2021-01-04",
                    "JOB_0025-JOB_0026-tesys.dataacq.rawdata-2021-01-07",
                },

                {
                    26/*ID*/,
                    2/*cnt*/,
                    "JOB_0025-JOB_0026-tesys.dataacq.rawdata-2021-01-07",
                    "JOB_0026-tesys.dataacq.rawdata-2021-01-10",
                },
            };

            static std::vector<std::string> GetJobRawFileVec(int jobID) {
                
                std::vector<std::string> vec;

                for (int i = 0; i < sizeof(s_JobRawFileTable) / sizeof(s_JobRawFileTable[0]); i++) {
            
                    struct JobRawFileName* r = &s_JobRawFileTable[i];
                    if (r->ID == jobID) {
                        for (int j = 0; j < r->fileCount; j++) {
                            std::string filePathName = RAWDATA_PATH;
                            filePathName += Comm::Property::Path::GetFilePathDelimChar();
                            filePathName += r->fileName[j];
                            vec.push_back(filePathName);
                        }
                        break;
                    }
                }

                return vec;
            }

            bool BasicTable(int argc, const char** argv) {
            
                PRINTF("TESys::DB::Single::Cpu::Generate() \n");
                TESys::DB::Single::Cpu::Generate();

                PRINTF("TESys::DB::Single::SocPcb::Generate() \n");
                TESys::DB::Single::SocPcb::Generate();

                PRINTF("TESys::DB::Single::DutPcb::Generate() \n");
                TESys::DB::Single::DutPcb::Generate();

                PRINTF("TESys::DB::Single::Hardware::Generate() \n");
                TESys::DB::Single::Hardware::Generate_1st();

                PRINTF("TESys::DB::Single::Ted::Generate() \n");
                TESys::DB::Single::Ted::Generate();

                PRINTF("TESys::DB::Single::AdcProp::Generate() \n");
                TESys::DB::Single::AdcProp::Generate();

                PRINTF("TESys::DB::Single::Software::Generate() \n");
                TESys::DB::Single::Software::Generate();

                return true;
            }

            bool RawData(int argc, const char** argv) {
                
                int jobID = -1;
                int scID = -1;
                int tcID = -1;
                
                float flt_num = 0.f;
                const char* path = NULL;
                int perms = 0;

                //#define PERM_READ  (1<<0)
                //#define PERM_WRITE (1<<1)
                //#define PERM_EXEC  (1<<2)

                static const char* const usages[] = {
                    "insert rawdata [options] [[--] args]",
                    "insert rawdata [options]",
                    NULL,
                };

                struct argparse_option options[] = {
                    OPT_HELP(),
                    OPT_GROUP("Basic options"),
                    //OPT_BOOLEAN('f', "force", &force, "force to do", NULL, 0, 0),
                    //OPT_BOOLEAN('t', "test", &test, "test only", NULL, 0, 0),
                    //OPT_STRING('p', "path", &path, "path to read", NULL, 0, 0),
                    OPT_INTEGER('j', "jobid", &jobID, "selected jobid", NULL, 0, 0),
                    OPT_INTEGER('s', "scdi", &scID, "selected scid", NULL, 0, 0),
                    OPT_INTEGER('t', "tcid", &tcID, "selected tcid", NULL, 0, 0),
                    //OPT_FLOAT('s', "float", &flt_num, "selected float", NULL, 0, 0),
                    ///OPT_GROUP("Bits options"),
                    //OPT_BIT(0, "read", &perms, "read perm", NULL, PERM_READ, OPT_NONEG),
                    //OPT_BIT(0, "write", &perms, "write perm", NULL, PERM_WRITE, 0),
                    //OPT_BIT(0, "exec", &perms, "exec perm", NULL, PERM_EXEC, 0),
                    OPT_END(),
                };

                struct argparse argparse;
                argparse_init(&argparse, options, usages, 0);
                argparse_describe(&argparse, "\ninsert rawdata to databse", "\nAdditional description of the program after the description of the arguments.");
                argc = argparse_parse(&argparse, argc, argv);

                if (jobID != -1)
                    printf("jobID: %d\n", jobID);
                if (scID != -1)
                    printf("scID: %d\n", scID);
                if (tcID != -1)
                    printf("scID: %d\n", tcID);

                if (jobID != -1) {

                    if (jobID == 9829) {

                        for (int i = 0; i < sizeof(s_JobRawFileTable) / sizeof(s_JobRawFileTable[0]); i++) {
                        
                            std::vector<std::string> vec;
                            struct JobRawFileName* r = &s_JobRawFileTable[i];

                            for (int j = 0; j < r->fileCount; j++) {
                                std::string filePathName = RAWDATA_PATH;
                                filePathName += Comm::Property::Path::GetFilePathDelimChar();
                                filePathName += r->fileName[j];
                                vec.push_back(filePathName);
                            }
                            
                            assert(r->fileCount == vec.size());
                            PRINTF("JobID=%d fileCnt=%d \n", r->ID, vec.size());
                            
                            if (r->ID >= 19) {
                                TESysDB::Insert(vec, r->ID, -1 /*scID*/, -1 /*tcID*/);
                            }
                            
                        }

                    }
                    else {
                        TESysDB::Insert(GetJobRawFileVec(jobID), jobID, scID, tcID);
                    }
                }
                else {
                    argparse_usage(&argparse);
                }
                                
                return true;
            }

        };
    };
};

