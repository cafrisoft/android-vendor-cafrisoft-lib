#include <Comm/Shell/Main.hpp>

namespace Comm {
    namespace Shell {

        static int mme_parse_args(char* cmdline, const char** argv);

        Main::Main(const char* prompt) : CmdSet("Main"),
            _PromptStr(prompt)
        {


        };

        bool Main::Run(const char* cmd, int argc, const char* argv[]) {
        
            bool bSearchCmd = false;

            for (std::vector<std::shared_ptr<CmdSet>>::const_iterator it = _SubCmdSet.cbegin(); it != _SubCmdSet.cend(); ++it) {
                std::shared_ptr<CmdSet> p = *it;
                bSearchCmd = p->RunCommand(cmd, argc, argv);
                if (bSearchCmd) {
                    break;
                }
            }

            return bSearchCmd;
        }

        bool Main::Run(int argc, const char* argv[]) {

            bool bSearchCmd = false;
            
            for (std::vector<std::shared_ptr<CmdSet>>::const_iterator it = _SubCmdSet.cbegin(); it != _SubCmdSet.cend(); ++it) {
                std::shared_ptr<CmdSet> p = *it;
                bSearchCmd = p->RunCommand(argc, argv);
                if (bSearchCmd) {
                    break;
                }
            }

            return bSearchCmd;
        }

        bool Main::Run() {
        
            bool bSearchCmd;
            int argc;
            const char* argv[32];
            char* readBuf = new char[4096];

            while (true) {

                printf("%s>>", _PromptStr);
                fgets(readBuf, 4096, stdin);

                argc = mme_parse_args(readBuf, argv);
                if (argc > 0) {
                    bSearchCmd = false;

                    for (std::vector<std::shared_ptr<CmdSet>>::const_iterator it = _SubCmdSet.cbegin(); it != _SubCmdSet.cend(); ++it) {
                        std::shared_ptr<CmdSet> p = *it;
                        bSearchCmd = p->RunCommand((const char*)argv[0], argc - 1, &argv[1]);
                        if (bSearchCmd) {
                            printf("\n");
                            break;
                        }
                    }

                    if ((!bSearchCmd)) {

                        if (strcmp(argv[0], "exit") == 0) {
                            break;
                        }
                        else if (strcmp(argv[0], "help") == 0) {
                            this->PrintHelp();
                        }
                        else {
                            printf("\tunknown command: %s\n\r", argv[0]);
                        }
                    }
                    
                }
            }

            delete[] readBuf;

            return true;
        }

        bool Main::RunEx1() {

            bool bSearchCmd;
            int argc;
            const char* argv[32];
            char* readBuf = new char[4096];

            while (true) {

                printf("%s>>", _PromptStr);
                fgets(readBuf, 4096, stdin);

                argc = mme_parse_args(readBuf, argv);
                if (argc > 0) {
                    bSearchCmd = false;

                    for (std::vector<std::shared_ptr<CmdSet>>::const_iterator it = _SubCmdSet.cbegin(); it != _SubCmdSet.cend(); ++it) {
                        std::shared_ptr<CmdSet> p = *it;
                        bSearchCmd = p->RunCommand(argc, argv);
                        if (bSearchCmd) {
                            printf("\n");
                            break;
                        }
                    }

                    if ((!bSearchCmd)) {

                        if (strcmp(argv[0], "exit") == 0) {
                            break;
                        }
                        else if (strcmp(argv[0], "help") == 0) {
                            this->PrintHelp();
                        }
                        else {
                            printf("\tunknown command: %s\n\r", argv[0]);
                        }
                    }

                }
            }

            delete[] readBuf;

            return true;
        }

        static char* ___mme_strtok;
        static char* mme_strpbrk(char* cs, char* ct)
        {
            const char* sc1, * sc2;

            for (sc1 = cs; *sc1 != '\0'; ++sc1) {
                for (sc2 = ct; *sc2 != '\0'; ++sc2) {
                    if (*sc1 == *sc2)
                        return (char*)sc1;
                }
            }
            return 0;
        }

        static char* mme_strtok(char* s, const char* ct)
        {
            char* sbegin, * send;

            sbegin = s ? s : ___mme_strtok;
            if (!sbegin) {
                return 0;
            }
            sbegin += strspn(sbegin, ct);
            if (*sbegin == '\0') {
                ___mme_strtok = 0;
                return(0);
            }
            send = mme_strpbrk(sbegin, (char*)ct);
            if (send && *send != '\0')
                *send++ = '\0';
            ___mme_strtok = send;
            return (sbegin);
        }


        static const char* mme_delim = " \f\n\r\t\v";
        static int mme_parse_args(char* cmdline, const char** argv)
        {
            char* tok;
            int argc = 0;

            argv[argc] = 0;

            for (tok = mme_strtok(cmdline, mme_delim); tok; tok = mme_strtok(0, mme_delim))
            {
                argv[argc++] = tok;
            }

            return argc;
        }

    };
};