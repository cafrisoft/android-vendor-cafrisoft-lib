#ifndef COMM_SHELL_CMDSET_HPP__
#define COMM_SHELL_CMDSET_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/Shell/CmdItem.hpp>

namespace Comm {
    namespace Shell {

        class CmdSet : public CmdItem {
        
            protected:
                std::vector<std::shared_ptr<CmdSet>> _SubCmdSet;

            public:
                CmdSet(const char* thisCmd, const char* desc=NULL, ShellCmdRunFuncType func=NULL);

            public:
                virtual bool RunCommand(const char* cmd, int argc, const char* argv[]);
                virtual bool RunCommand(int argc, const char* argv[]);
                virtual bool PrintHelp();

                bool AddSubSet(std::shared_ptr<CmdSet> subSet);
                bool AddItem(const char* thisCmd, const char* desc, ShellCmdRunFuncType func);
                
        };


    }; //namespace Utils
}; // namespace Comm {

#endif //COMM_UTILS_PROPERTY_HPP__
