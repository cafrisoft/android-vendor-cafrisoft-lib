#include "AppCmdProc.hpp"

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

#if 0
        int vlin1_volt_VLIN, vlin1_volt_VBAT, vlin1_volt_ELVDD;
        int vlin1_curr_VLIN, vlin1_curr_VBAT, vlin1_curr_ELVDD;

        int vci_volt_VCI, vci_volt_VDDR, vci_volt_VDDI;
        int vci_curr_VCI, vci_curr_VDDR, vci_curr_VDDI;

        int sout_ch_cnt;
        int* sout_volt = NULL;

        int ldo_ch_cnt;
        int* ldo_volt = NULL;

        int reg_ch_cnt;
        int* reg_volt = NULL;

        char* msgbuf = new char[1024 * 8];
        assert(msgbuf);


        //Get VLIN1
        pack->GetVlin1Adc(&vlin1_volt_VLIN, &vlin1_volt_VBAT, &vlin1_volt_ELVDD,
            &vlin1_curr_VLIN, &vlin1_curr_VBAT, &vlin1_curr_ELVDD);

        //Get VCI
        pack->GetVciAdc(&vci_volt_VCI, &vci_volt_VDDR, &vci_volt_VDDI,
            &vci_curr_VCI, &vci_curr_VDDR, &vci_curr_VDDI);

        //Get SOUT
        sout_ch_cnt = pack->GetSoutChannelCount();
        if (sout_ch_cnt > 0) {
            sout_volt = new int[sout_ch_cnt];
            assert(sout_volt);
            pack->GetSoutAdc(sout_volt);
        }

        //Get LDO
        ldo_ch_cnt = pack->GetLdoChannelCount();
        if (ldo_ch_cnt > 0) {
            ldo_volt = new int[ldo_ch_cnt];
            assert(ldo_volt);
            pack->GetLdoAdc(ldo_volt);
        }

        //Get REG
        reg_ch_cnt = pack->GetRegChannelCount();
        if (reg_ch_cnt > 0) {
            reg_volt = new int[reg_ch_cnt];
            assert(reg_volt);
            pack->GetRegAdc(reg_volt);
        }

        //Print 
        CLOGI("[MeasureADC %04d-%02d-%02d %02d:%02d:%02d:%03d BoardID(%d) ] Job(%d) SC(%d) TC(%d-%d)",

            pack->GetKstYear(), pack->GetKstMonth(), pack->GetKstDay(),
            pack->GetKstHour(), pack->GetKstMinute(), pack->GetKstSecond(), pack->GetSystemTickMilisec(),

            pack->GetBoardID(),

            pack->GetJobID(), pack->GetScID(), pack->GetTcID(), pack->GetTcStepID()
        );

        CLOGI("\tVLIN1 Voltage: ");
        CLOGI("\t   VLIN1=%d VBAT=%d ELVDD=%d", vlin1_volt_VLIN, vlin1_volt_VBAT, vlin1_volt_ELVDD);
        CLOGI("\tVLIN1 Current: ");
        CLOGI("\t   VLIN1=%d VBAT=%d ELVDD=%d", vlin1_curr_VLIN, vlin1_curr_VBAT, vlin1_curr_ELVDD);

        CLOGI("\tVCI Voltage: ");
        CLOGI("\t   VCI=%d VDDR=%d VDDI=%d", vci_volt_VCI, vci_volt_VDDR, vci_volt_VDDI);
        CLOGI("\tVCI Current: ");
        CLOGI("\t   VCI=%d VDDR=%d VDDI=%d", vci_curr_VCI, vci_curr_VDDR, vci_curr_VDDI);

        if (sout_ch_cnt > 0) {
            IntArrToString(sout_volt, sout_ch_cnt, msgbuf);
            CLOGI("\tSOUT Voltage: ch_cnt(%d) [%s]", sout_ch_cnt, msgbuf);
        }

        if (ldo_ch_cnt > 0) {
            IntArrToString(ldo_volt, ldo_ch_cnt, msgbuf);
            CLOGI("\tLDO Voltage: ch_cnt(%d) [%s]", ldo_ch_cnt, msgbuf);
        }

        if (reg_ch_cnt > 0) {
            IntArrToString(reg_volt, reg_ch_cnt, msgbuf);
            CLOGI("\tREG Voltage: ch_cnt(%d) [%s]", reg_ch_cnt, msgbuf);
        }

        delete[] sout_volt;
        delete[] ldo_volt;
        delete[] reg_volt;
        delete[] msgbuf;
#endif
    }

    void CmdProc::ErrorReport(std::shared_ptr<TESys::Net::PacketDataAcq> pack) {
    
        //Print 
        CLOGI("[ErrorReprot %04d-%02d-%02d %02d:%02d:%02d BoardID(%d) ] Job(%d) SC(%d) TC(%d-%d)",

            pack->GetKstYear(), pack->GetKstMonth(), pack->GetKstDay(),
            pack->GetKstHour(), pack->GetKstMinute(), pack->GetKstSecond(),

            pack->GetBoardID(),

            pack->GetJobID(), pack->GetScID(), pack->GetTcID(), pack->GetTcStepID()
        );

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
    
        CLOGI("[JobEnd %04d-%02d-%02d %02d:%02d:%02d: BoardID(%d) ] Job(%d)",

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

        CLOGI("[TcEnd %04d-%02d-%02d %02d:%02d:%02d BoardID(%d) ] Job(%d) SC(%d) TC(%d)",

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