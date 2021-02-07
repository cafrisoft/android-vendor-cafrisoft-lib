#ifndef CONTROLOPERATOR_APP_HPP__
#define CONTROLOPERATOR_APP_HPP__

#include "AppDefine.hpp"
#include "TesterStatus.hpp"
#include "HubStatus.hpp"

namespace TESysOperator {

    class App {

    private:
        static std::shared_ptr<App> _Instance;
    public:
        static void Init();
        static void Deinit();

        static std::shared_ptr<App> Inst();
        static std::shared_ptr<TESys::Control::Operator> Oper();
        static std::shared_ptr<TESysOperator::TesterStatus> TesterStatus();
        static std::shared_ptr<TESysOperator::HubStatus> HubStatus();

    private:
        std::shared_ptr<TESys::Control::Operator> _Operator;
        std::shared_ptr<TESysOperator::TesterStatus> _TesterStatus;
        std::shared_ptr<TESysOperator::HubStatus> _HubStatus;

    public:
        App();
        ~App();

    public:
        int Main(int argc, char* argv[]);

    
    };



};

#endif

