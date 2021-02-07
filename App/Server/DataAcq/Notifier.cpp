#include "Notifier.hpp"

namespace TESysDataAcq {
    
    CLASS_SINGLETON_PATTERN_IMPLEMENT(Notifier);

    Notifier::Notifier() 
    {
        _AgingMonitor = std::make_shared<TESys::Control::AgingMonitor>();
        assert(_AgingMonitor);
        //_AgingMonitor->EnableExport(true);

        //_Exporter = std::make_shared<Exporter>(this);
        //assert(_Exporter);

        _RawDataSaver = std::make_shared<RawDataSaver>(this);
        assert(_RawDataSaver);
    
        _TCPServer = std::make_shared<TCPServer>(this);
        assert(_TCPServer);

        _Tester = std::make_shared<Tester>(this);
        assert(_Tester);

    }
    
    std::shared_ptr<TESys::Control::AgingMonitor> Notifier::GetAgingMonitor() {
        return _AgingMonitor;
    }

    std::shared_ptr<Notifier::Exporter> Notifier::GetExporter() {
        return _Exporter;
    }

    std::shared_ptr<Notifier::RawDataSaver> Notifier::GetRawDataSaver() {
        return _RawDataSaver;
    }
    
    std::shared_ptr<Notifier::Tester> Notifier::GetTester() {
        return _Tester;
    }
    
    std::shared_ptr<Notifier::TCPServer> Notifier::GetTCPServer() {
        return _TCPServer;
    }

};
