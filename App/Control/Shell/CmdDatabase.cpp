#include "Cmd.hpp"
#include <TESys/Property/Tester.hpp>
#include <TESys/Property/Path.hpp>
#include <TED/Api.h>
#include <TESys/Data/DataAcqDB.hpp>

namespace AppControlShell {
    namespace Cmd {


         bool Database::PickTester(int argc, const char** argv) {

             int boardID = 180;
             int dutIdx = 1;
             const time_t beginTime = Comm::OAL::DateTime::GetUtcTime_KST(2020, 9, 23, 19, 7, 0);
             const time_t endTime = Comm::OAL::DateTime::GetUtcTime_KST(2020, 9, 23, 19, 10, 0);

             std::shared_ptr<TESys::Data::DataAcqDB> dataAcqDB = TESys::Data::DataAcqDB::CreateObject(TESys::Data::DataAcqDB::ID::Raw);
             assert(dataAcqDB);

             dataAcqDB->Verify_PacketDataAcq(beginTime, endTime, boardID, dutIdx);

             return true;
         }


    };
};


