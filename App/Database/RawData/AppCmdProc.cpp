#define CLOG_TAG SYSLOG_NAME
#include "AppCmdProc.hpp"
#include <Comm/Property/System.hpp>
#include <TESys/TED/PowerSource.hpp>
#include <TESys/Property/TED.hpp>

namespace AppDataBaseRawData {

    static void IntArrToString(int* valueArr, int valueCnt, /*OUT*/ char* msgBuf) {

        char szTmp[128];

        msgBuf[0] = '\0';
        for (int i = 0; i < valueCnt; i++) {
            sprintf(szTmp, "%d ", valueArr[i]);
            strcat(msgBuf, szTmp);
        }
    }


    void CmdProc::MeasureAdc(std::shared_ptr<TESys::Net::PacketDataAcq> pack) {

        char* szMsg;
        struct TESys::Data::Adc::ValueCollection valueCollection;
        pack->GetAdc(&valueCollection);

        szMsg = new char[valueCollection.AdcCount * 100 + 1024];
        assert(szMsg);
        strcpy(szMsg, "");

        strcat(szMsg, Comm::OAL::DateTime::GetKstDateString(pack->GetUtcTime()).c_str());
        strcat(szMsg, " ");
        strcat(szMsg, Comm::OAL::DateTime::GetKstTimeString(pack->GetUtcTime()).c_str());
        strcat(szMsg, ":");
        strcat(szMsg, Comm::Utils::StringFormat("%d", pack->GetSystemTick() % 1000).c_str());
        strcat(szMsg, " ");
        strcat(szMsg, Comm::Utils::StringFormat("BoardID=%d DutIdx=%d ProductID=%d", pack->GetBoardID(), pack->GetDutIndex(), pack->GetProductID()).c_str());
        strcat(szMsg, " ChipID=[");
        strcat(szMsg, Comm::Utils::StringTool::ToStringHex(pack->GetChipID()).c_str());
        strcat(szMsg, "] ");
        
        for (int iadc = 0; iadc < valueCollection.AdcCount; iadc++) {
        
            struct TESys::Data::Adc::Value* pValue = &valueCollection.Value[iadc];
            char szTmp[128];
            sprintf(szTmp, "%s(%d) ", TESys::TED::PowerSource::GetName(TESys::Property::TED::Product::ANA6707, pValue->PsId).c_str(), pValue->Volt);
            strcat(szMsg, szTmp);
        }

        CLOGI("%s", szMsg);

        delete[] szMsg;
    }

    void CmdProc::ErrorReport(std::shared_ptr<TESys::Net::PacketDataAcq> pack) {
    
#if 0
        //Print 
        CLOGI("[ErrorReprot %04d-%02d-%02d %02d:%02d:%02d:%03d BoardID(%d) OS(%s) ] Job(%d) SC(%d) TC(%d-%d)",

            pack->GetKstYear(), pack->GetKstMonth(), pack->GetKstDay(),
            pack->GetKstHour(), pack->GetKstMinute(), pack->GetKstSecond(), pack->GetSystemTickMilisec(),

            pack->GetBoardID(), Comm::Property::System::Get_OS_Name(pack->GetBoardOS()),

            pack->GetJobID(), pack->GetScID(), pack->GetTcID(), pack->GetTcStepID()
        );
#endif
    }

    void CmdProc::JobBegin(std::shared_ptr<TESys::Net::PacketDataAcq> pack) {

        CLOGI("[JobBegin %04d-%02d-%02d %02d:%02d:%02d BoardID(%d) ] Job(%d) ",

            pack->GetKstYear(), pack->GetKstMonth(), pack->GetKstDay(),
            pack->GetKstHour(), pack->GetKstMinute(), pack->GetKstSecond(), 

            pack->GetBoardID(), 
            pack->GetJobID()
        );
    }

    void CmdProc::JobEnd(std::shared_ptr<TESys::Net::PacketDataAcq> pack) {
    
        CLOGI("[JobEnd %04d-%02d-%02d %02d:%02d:%02d BoardID(%d) ] Job(%d)",

            pack->GetKstYear(), pack->GetKstMonth(), pack->GetKstDay(),
            pack->GetKstHour(), pack->GetKstMinute(), pack->GetKstSecond(),

            pack->GetBoardID(), 
            pack->GetJobID()
        );
    }

    void CmdProc::ScBegin(std::shared_ptr<TESys::Net::PacketDataAcq> pack) {

        CLOGI("[ScBegin %04d-%02d-%02d %02d:%02d:%02d BoardID(%d) ] Job(%d) SC(%d)",

            pack->GetKstYear(), pack->GetKstMonth(), pack->GetKstDay(),
            pack->GetKstHour(), pack->GetKstMinute(), pack->GetKstSecond(),

            pack->GetBoardID(), 
            pack->GetJobID(), pack->GetScID()
        );
    }

    void CmdProc::ScEnd(std::shared_ptr<TESys::Net::PacketDataAcq> pack) {

        CLOGI("[ScEnd %04d-%02d-%02d %02d:%02d:%02d BoardID(%d) ] Job(%d) SC(%d)",

            pack->GetKstYear(), pack->GetKstMonth(), pack->GetKstDay(),
            pack->GetKstHour(), pack->GetKstMinute(), pack->GetKstSecond(), 

            pack->GetBoardID(), 

            pack->GetJobID(), pack->GetScID()
        );
    }

    void CmdProc::TcBegin(std::shared_ptr<TESys::Net::PacketDataAcq> pack) {

        CLOGI("[TcBegin %04d-%02d-%02d %02d:%02d:%02d BoardID(%d) ] Job(%d) SC(%d) TC(%d)",

            pack->GetKstYear(), pack->GetKstMonth(), pack->GetKstDay(),
            pack->GetKstHour(), pack->GetKstMinute(), pack->GetKstSecond(), 

            pack->GetBoardID(), 
            pack->GetJobID(), pack->GetScID(), pack->GetTcID()
        );
    }

    void CmdProc::TcEnd(std::shared_ptr<TESys::Net::PacketDataAcq> pack) {

        CLOGI("[TcEnd %04d-%02d-%02d %02d:%02d:%02d BoardID(%d)  ] Job(%d) SC(%d) TC(%d)",

            pack->GetKstYear(), pack->GetKstMonth(), pack->GetKstDay(),
            pack->GetKstHour(), pack->GetKstMinute(), pack->GetKstSecond(),

            pack->GetBoardID(), 

            pack->GetJobID(), pack->GetScID(), pack->GetTcID()
        );
    }

    void CmdProc::TcStepBegin(std::shared_ptr<TESys::Net::PacketDataAcq> pack) {

        CLOGI("[TcStepBegin %04d-%02d-%02d %02d:%02d:%02d BoardID(%d) ] Job(%d) SC(%d) TC(%d-%d)",

            pack->GetKstYear(), pack->GetKstMonth(), pack->GetKstDay(),
            pack->GetKstHour(), pack->GetKstMinute(), pack->GetKstSecond(), 

            pack->GetBoardID(), 
            pack->GetJobID(), pack->GetScID(), pack->GetTcID(), pack->GetTcStepID()
        );
    }

    void CmdProc::TcStepEnd(std::shared_ptr<TESys::Net::PacketDataAcq> pack) {

        CLOGI("[TcStepEnd %04d-%02d-%02d %02d:%02d:%02d BoardID(%d) ] Job(%d) SC(%d) TC(%d-%d)",

            pack->GetKstYear(), pack->GetKstMonth(), pack->GetKstDay(),
            pack->GetKstHour(), pack->GetKstMinute(), pack->GetKstSecond(), 

            pack->GetBoardID(), 

            pack->GetJobID(), pack->GetScID(), pack->GetTcID(), pack->GetTcStepID()
        );
    }

};