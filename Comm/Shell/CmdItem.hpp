#ifndef COMM_SHELL_CMDITEM_HPP__
#define COMM_SHELL_CMDITEM_HPP__

#include <Comm/Base/Object.hpp>

typedef bool (*ShellCmdRunFuncType)(int argc, const char** argv);

namespace Comm {
    namespace Shell {

        class CmdItem : public Base::Object {
        
            protected:
                //struct CmdItem {
                  //  char* cmdstr;                     	// command string
                    //int (*func)(int argc, char** argv);	// execute function
                    //char* desc;    			            // descriptor
                //};

            private:
                char _ThisCmd[64];
                char _Desc[1024];
                ShellCmdRunFuncType _Func;

            protected:
                CmdItem(const char* thisCmd, const char* desc=NULL, ShellCmdRunFuncType func=NULL);

            public:
                std::string GetCmd();
                std::string GetDesc();
                virtual bool RunCommand(const char* cmd, int argc, const char* argv[]);
                virtual bool RunCommand(int argc, const char* argv[]);
                bool IsThisCommand(const char* cmd);
        };


    }; //namespace Utils
}; // namespace Comm {

#endif //COMM_UTILS_PROPERTY_HPP__
