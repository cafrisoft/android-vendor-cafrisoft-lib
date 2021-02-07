#include "App.hpp"
#include "Cmd.hpp"
#include <TESys/Property/Tester.hpp>

namespace TESysOperator {
    namespace Cmd {

        bool Tester::DisplayStatus(int argc, const char** argv) {
        
            int boardID;
            printf("<<Tester Status>>\n");

            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            if (argc == 0) {
                boardID = TESys::Property::Tester::Board::GetGeneralID();
            }
            else if (argc == 1) {
                boardID = atoi(argv[0]);
            }
            else {
                printf("ERROR : argument error \n");
                printf("\t ex1) #tester status     ## boardID=GeneralID \n");
                printf("\t ex2) #tester status 30  ## boardID=30        \n");
                return false;
            }

            if (boardID == TESys::Property::Tester::Board::GetGeneralID()) {
                printf("BoardID=%d (General ID) \n", boardID);
            }
            else {
                printf("BoardID=%d \n", boardID);
            }

            App::Inst()->TesterStatus()->DisplayStatus(boardID);

            return true;
        }
        
        bool Tester::FWUpgrade(int argc, const char** argv) {

            int boardID;
            printf("<<FWUpgrade>>\n");

            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            if (argc == 0) {
                boardID = TESys::Property::Tester::Board::GetGeneralID();
            }
            else if (argc == 1) {
                boardID = atoi(argv[0]);
            }
            else {
                printf("ERROR : argument error \n");
                printf("\t ex1) #tester fwupgrade     ## boardID=GeneralID \n");
                printf("\t ex2) #tester fwupgrade 30  ## boardID=30        \n");
                return false;
            }

            if (boardID == TESys::Property::Tester::Board::GetGeneralID()) {
                printf("BoardID=%d (General ID) \n", boardID);
            }
            else {
                printf("BoardID=%d \n", boardID);
            }

            App::Oper()->C_OHT_RunFWUpgrade(boardID);

            return true;
        }

        bool Tester::Reboot(int argc, const char** argv) {

            int boardID;

            printf("<<FileSync>>\n");

            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            if (argc == 0) {
                boardID = TESys::Property::Tester::Board::GetGeneralID();
            }
            else if (argc == 1) {
                boardID = atoi(argv[0]);
            }
            else {
                printf("ERROR : argument error \n");
                printf("\t ex1) #tester reboot     ## boardID=GeneralID\n");
                printf("\t ex2) #tester reboot 30  ## boardID=30       \n");
                return false;
            }

            if (boardID == TESys::Property::Tester::Board::GetGeneralID()) {
                printf("BoardID=%d (General ID) \n", boardID);
            }
            else {
                printf("BoardID=%d \n", boardID);
            }

            App::Oper()->C_OHT_Reboot(boardID);

            return true;
        }

        bool Tester::Shutdown(int argc, const char** argv) {

            int boardID;

            printf("<<Shutdown>>\n");

            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            if (argc == 0) {
                boardID = TESys::Property::Tester::Board::GetGeneralID();
            }
            else if (argc == 1) {
                boardID = atoi(argv[0]);
            }
            else {
                printf("ERROR : argument error \n");
                printf("\t ex1) #tester shutdown     ## boardID=GeneralID\n");
                printf("\t ex2) #tester shutdown 30  ## boardID=30       \n");
                return false;
            }

            if (boardID == TESys::Property::Tester::Board::GetGeneralID()) {
                printf("BoardID=%d (General ID) \n", boardID);
            }
            else {
                printf("BoardID=%d \n", boardID);
            }

            App::Oper()->C_OHT_Shutdown(boardID);

            return true;
        }

        bool Tester::RunTC(int argc, const char** argv) {

            int boardID;
            int tcID;

            printf("<<RunTC >>\n");

            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            if (argc == 1) {
            
                boardID = TESys::Property::Tester::Board::GetGeneralID();
                tcID = atoi(argv[0]);
            }
            else if (argc == 2) {
                
                boardID = atoi(argv[0]);
                tcID = atoi(argv[1]);
            }
            else {
                printf("ERROR : argument error \n");
                printf("\t ex1) #tester tc 1 2  ## boardID=1  tcID=2\n");
                printf("\t ex1) #tester tc 3    ## tcID=3\n");
                return false;
            }

            if (boardID == TESys::Property::Tester::Board::GetGeneralID()) {
                printf("BoardID=%d (General ID) \n", boardID);
            }
            else {
                printf("BoardID=%d \n", boardID);
            }
            printf("TC_ID=%d \n", tcID);

            //App::Oper()->C_OHT_Reboot();

            App::Oper()->C_OHT_RunPythonTC(boardID, tcID);

            return true;
        }

        bool Tester::RunJOB(int argc, const char** argv) {

            int boardID;
            int jobID;

            printf("<<RunJOB>>\n");

            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            if (argc == 1) {

                boardID = TESys::Property::Tester::Board::GetGeneralID();
                jobID = atoi(argv[0]);
            }
            else if (argc == 2) {

                boardID = atoi(argv[0]);
                jobID = atoi(argv[1]);
            }
            else {
                printf("ERROR : argument error \n");
                printf("\t ex1) #tester job 1 2  ## boardID=1  jobID=2\n");
                printf("\t ex2) #tester job 3    ## jobID=3\n");
                printf("\t ex2) #tester job %d 3 ## boardID=ExtraID jobID=3\n", TESys::Property::Tester::Board::GetExtraID());
                return false;
            }

            if (boardID == TESys::Property::Tester::Board::GetGeneralID()) {
                printf("BoardID=%d (General ID) \n", boardID);
            }
            else if (boardID == TESys::Property::Tester::Board::GetExtraID()) {
                printf("BoardID=%d (Extra ID) \n", boardID);
            }
            else {
                printf("BoardID=%d \n", boardID);
            }
            printf("JOB_ID=%d \n", jobID);

            //App::Oper()->C_OHT_Reboot();


            if (boardID == TESys::Property::Tester::Board::GetExtraID()) {

                std::vector<int> vecBoardID = GetExtraBoardID();

                printf("Extra Board Count : %lld \n", vecBoardID.size());

                for (std::vector<int>::const_iterator it = vecBoardID.cbegin();
                    it != vecBoardID.cend();
                    it++) {

                    int bid = *it;

                    PRINTF("BoardID=%d Run Job_%d\n", bid, jobID);
                    App::Oper()->C_OHT_RunPythonJOB(bid, jobID);
                }
            }
            else {
                App::Oper()->C_OHT_RunPythonJOB(boardID, jobID);
            }

            return true;
        }

        bool Tester::FileSync(int argc, const char** argv) {

            int boardID;
            
            printf("<<FileSync>>\n");

            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            if (argc == 0) {
                boardID = TESys::Property::Tester::Board::GetGeneralID();
            }
            else if (argc == 1) {
                boardID = atoi(argv[0]);
            }
            else {
                printf("ERROR : argument error \n");
                printf("\t ex1) #tester filesync     ## boardID=GeneralID\n");
                printf("\t ex2) #tester fileSync 30  ## boardID=30       \n");
                printf("\t ex3) #tester filesync %d  ## boardID=ExtraID\n", TESys::Property::Tester::Board::GetExtraID());
                return false;
            }

            if (boardID == TESys::Property::Tester::Board::GetGeneralID()) {
                printf("BoardID=%d (General ID) \n", boardID);
            }
            else if (boardID == TESys::Property::Tester::Board::GetExtraID()) {
                printf("BoardID=%d (Extra ID) \n", boardID);
            }
            else {
                printf("BoardID=%d \n", boardID);
            }
            
            App::Oper()->C_OH_RunHubCalCRC();

            if (boardID == TESys::Property::Tester::Board::GetExtraID()) {

                std::vector<int> vecBoardID = GetExtraBoardID();

                printf("Extra Board Count : %lld \n", vecBoardID.size());

                for (std::vector<int>::const_iterator it = vecBoardID.cbegin();
                    it != vecBoardID.cend();
                    it++) {

                    int bid = *it;
                    App::Oper()->C_OHT_RunFileSync(bid);
                    printf("Run Filesync send command BoardID=%d \n", bid);
                }
            }
            else {
                App::Oper()->C_OHT_RunFileSync(boardID);
            }

            return true;
        }

        bool Tester::FlashWriter(int argc, const char** argv) {

            int boardID;

            printf("<<FlashWriter>>\n");

            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            if (argc == 0) {
                boardID = TESys::Property::Tester::Board::GetGeneralID();
            }
            else if (argc == 1) {
                boardID = atoi(argv[0]);
            }
            else {
                printf("ERROR : argument error \n");
                printf("\t ex1) #tester flashwriter     ## boardID=GeneralID\n");
                printf("\t ex2) #tester flashwriter 30  ## boardID=30       \n");
                return false;
            }

            if (boardID == TESys::Property::Tester::Board::GetGeneralID()) {
                printf("BoardID=%d (General ID) \n", boardID);
            }
            else {
                printf("BoardID=%d \n", boardID);
            }

            App::Oper()->C_OHT_RunFlashWriter(boardID);

            return true;
        }

        bool Tester::GetFlashWriterError(int argc, const char** argv) {
        
            int boardID;

            printf("<<GetFlashWriterError>>\n");

            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            if (argc == 1) {
                boardID = atoi(argv[0]);
            }
            else {
                printf("ERROR : argument error \n");
                printf("\t ex2) #tester flashws 30  ## boardID=30 \n");
                return false;
            }
            
            printf("BoardID=%d \n", boardID);

            App::Oper()->C_OHT_THO_GetSystemFlashWriteError(boardID);

            return true;
        }

        bool Tester::Test1(int argc, const char** argv) {
        
            void* dcHdl =  App::Inst()->Oper()->DataConsumerTesterStatusCreate();
            unsigned int startTick = Comm::OAL::System::GetTickCount32();
            unsigned int curTick;
            TESys::API::PacketTesterStatusArray packetTesterArray;
            int rcvStatusCnt = 0;

            while(true) {

                App::Inst()->Oper()->DataConsumerTesterStatusGetApiData(dcHdl, &packetTesterArray);
                
                //PRINTF("QueueCnt = %d \n", App::Inst()->Oper()->DataConsumerTesterStatusQueueCount(dcHdl) );

                if (packetTesterArray._ArrayCount > 0) {

                    rcvStatusCnt += packetTesterArray._ArrayCount;
                    PRINTF("statusPackCnt = %d  rcvStatusCnt=%d \n", packetTesterArray._ArrayCount, rcvStatusCnt);

                    for (int i = 0; i < packetTesterArray._ArrayCount; i++) {
                        
                        struct TESys::Data::Status::Tester *pTstr = &packetTesterArray._TesterStatus[i];

                        PRINTF("BoardID=%d  QueuCnt=%d\n", pTstr->Board.BoardID, App::Inst()->Oper()->DataConsumerTesterStatusQueueCount(dcHdl));
                    }

                    
                }
            
                curTick = Comm::OAL::System::GetTickCount32();
                if ((curTick - startTick) > (10 * 1000)) {
                    break;
                }

                OAL::Thread::Sleep(1000);
            }


            App::Inst()->Oper()->DataConsumerTesterStatusDestroy(dcHdl);

            return true;
        }

        static void AdbTESysUpgrade(int boardID, const char* ipAddr) {
            /*
                adb connect 192.168.1.246:55555
                adb root
                adb connect 192.168.1.246:55555
                adb remount
                adb push /home/anapass/ANAPASS-DEV-SERVER/develop/TED/exynos8895/android/OUTT/system/lib64/libTESysTESys.so /system/lib64
                adb shell svc power reboot
            */
            const int CMD_CNT = 6;
            char connectCmd[128];
            char adbCommand[CMD_CNT][136] = {
                "adb connect 192.168.1.246:55555",
                "adb root",
                "adb connect 192.168.1.246:55555",
                "adb remount",
                "bash /home/anapass/tesys_sh/adb_tesys.sh", //"adb push /home/anapass/ANAPASS-DEV-SERVER/develop/TED/exynos8895/android/OUTT/system/lib64/libTESysTESys.so /system/lib64",
                "adb disconnect",
            };
            sprintf(connectCmd, "adb connect %s:55555", ipAddr);
            strcpy(adbCommand[0], connectCmd);
            strcpy(adbCommand[2], connectCmd);
            
            //adb connect 192.168.1.246:55555
            
            for (int i = 0; i < CMD_CNT; i++) {
                PRINTF("BID%d. [%s] \n", boardID, adbCommand[i]);
#if (CommOS==CommOS_LINUX)
                system(adbCommand[i]);
                Comm::OAL::Thread::Sleep(1000);
#endif
            }
            PRINTF("\n");
        }

        bool Tester::RunAdbTEsysUpgrade(int argc, const char** argv) {
        
            int boardID;

            printf("<<RunAdbShellScript>>\n");

            if (argc == 0) {
                 boardID = TESys::Property::Tester::Board::GetGeneralID();
            }
            else if (argc == 1) {
                 boardID = atoi(argv[0]);
            }
            else {
                printf("ERROR : argument error \n");
                printf("\t ex1) #tester runadbscript     ## boardID=GeneralID\n");
                printf("\t ex2) #tester runadbscript 30  ## boardID=30       \n");
                return false;
            }

            if (boardID == TESys::Property::Tester::Board::GetGeneralID()) {
                printf("BoardID=%d (General ID) \n", boardID);
            }
            else {
                printf("BoardID=%d \n", boardID);
            }
            
            TESys::API::PacketTesterStatusArray packetTesterArray;
            bool* isRunBoard = new bool[TESys::Property::Tester::Board::GetAvailMaxCount()+1];
            assert(isRunBoard);
            int boardCount = 0;

            for (int i = 0; i < TESys::Property::Tester::Board::GetAvailMaxCount() + 1; i++) {
                isRunBoard[i] = false;
            }
            
            //Tester Status Data Consumer Handle Create
            void* dcHdl = App::Inst()->Oper()->DataConsumerTesterStatusCreate();
            Comm::OAL::Thread::Sleep(2000);

            //GetAPI Data
            App::Inst()->Oper()->DataConsumerTesterStatusGetApiData(dcHdl, &packetTesterArray);
            App::Inst()->Oper()->DataConsumerTesterStatusDestroy(dcHdl);

            for (int i = 0; i < packetTesterArray._ArrayCount; i++) {

                struct TESys::Data::Status::Tester* pTstr = &packetTesterArray._TesterStatus[i];
                struct sockaddr_in addr;
                addr.sin_addr.s_addr = pTstr->Board.NetIPAddrI32;

                if( (boardID == pTstr->Board.BoardID) 
                    || (boardID == TESys::Property::Tester::Board::GetGeneralID()) )
                {

                    if (pTstr->Board.BoardID > 0) {
                        if (isRunBoard[pTstr->Board.BoardID] == false) {

                            char szIPAddr[64];
                            strcpy(szIPAddr, inet_ntoa(addr.sin_addr));

                            PRINTF("%d. BoardID=%d  IPAddr=%s\n", boardCount, pTstr->Board.BoardID, szIPAddr);

                            AdbTESysUpgrade(pTstr->Board.BoardID, szIPAddr);


                            isRunBoard[pTstr->Board.BoardID] = true;
                            boardCount++;
                        }
                    }
                }
            }

            PRINTF("BoardCount=%d \n", boardCount);
            //Tester Status Data Consumer Handle Destroy
            

            delete[] isRunBoard;

            return true;
        }

        bool Tester::KillTESysTester(int argc, const char** argv) {

            int boardID;

            printf("<<KillTESysTester>>\n");

            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            if (argc == 0) {
                boardID = TESys::Property::Tester::Board::GetGeneralID();
            }
            else if (argc == 1) {
                boardID = atoi(argv[0]);
            }
            else {
                printf("ERROR : argument error \n");
                printf("\t ex1) #tester killtesystester     ## boardID=GeneralID\n");
                printf("\t ex2) #tester killtesystester 30  ## boardID=30       \n");
                return false;
            }

            if (boardID == TESys::Property::Tester::Board::GetGeneralID()) {
                printf("BoardID=%d (General ID) \n", boardID);
            }
            else {
                printf("BoardID=%d \n", boardID);
            }

            App::Oper()->C_OHT_KillTESysTeser(boardID);

            return true;
        }

        bool Tester::SendLinuxCommand(int argc, const char** argv) {
        
            int boardID;

            printf("<<KillTESysTester>>\n");

            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            if (argc == 0) {
                boardID = TESys::Property::Tester::Board::GetGeneralID();
            }
            else if (argc == 1) {
                boardID = atoi(argv[0]);
            }
            else {
                printf("ERROR : argument error \n");
                printf("\t ex1) #tester linuxcmd1    ## boardID=GeneralID\n");
                printf("\t ex2) #tester linuxcmd1 30  ## boardID=30       \n");
                return false;
            }

            if (boardID == TESys::Property::Tester::Board::GetGeneralID()) {
                printf("BoardID=%d (General ID) \n", boardID);
            }
            else {
                printf("BoardID=%d \n", boardID);
            }

            App::Oper()->C_OHT_RunLinuxCommand(boardID, "ted.chipid");

            return true;
        }
        
        bool Tester::SendLinuxCommandWithResponse(int argc, const char** argv) {

            int boardID;

            printf("<<SendLinuxCommandWithResponse>>\n");

            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            if (argc == 0) {
                boardID = TESys::Property::Tester::Board::GetGeneralID();
            }
            else if (argc == 1) {
                boardID = atoi(argv[0]);
            }
            else {
                printf("ERROR : argument error \n");
                printf("\t ex1) #tester linuxcmd1    ## boardID=GeneralID\n");
                printf("\t ex2) #tester linuxcmd1 30  ## boardID=30       \n");
                return false;
            }

            if (boardID == TESys::Property::Tester::Board::GetGeneralID()) {
                printf("BoardID=%d (General ID) \n", boardID);
            }
            else {
                printf("BoardID=%d \n", boardID);
            }

            //App::Oper()->C_OHT_THO_RunLinuxCommand(boardID, "cat /sys/devices/platform/12860000.decon_f/tetime");
            App::Oper()->C_OHT_THO_RunLinuxCommand(boardID, "ted.rreg 0xE9 4");
            //App::Oper()->C_OHT_THO_RunLinuxCommand(boardID, "ted.rreg 0xEE 2");

            return true;
        }

        bool Tester::KillPython(int argc, const char** argv) {
        
            printf("<<KillPython>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "TESysShell tester killpy";
            App::Oper()->C_OHT_THO_RunLinuxCommand(boardID, linuxCmd, false   /*if ture, ignore command in case of running py*/);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }

        bool Tester::PythonPID(int argc, const char** argv) {

            printf("<<PythonPID>>\n");
            if (!App::Oper()->IsConnect()) {
                printf("ERROR : Disconnect Status \n");
                return false;
            }

            int boardID = ParseBoardID(argc, argv);
            if (boardID < 0) return false;

            const char* linuxCmd = "TESysShell tester pypid";
            App::Oper()->C_OHT_THO_RunLinuxCommand(boardID, linuxCmd, false   /*if ture, ignore command in case of running py*/);
            PRINTF("[%s]\n", linuxCmd);

            return true;
        }

    };
};


