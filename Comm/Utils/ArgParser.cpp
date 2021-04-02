#include <Comm/Global/BuildOptions.h>
#include <Comm/Utils/argparse.h>
#include <Comm/Utils/ArgParser.hpp>

#define INVALID_INT_VALUE -99999999

namespace Comm {
    namespace Utils {
        namespace ArgParser {

            bool GetValue(int argc, const char** argv, int* retInt0, const char* parName) {
            
                int ivalue = INVALID_INT_VALUE;
                const char* const usages[] = {
                    "-y2021 -m2 -d22 -s5930 -r5",
                    "--year=2021 --month=2 --day=22 --stockcode=5930 --dur=5",
                    NULL,
                };
                struct argparse_option options[] = {
                    OPT_HELP(),
                    OPT_GROUP("Basic options"),
                    OPT_INTEGER(parName[0], parName, &ivalue, "selected par", NULL, 0, 0),
                    OPT_END(),
                };
                struct argparse argparse;
                argparse_init(&argparse, options, usages, 0);
                argparse_describe(&argparse, "\nsend txt kiwoom data to StockHub", "\nAdditional description of the program after the description of the arguments.");
                argc = argparse_parse(&argparse, argc, argv);

                if (retInt0) *retInt0 = ivalue;

                return true;
            }

            bool GetValue(int argc, const char** argv, const char* parName, bool* retValue, bool defaultValue) {

                bool bRet;
                int ivalue = INVALID_INT_VALUE;
                bool bValue;
                const char* const usages[] = {
                    "-y2021 -m2 -d22 -s5930 -r5",
                    "--year=2021 --month=2 --day=22 --stockcode=5930 --dur=5",
                    NULL,
                };
                struct argparse_option options[] = {
                    OPT_HELP(),
                    OPT_GROUP("Basic options"),
                    OPT_INTEGER(parName[0], parName, &ivalue, "selected par", NULL, 0, 0),
                    OPT_END(),
                };
                struct argparse argparse;
                argparse_init(&argparse, options, usages, 0);
                argparse_describe(&argparse, "\nsend txt kiwoom data to StockHub", "\nAdditional description of the program after the description of the arguments.");
                argc = argparse_parse(&argparse, argc, argv);

                if (ivalue == INVALID_INT_VALUE) {
                    bRet = false;
                    bValue = defaultValue;
                }
                else {
                    bRet = true;
                    bValue = ivalue ? true : false;
                }

                if (retValue) *retValue = bValue;

                return bRet;
            }




        }; //namespace ArgParser
    };//namespace Utils
};//namespace Comm
