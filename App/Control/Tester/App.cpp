#include "App.hpp"
#include <TESys/Property/Tester.hpp>

namespace ControlTester {

    std::shared_ptr<App> App::_Instance;

    bool App::Init(int testerCount) {
    
        App::_Instance = std::make_shared<App>(testerCount);
        assert(App::_Instance);

        return true;
    }

    std::shared_ptr<App> App::Inst() {
        assert(App::_Instance);
        return App::_Instance;
    }

    std::shared_ptr<TESys::Control::Tester> App::Tester(int idx) {

        return App::Inst()->_TesterArray[idx];
    }

    App::App(int testerCount) :
     _TesterCount(testerCount)
    {
        assert( (_TesterCount > 0) && (_TesterCount <= TESys::Property::Tester::Board::GetAvailMaxCount()) );
        _TesterArray = new std::shared_ptr<TESys::Control::Tester>[_TesterCount];
        assert(_TesterArray);

        for (int idx = 0; idx < _TesterCount; idx++) {
            int testerID = idx + TESys::Property::Tester::Board::GetID();
            _TesterArray[idx] = std::make_shared<TESys::Control::Tester>(testerID);
            assert(_TesterArray[idx]);

            OAL::Thread::Sleep(100);
        }

    }

    bool App::Run() {


        while (true) {
            OAL::Thread::Sleep(1000);
        }

        return true;
    }


};