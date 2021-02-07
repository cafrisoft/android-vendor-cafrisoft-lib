#ifndef COMM_SHELL_MAIN_HPP__
#define COMM_SHELL_MAIN_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/Shell/CmdSet.hpp>

namespace Comm {
    namespace Shell {

        class Main : public CmdSet {

        private:
            const char* _PromptStr;

        public:
            Main(const char* prompt);

            bool Run(const char* cmd, int argc, const char* argv[]);
            bool Run(int argc, const char* argv[]);
            bool Run();
            bool RunEx1();
        };


    }; //namespace Utils
}; // namespace Comm {

#endif //COMM_UTILS_PROPERTY_HPP__
