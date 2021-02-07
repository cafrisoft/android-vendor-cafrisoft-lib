#include "AppDefine.hpp"

namespace TESysDB {

    bool Export(int jobID, int scID, int tcID) {

        std::shared_ptr<TESys::DB::Join::TcStepList> joineTcStepList = std::make_shared<TESys::DB::Join::TcStepList>();
        assert(joineTcStepList);
        joineTcStepList->Select(jobID, scID, tcID);

        return true;
    }

};

