#include <Comm/Global/BuildOptions.h>
#include <Comm/Shell/CmdSet.hpp>

namespace Comm {
    namespace Shell {

        CmdSet::CmdSet(const char* thisCmd, const char* desc, ShellCmdRunFuncType func) :
            CmdItem(thisCmd, desc, func)
        {
            
        }
        
        bool CmdSet::AddSubSet(std::shared_ptr<CmdSet> subSet) {
        
            this->_SubCmdSet.push_back(subSet);
            return true;
        }

        bool CmdSet::AddItem(const char* thisCmd, const char* desc, ShellCmdRunFuncType func) {
            std::shared_ptr<CmdSet> cmdSubSet = std::make_shared<CmdSet>(thisCmd, desc, func);
            return this->AddSubSet(cmdSubSet);
        }

        bool CmdSet::RunCommand(const char* cmd, int argc, const char* argv[]) {
        
            bool isSearch = false;
            
            if ( _SubCmdSet.size() > 0   ) {
            
                if(this->IsThisCommand(cmd)) {

                    if (argc >= 1) {

                        for (std::vector<std::shared_ptr<CmdSet>>::const_iterator it = _SubCmdSet.cbegin(); it != _SubCmdSet.cend(); ++it) {

                            std::shared_ptr<CmdSet> p = *it;
                            isSearch = p->RunCommand(argv[0], argc - 1, &argv[1]);
                            if (isSearch) {
                                break;
                            }
                        }
                    }
                    else {
                        this->PrintHelp();
                    }

                    isSearch = true;
                }
            }
            else {
                isSearch = CmdItem::RunCommand(cmd, argc, argv);
            }
            
            return isSearch;
        }

        bool CmdSet::RunCommand(int argc, const char* argv[]) {

            bool isSearch = false;
            const char* cmd = argv[0];

            if (_SubCmdSet.size() > 0) {

                if (this->IsThisCommand(cmd)) {

                    if (argc > 1) {

                        for (std::vector<std::shared_ptr<CmdSet>>::const_iterator it = _SubCmdSet.cbegin(); it != _SubCmdSet.cend(); ++it) {

                            std::shared_ptr<CmdSet> p = *it;
                            isSearch = p->RunCommand(argc - 1, &argv[1]);
                            if (isSearch) {
                                break;
                            }
                        }
                    }
                    else {
                        this->PrintHelp();
                    }

                    isSearch = true;
                }
            }
            else {
                isSearch = CmdItem::RunCommand(argc, argv);
            }

            return isSearch;
        }
        bool CmdSet::PrintHelp() {
        
            printf("------------ %s ------------\n", this->GetCmd().c_str());
            for (std::vector<std::shared_ptr<CmdSet>>::const_iterator it = _SubCmdSet.cbegin(); it != _SubCmdSet.cend(); ++it) {
                std::shared_ptr<CmdSet> p = *it;
                printf("%s : %s\n", p->GetCmd().c_str(), p->GetDesc().c_str());
            }
            printf("\n");

            return true;
        }
    };
};