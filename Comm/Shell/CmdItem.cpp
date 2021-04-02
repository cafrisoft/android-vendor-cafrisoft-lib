#include <Comm/Global/BuildOptions.h>
#include <Comm/Shell/CmdItem.hpp>

namespace Comm {
    namespace Shell {

        CmdItem::CmdItem(const char* thisCmd, const char* desc, ShellCmdRunFuncType func) {
        
            assert(_ThisCmd);
            strcpy(_ThisCmd, thisCmd);

            if (desc != NULL) {
                strcpy(_Desc, desc);
            }
            else {
                strcpy(_Desc, "");
            }

            _Func = func;
        }

        std::string CmdItem::GetCmd() {
            std::string str = _ThisCmd;
            return str;
        }

        std::string CmdItem::GetDesc() {
            std::string str = _Desc;
            return str;
        }

        bool CmdItem::IsThisCommand(const char* cmd) {
        
            bool bRet = false;
            if (strcmp(cmd, _ThisCmd) == 0) {
                bRet = true;
            }
            return bRet;
        }

        bool CmdItem::RunCommand(const char* cmd, int argc, const char* argv[]) {
        
            bool bRet = false;

            if (this->IsThisCommand(cmd)) {
            
                if (_Func) {
                    (*_Func)(argc, argv);
                }
                
                bRet = true;
                
            }

            return bRet;
        }

        bool CmdItem::RunCommand(int argc, const char* argv[]) {

            bool bRet = false;
            const char* cmd = argv[0];

            if (this->IsThisCommand(cmd)) {

                if (_Func) {
                    (*_Func)(argc, argv);
                }

                bRet = true;

            }

            return bRet;
        }
    };
};
