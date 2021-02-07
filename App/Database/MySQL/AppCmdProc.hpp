#ifndef APPDATABASERAWDATA_CMDPROC_HPP__
#define APPDATABASERAWDATA_CMDPROC_HPP__

#include "AppDefine.hpp"

namespace AppDataBaseRawData {
    
    class CmdProc {
    public:
        static void MeasureAdc(std::shared_ptr<TESys::Net::PacketDataAcq> pack);
        static void ErrorReport(std::shared_ptr<TESys::Net::PacketDataAcq> pack);

        static void JobBegin(std::shared_ptr<TESys::Net::PacketDataAcq> pack);
        static void JobEnd(std::shared_ptr<TESys::Net::PacketDataAcq> pack);

        static void ScBegin(std::shared_ptr<TESys::Net::PacketDataAcq> pack);
        static void ScEnd(std::shared_ptr<TESys::Net::PacketDataAcq> pack);

        static void TcBegin(std::shared_ptr<TESys::Net::PacketDataAcq> pack);
        static void TcEnd(std::shared_ptr<TESys::Net::PacketDataAcq> pack);

        static void TcStepBegin(std::shared_ptr<TESys::Net::PacketDataAcq> pack);
        static void TcStepEnd(std::shared_ptr<TESys::Net::PacketDataAcq> pack);

    };

};
#endif

