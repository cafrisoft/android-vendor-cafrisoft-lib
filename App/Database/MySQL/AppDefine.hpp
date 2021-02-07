#ifndef APPDATABASERAWDATA_APPDEFINE_HPP__
#define APPDATABASERAWDATA_APPDEFINE_HPP__

#include <Comm/Shell/Main.hpp>
#include <Comm/Utils/argparse.h>

#include <Database/RDBMS/Base.hpp>

#include <TESys/Global/BuildOptions.h>
#include <TESys/Net/PacketDataAcq.hpp>
#include <TESys/Property/HeaderFiles.hpp>
#include <TESys/Property/Net.hpp>
#include <TESys/Data/DataAcqDBRaw.hpp>
#include <TESys/TED/VerifyBoard.hpp>

#include <TESys/DB/Single/Ted.hpp>
#include <TESys/DB/Single/TedList.hpp>
#include <TESys/DB/Single/Job.hpp>
#include <TESys/DB/Single/JobList.hpp>
#include <TESys/DB/Single/Sc.hpp>
#include <TESys/DB/Single/ScList.hpp>
#include <TESys/DB/Single/Tc.hpp>
#include <TESys/DB/Single/TcList.hpp>
#include <TESys/DB/Single/TcStep.hpp>
#include <TESys/DB/Single/TcStepList.hpp>
#include <TESys/DB/Single/Cpu.hpp>
#include <TESys/DB/Single/SocPcb.hpp>
#include <TESys/DB/Single/DutPcb.hpp>
#include <TESys/DB/Single/Hardware.hpp>
#include <TESys/DB/Single/AdcProp.hpp>
#include <TESys/DB/Single/Software.hpp>

#include <TESys/DB/Single/AdcExtV.hpp>
#include <TESys/DB/Single/AdcExtA.hpp>
#include <TESys/DB/Single/AdcLdoV.hpp>
#include <TESys/DB/Single/AdcRegV.hpp>
#include <TESys/DB/Single/AdcSoutV.hpp>
#include <TESys/DB/Single/AdcErr.hpp>

#include <TESys/DB/Join/TcStepList.hpp>

#define CLOG_TAG "TESysDBMySQL"


namespace TESysDB {
    void Connect();
    void Disconnect();
    void Insert(std::vector<std::string> rawDBFileNameVector, int reqJobID=-1, int reqScID = -1, int reqTcID = -1);

    bool Export(int jobID, int scID, int tcID);
};

#endif