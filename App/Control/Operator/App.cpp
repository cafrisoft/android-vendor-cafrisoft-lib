#include "App.hpp"

namespace TESysOperator {

    std::shared_ptr<App> App::_Instance;

    void App::Init() {
        App::_Instance = std::make_shared<App>();
        assert(App::_Instance);
    }

    void App::Deinit() {
        App::_Instance.reset();
    }

    std::shared_ptr<App> App::Inst() {

        assert(App::_Instance);
        return App::_Instance;
    }

    
    std::shared_ptr<TESys::Control::Operator> App::Oper() {
        
        return App::Inst()->_Operator;
    }

    std::shared_ptr<TESysOperator::TesterStatus> App::TesterStatus() {

        return App::Inst()->_TesterStatus;
    }

    std::shared_ptr<TESysOperator::HubStatus> App::HubStatus() {

        return App::Inst()->_HubStatus;
    }


    App::App() {
     
        _Operator = std::make_shared<TESys::Control::Operator>();
        assert(_Operator);

        _TesterStatus = std::make_shared<TESysOperator::TesterStatus>(_Operator, 60);
        assert(_TesterStatus);

        _HubStatus = std::make_shared<TESysOperator::HubStatus>(_Operator);
        assert(_HubStatus);
    }

    App::~App() {
    
        CLOGD("");
        _HubStatus.reset();
        CLOGD("");
        _TesterStatus.reset();
        CLOGD("");
        _Operator.reset();
        CLOGD("");

    }
        
    int App::Main(int argc, char* argv[]) {

        
        return 0;
    }

    
};