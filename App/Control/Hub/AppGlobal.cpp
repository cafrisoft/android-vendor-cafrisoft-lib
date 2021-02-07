#include "AppGlobal.hpp"

namespace ControlHub {

    CLASS_SINGLETON_PATTERN_IMPLEMENT(AppGlobal);
    
    AppGlobal::AppGlobal() {

        _CriticalSection = OAL::CriticalSection::CreateObject();
        assert(_CriticalSection);
    }

    bool AppGlobal::RegisterNewTester(int boardID, int cliSockID) {

        bool bRet = true;
        OAL::Lock lock(_CriticalSection);

        for (std::vector<std::shared_ptr<Tester>>::const_iterator it = _TesterVector.cbegin(); it != _TesterVector.cend(); ++it) {

            std::shared_ptr<Tester> tester = *it;
            if (tester->GetBoardID() == boardID || tester->GetCliSockID() == cliSockID) {
                CLOGE("Fail to Register new Board ,  ID has some error...");
                CLOGE("Already Registered Deivce :  BoardID(%d) cliSockID(%d) ", tester->GetBoardID(), tester->GetCliSockID());
                CLOGE("    New Registered Deivce :  BoardID(%d) cliSockID(%d) ", boardID, cliSockID);
                bRet = false;
                break;
            }
        }

        if (bRet) {
            std::shared_ptr<Tester> tester = std::make_shared<Tester>(boardID, cliSockID);
        }

        return bRet;
    }

    bool AppGlobal::UnRegisterNewTester(int cliSockID) {
    
        bool bRet = false;
        OAL::Lock lock(_CriticalSection);

        for (std::vector<std::shared_ptr<Tester>>::iterator it = _TesterVector.begin(); it != _TesterVector.end(); ++it) {

            std::shared_ptr<Tester> tester = *it;
            if (tester->GetCliSockID() == cliSockID) {
                
                _TesterVector.erase(it);
                bRet = true;
                break;
            }
        }

        return bRet;
    }

};
