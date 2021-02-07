#ifndef CONTROLHUB_COMMANDAGENT_HPP__
#define CONTROLHUB_COMMANDAGENT_HPP__

#include "AppDefine.h"

namespace TESysControlHub {

    class CommanderAgent {
    
        CLASS_SINGLETON_PATTERN_DECLARE(CommanderAgent);

    private:
        
        /*
            CommanderAgent::Operator
                 Commnd 중계를 안정적으로 하는데 목적이 있다.
                 소켓통신 데이타 전달 방향은 한가지 경우만 있다.

                    Request  : Operator=>Hub=>Tester
                    Response : 전달된 명령에 대해 Tester는 Response보내지 않는다. 

        */

        class Operator  {
        private:
            CommanderAgent* _CommanderAgent;
            std::shared_ptr<Socket::TCP::Server> _SrvTcpSock;

        public:
            Operator(CommanderAgent* commandAgent);
            virtual ~Operator();

        private:
            static void CallbackAcceptStub(void* arg, std::shared_ptr<Socket::TCP::Client> cliSock);
            static void CallbackReceiveStub(void* arg, std::shared_ptr<Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize);
            static void CallbackCloseStub(void* arg, std::shared_ptr<Socket::TCP::Client> cliSock);

            void CallbackAccept(std::shared_ptr<Socket::TCP::Client> cliSock);
            void CallbackReceive(std::shared_ptr<Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize);
            void CallbackClose(std::shared_ptr<Socket::TCP::Client> cliSock);

        private:
            bool CmdProc_C_OH_HO_GetConnectedTesterCount(std::shared_ptr<Socket::TCP::Client> cliSock, std::shared_ptr<TESys::Net::PacketControl> reqPack);
            bool CmdProc_C_OH_RunHubCalCRC(std::shared_ptr<Socket::TCP::Client> cliSock, std::shared_ptr<TESys::Net::PacketControl> reqPack);
            //bool CmdProc_C_OH_HO_GetFileCRC(std::shared_ptr<Socket::TCP::Client> cliSock, std::shared_ptr<TESys::Net::PacketControl> reqPack);
        
        };

        /*
            CommanderAgent::Tetser
                 Commnd 중계를 안정적으로 하는데 목적이 있다.
                 소켓통신 데이타 전달 방향은 한가지 경우만 있다.

                    Request  : Operator=>Hub=>Tester
                    Response : 전달된 명령에 대해 Tester는 Response보내지 않는다. 

        */
        class Tester  {

        private:
            /************************************************************************************
                class CommanderAgent::Tester::TesterItem
            ************************************************************************************/
            class TesterItem {
            private:
                std::shared_ptr<OAL::CriticalSection> _CS;
                int _BoardID;
                int _BoardOS;
                std::shared_ptr<Socket::TCP::Client> _CliSock;
            public:
                TesterItem();

                bool Reset();
                bool IsRegister();
                bool Register(int boardID, int boardOS, std::shared_ptr<Socket::TCP::Client> cliSock);

                int GetBoardID();
                int GetBoardOS();
                int GetSocketID();
            };

            /************************************************************************************
                class CommanderAgent::Tester::TesterItemArray
            ************************************************************************************/
            class TesterItemArray {

            private:
                int _TesterItemValidCount;
                TesterItem *_TesterItem;
                std::shared_ptr<OAL::CriticalSection> _Cs;
                
            public:
                TesterItemArray();
                ~TesterItemArray();

            public:
                int GetTesterItemIndex(int boardID);
                bool AddNewTester(int boardID, int boardOS, std::shared_ptr<Socket::TCP::Client> cliSock);
                bool DeleteThisTester(std::shared_ptr<Socket::TCP::Client> cliSock);
                int GetTesterItemCount();
            };

        private:
            CommanderAgent* _CommanderAgent;
            std::shared_ptr<Socket::TCP::Server> _SrvTcpSock;
            unsigned char _RcvRawData[4096];

            std::shared_ptr<OAL::CriticalSection> _CsExtern;
            std::shared_ptr<TesterItemArray> _TesterItemArray;

        public:
            Tester(CommanderAgent* commandAgent);
            virtual ~Tester();
        
        private:
            static void CallbackAcceptStub(void* arg, std::shared_ptr<Socket::TCP::Client> cliSock);
            static void CallbackReceiveStub(void* arg, std::shared_ptr<Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize);
            static void CallbackCloseStub(void* arg, std::shared_ptr<Socket::TCP::Client> cliSock);

            void CallbackAccept(std::shared_ptr<Socket::TCP::Client> cliSock);
            void CallbackReceive(std::shared_ptr<Socket::TCP::Client> cliSock, const unsigned char* data, int dataSize);
            void CallbackClose(std::shared_ptr<Socket::TCP::Client> cliSock);
    
        private:
            void CmdProc_TH_HT_RegisterBoardID(std::shared_ptr<Socket::TCP::Client> cliSock, std::shared_ptr<TESys::Net::PacketControl> reqPack);

            //Extern 함수 
        public:
            int GetConnectedTesterCount();
            bool BroadCast(const unsigned char* data, int dataSize);

        };

    private:
        std::shared_ptr<Operator> _Operator;
        std::shared_ptr<Tester> _Tester;
    
    public:
        CommanderAgent();

    private:
        std::shared_ptr<Operator> GetOperator();
        std::shared_ptr<Tester> GetTester();

    
    };

};

#endif

