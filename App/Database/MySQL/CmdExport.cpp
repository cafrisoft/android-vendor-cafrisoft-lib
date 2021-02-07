#include "Cmd.hpp"
#include <Comm/Utils/argparse.h>

namespace AppDatabaseMySQL {
    namespace Cmd {
        namespace Export {

            bool ToCSV(int argc, const char** argv) {
                
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

                
                if (jobID != -1 && scID != -1 && tcID != -1) {
                    TESysDB::Export(jobID, scID, tcID);
                }

                
                return true;
            }

        };
    };
};

