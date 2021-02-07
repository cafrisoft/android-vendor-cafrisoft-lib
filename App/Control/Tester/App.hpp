#ifndef CONTROLTESTER_APP_HPP__
#define CONTROLTESTER_APP_HPP__

#include <Comm/Shell/Main.hpp>

#include <TESys/Global/BuildOptions.h>
#include <TESys/Net/PacketControl.hpp>
#include <TESys/Control/Tester.hpp>

#define CLOG_TAG "TESysControlTester"

using namespace Comm;

namespace ControlTester {

    class App {

    private:
        static std::shared_ptr<App> _Instance;
    public:
        static bool Init(int testerCount=1);
        static std::shared_ptr<App> Inst();
        static std::shared_ptr<TESys::Control::Tester> Tester(int idx=0);

    private:
        int _TesterCount;
        std::shared_ptr<TESys::Control::Tester>* _TesterArray;

    public:
        App(int testerCount);

    public:
        bool Run();

    };



};

#endif

