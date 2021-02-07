#include <TESys/Global/BuildOptions.h>
#include <TESys/Control/AgingMonitor.hpp>
#include <TESys/Data/DataAcqDB.hpp>


#if 1
int main(int argc, char* argv[]) {

    //const time_t beginTime = Comm::OAL::DateTime::GetUtcTime_KST(2020, 9, 23, 19, 0, 0);
    //const time_t endTime = Comm::OAL::DateTime::GetUtcTime_KST(2020, 9, 24, 8, 2, 0);

    const int year = 2020;
    const int min = 0;
    const int sec = 0;
    int beginYear=year, beginMonth = 0, beginDay = 0, beginHour=0, beginMin=min, beginSec=sec;
    int endYear=year, endMonth = 0, endDay = 0, endHour = 0, endMin=min, endSec=sec;

    printf("----------------------------------------------\n");
    printf("Begin Month : ");
    scanf("%d", &beginMonth);

    printf("Begin Day : ");
    scanf("%d", &beginDay);

    printf("Begin Hour : ");
    scanf("%d", &beginHour);

    printf("----------------------------------------------\n");
    printf("End Month : ");
    scanf("%d", &endMonth);

    printf("End Day : ");
    scanf("%d", &endDay);

    printf("End Hour : ");
    scanf("%d", &endHour);

    printf("----------------------------------------------\n");
    printf("BeginTime : %04d-%02d-%02d %02d:%02d:%02d \n", beginYear, beginMonth, beginDay, beginHour, beginMin, beginSec);
    printf("EndTime : %04d-%02d-%02d %02d:%02d:%02d \n", endYear, endMonth, endDay, endHour, endMin, endSec);

#if 1
    const time_t beginTime = Comm::OAL::DateTime::GetUtcTime_KST(beginYear, beginMonth, beginDay, beginHour, beginMin, beginSec);
    const time_t endTime = Comm::OAL::DateTime::GetUtcTime(endYear, endMonth, endDay, endHour, endMin, endSec);

    std::shared_ptr<TESys::Data::DataAcqDB> dataAcqDB = TESys::Data::DataAcqDB::CreateObject(TESys::Data::DataAcqDB::ID::Raw);
    assert(dataAcqDB);

    dataAcqDB->Verify_PacketDataAcq(beginTime, endTime);
#endif

    return 0;
}

#else
int main(int argc, char* argv[]) {

    const time_t beginTime = Comm::OAL::DateTime::GetUtcTime_KST(2020, 9, 23, 19, 0, 0);
    const time_t endTime = Comm::OAL::DateTime::GetUtcTime_KST(2020, 9, 24, 7, 2, 0);

    std::shared_ptr<TESys::Control::AgingMonitor> agingMonitor = std::make_shared<TESys::Control::AgingMonitor>();
    assert(agingMonitor);

    std::shared_ptr<TESys::Data::DataAcqDB> dataAcqDB = TESys::Data::DataAcqDB::CreateObject(TESys::Data::DataAcqDB::ID::Raw);
    assert(dataAcqDB);

    std::vector<std::shared_ptr<TESys::Net::PacketDataAcq>> vecPack = dataAcqDB->Query_PacketDataAcq(beginTime, endTime);
        
    for (std::vector<std::shared_ptr<TESys::Net::PacketDataAcq>>::const_iterator it = vecPack.cbegin();
        it != vecPack.cend();
        it++) {
    
        std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack = (*it);
        
        //boardID = rcvPack->GetBoardID();
        //dutIdx = rcvPack->GetDutIndex();

        agingMonitor->CmdProc(rcvPack);

#if 0
        TESys::Net::Command::Aging cmd = rcvPack->GetCommand();
        switch (cmd) {
            case TESys::Net::Command::Aging::PyStart:
                break;
                
            case TESys::Net::Command::Aging::PyStop:
                PRINTF("[%d:%d] Err:%d \n", boardID, dutIdx, agingMonitor->IsLastActionError(boardID, dutIdx));
                break;
        }
#endif

    }

    for (int boardID = 1; boardID <= 500; boardID++) {
    
        for (int dutIdx = 0; dutIdx < 2; dutIdx++) {

            PRINTF("[%d:%d] PyRun(%d-%d) Err=%d \n", boardID, dutIdx, 
                agingMonitor->GetPyStartCount(boardID, dutIdx), agingMonitor->GetPyStopCount(boardID, dutIdx), agingMonitor->GetPyResultErrCount(boardID, dutIdx));

        }
    }



    return 0;
}


#endif