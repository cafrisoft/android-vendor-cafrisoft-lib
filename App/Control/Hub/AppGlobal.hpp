#ifndef APPCONTROLHUB_APPGLOBAL_HPP__
#define APPCONTROLHUB_APPGLOBAL_HPP__

#include "AppDefine.h"
#include "Tester.hpp"

namespace ControlHub {

    class AppGlobal {

        CLASS_SINGLETON_PATTERN_DECLARE(AppGlobal);
    
    private:
        std::vector<std::shared_ptr<Tester>> _TesterVector;
        std::shared_ptr<Comm::OAL::CriticalSection> _CriticalSection;

    public:
        AppGlobal();

    public:
        bool RegisterNewTester(int boardID, int cliSockID);
        bool UnRegisterNewTester(int cliSockID);
    };

};

#endif
