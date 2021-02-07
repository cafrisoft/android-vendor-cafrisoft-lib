#include "Receiver.hpp"

namespace TESysDBRawData {
    
    CLASS_SINGLETON_PATTERN_IMPLEMENT(Receiver);

    Receiver::Receiver() 
    {
        _RawDataSaver = std::make_shared<RawDataSaver>(this);
        assert(_RawDataSaver);
    
        _ExportCSV = std::make_shared<ExportCSV>(this);
        assert(_ExportCSV);
    
        _DataAcq = std::make_shared<DataAcq>(this);
        assert(_DataAcq);

    }
    
    std::shared_ptr<Receiver::RawDataSaver> Receiver::GetRawDataSaver() {
        return _RawDataSaver;
    }

    std::shared_ptr<Receiver::ExportCSV> Receiver::GetExportCSV() {
        return _ExportCSV;
    }


    std::shared_ptr<Receiver::DataAcq> Receiver::GetDataAcq() {
        return _DataAcq;
    }
    
    
};
