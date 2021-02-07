#include "App.hpp"
#include "TesterStatus.hpp"
#include <TESys/Property/FileSync.hpp>

namespace TESysOperator {

    TesterStatus::TesterStatus(std::shared_ptr<TESys::Control::Operator> oper, int maxBoardID) :
        _Operator(oper)
        , _MaxBoardID(maxBoardID)
        , _IsServiceRun(true)
    {
        _DataConsumerTesterHandle = _Operator->DataConsumerTesterStatusCreate();
        assert(_DataConsumerTesterHandle);

        _TesterStatus = new struct TESys::Data::Status::Tester[_MaxBoardID+1];
        assert(_TesterStatus);

        _ThreadService = std::make_shared<Comm::OAL::ThreadService>(this);
        assert(_ThreadService);

    }

    TesterStatus::~TesterStatus() {
        
        _IsServiceRun = false;

        _ThreadService.reset();
        _Operator->DataConsumerTesterStatusDestroy(_DataConsumerTesterHandle);

        delete[] _TesterStatus;
    }
    
    void TesterStatus::Service() {
    
        memset(&_PacketTesterStatusArray, 0x00, sizeof(_PacketTesterStatusArray));

        _Operator->DataConsumerTesterStatusGetApiData(_DataConsumerTesterHandle , &_PacketTesterStatusArray);

        for (int i = 0; i < _PacketTesterStatusArray._ArrayCount; i++) {
            
            struct TESys::Data::Status::Tester* pTstrStat = &_PacketTesterStatusArray._TesterStatus[i];

            if (pTstrStat->Board.BoardID == TESys::Property::Tester::Board::GetInvalidID()) {
                //PRINTF("Invalid BoardID Detected!! \n");
                memcpy(&_TesterStatus[_MaxBoardID-1], pTstrStat, sizeof(struct TESys::Data::Status::Tester));
            }
            else if (pTstrStat->Board.BoardID <= _MaxBoardID) {
                memcpy(&_TesterStatus[pTstrStat->Board.BoardID], pTstrStat, sizeof(struct TESys::Data::Status::Tester));
            }
        }
    }
    
    void TesterStatus::WaitForNextService() {
    
        OAL::Thread::Sleep(1000);
    }
    
    bool TesterStatus::IsServiceRun() {
        return _IsServiceRun;
    }

    void TesterStatus::DisplayStatus(int reqBoardID) {
    
        int  diff10secBoardCount = 0;
        int  diff5secBoardCount = 0;

        char* szHead = new char[4096];
        assert(szHead);
        
        char* szTail = new char[4096];
        assert(szTail);
        

        for (int boardID = 1; boardID <= _MaxBoardID; boardID++) {

            struct TESys::Data::Status::Tester *pTstrStat = &_TesterStatus[boardID];
            
            if (pTstrStat->Board.BoardID == -1) {

                TESys::Property::FileSync::Status::AppStatus appStatusFileSync = (TESys::Property::FileSync::Status::AppStatus)pTstrStat->FileSync.AppStatus;
                
                struct sockaddr_in addr;
                addr.sin_addr.s_addr = pTstrStat->Board.NetIPAddrI32;
                bool isDisplay = false;

                sprintf(szHead, "%d. %s %s",
                    pTstrStat->Board.BoardID,
                    OAL::DateTime::GetKstTimeString(pTstrStat->Header.NotifyUtcTime).c_str(),
                    inet_ntoa(addr.sin_addr)
                );

                PRINTF("%s \n", szHead);
            }
            else if (pTstrStat->Board.BoardID == boardID) {

                TESys::Property::FileSync::Status::AppStatus appStatusFileSync = (TESys::Property::FileSync::Status::AppStatus)pTstrStat->FileSync.AppStatus;
                int diffTick = _Operator->TesterMonitorGetLastNotifyTickDiff(boardID);

                struct sockaddr_in addr;
                addr.sin_addr.s_addr = pTstrStat->Board.NetIPAddrI32;
                bool isDisplay = false;
                
                if (pTstrStat->Board.ErrFlag == 0) {
                    sprintf(szHead, "0x%016llX %d. %s(%d) %s",
                        pTstrStat->Board.ErrFlag,
                        pTstrStat->Board.BoardID,
                        OAL::DateTime::GetKstTimeString(pTstrStat->Header.NotifyUtcTime).c_str(),
                        diffTick,
                        inet_ntoa(addr.sin_addr)
                    );
                }
                else {
                    sprintf(szHead, "\033[31m0x%016llX\033[0m %d. %s(%d) %s",
                        pTstrStat->Board.ErrFlag,
                        pTstrStat->Board.BoardID,
                        OAL::DateTime::GetKstTimeString(pTstrStat->Header.NotifyUtcTime).c_str(),
                        diffTick,
                        inet_ntoa(addr.sin_addr)
                    );

                }

                sprintf(szTail, "%s", pTstrStat->Board.FWVer);
                std::string strAging = TESys::Data::Status::AgingToString(&pTstrStat->Aging);
                std::string strFileSync = TESys::Data::Status::FileSyncToString(&pTstrStat->FileSync);

                if (reqBoardID == TESys::Property::Tester::Board::GetGeneralID()) {
                    isDisplay = true;
                }
                else if (reqBoardID == boardID) {
                    isDisplay = true;
                }

                if (isDisplay) {
                    PRINTF("%s %s %s %s\n", szHead, strAging.c_str(), strFileSync.c_str(), szTail);
                }

                if ( (diffTick >= -2) && (diffTick < 5)  ) {
                    diff5secBoardCount++;
                }
                
                if ( (diffTick >= -2) && (diffTick < 10) ) {
                    diff10secBoardCount++;
                }
            }
            else {
                if (reqBoardID == TESys::Property::Tester::Board::GetGeneralID()) {
                    long long errFlag = 0xFFFFFFFFFFFFFFFF;
                    PRINTF("0x%016llX %d. XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX \n", errFlag, boardID);
                }
            }

            
        } // end of for (int boardID = 1; boardID <= _MaxBoardID; boardID++) {

        delete[] szHead;
        delete[] szTail;

        PRINTF("\n\n");
        PRINTF("NotifyBoardCnt in 5 sec  : %d \n", diff5secBoardCount);
        PRINTF("NotifyBoardCnt in 10 sec  : %d \n", diff10secBoardCount);
    }

};