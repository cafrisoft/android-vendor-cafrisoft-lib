#include "RemotePython.hpp"
#include <TED/Api.h>

using namespace TESys::Net;

namespace RemotePython {

    bool Mipi::ReadReg(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        unsigned int addr;
        int byteOffset, readCount;
        unsigned char* regValue;
        bool bRet = false;

        addr = rcvPack->GetInt(0);
        byteOffset = rcvPack->GetInt(1);
        readCount = rcvPack->GetInt(2);

        regValue = new unsigned char[readCount];
        assert(regValue);
        
        bRet = TedMipiReadReg(addr, byteOffset, readCount, regValue, readCount);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, addr);
        sendPack->SetInt(1, byteOffset);
        sendPack->SetInt(2, readCount);
        sendPack->SetInt(3, bRet);

        sendPack->SetData(regValue, readCount);
        sendPack->GenCRC();
        
        client->Send(sendPack);

        delete[] regValue;
#endif
        return true;
    }

    bool Mipi::WriteReg(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        unsigned int addr;
        int byteOffset, writeCount;
        unsigned char* regValue;
        bool bRet = false;

        addr = rcvPack->GetInt(0);
        byteOffset = rcvPack->GetInt(1);
        writeCount = rcvPack->GetInt(2);
        regValue = new unsigned char[writeCount];
        assert(regValue);
        rcvPack->GetData(regValue, writeCount);

        bRet = TedMipiWriteReg(addr, byteOffset, writeCount, regValue);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, addr);
        sendPack->SetInt(1, byteOffset);
        sendPack->SetInt(2, writeCount);
        sendPack->SetInt(3, bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        delete[] regValue;
#endif
        return true;
    }

    //WREG0=0x39, [Addr], [regVal0], [regVal1].....
    bool Mipi::WriteReg39(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        unsigned int addr;
        int writeCount;
        unsigned char* regValue;
        bool bRet = false;

        addr = rcvPack->GetInt(0);
        writeCount = rcvPack->GetInt(1);
        regValue = new unsigned char[writeCount];
        assert(regValue);
        rcvPack->GetData(regValue, writeCount);

        bRet = TedMipiWriteReg39(addr, writeCount, regValue);


        char* szRegValue = new char[1024 * 8];
        assert(szRegValue);
        szRegValue[0] = '\0';
        for (int i = 0; i < writeCount; i++) {
            char szTmp[32];
            sprintf(szTmp, "0x%02x,", (int)regValue[i] & 0xFF);
            strcat(szRegValue, szTmp);
        }
        CLOGI("WREG0(%d)=0x39,0x%02X,%s\t%s", writeCount, addr, szRegValue, Debug::FuncNameStack().c_str());
        Debug::ExecelTxtPrint("WREG0(%d)=0x39,0x%02X,%s", writeCount, addr, szRegValue);
        delete[] szRegValue;

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, addr);
        sendPack->SetInt(1, writeCount);
        sendPack->SetInt(2, bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        delete[] regValue;

#endif
        return true;
    }

    bool Mipi::WriteReg15(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        unsigned int  addr;
        unsigned char regValue;
        bool bRet = false;

        addr = rcvPack->GetInt(0);
        regValue = rcvPack->GetInt(1);
        
        bRet = TedMipiWriteReg15(addr, regValue);

        //PRINTF("[%s] WREG0=0x15,0x%02X, 0x%02X ", Debug::FuncNameStack().c_str(), addr, regValue);
        //CLOGI("WREG0=0x15,0x%02X,0x%02X\t%s", addr, regValue, Debug::FuncNameStack().c_str());
        Debug::ExecelTxtPrint("WREG0=0x15,0x%02X,0x%02X", addr, regValue);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, addr);
        sendPack->SetInt(1, regValue);
        sendPack->SetInt(2, bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

#endif
        return true;
    }

    bool Mipi::WriteReg05(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        unsigned int  addr;
        bool bRet = false;

        addr = rcvPack->GetInt(0);
        
        bRet = TedMipiWriteReg05(addr);

        //PRINTF("[%s] WREG0=0x05,0x%02X ", Debug::FuncNameStack().c_str(), addr);
        //CLOGI("WREG0=0x05,0x%02X\t%s", addr, Debug::FuncNameStack().c_str());
        Debug::ExecelTxtPrint("WREG0=0x05,0x%02X", addr);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, addr);
        sendPack->SetInt(1, bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

#endif
        return true;
    }

    bool Mipi::WriteReg07(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

#if 0
        unsigned int  value;
        bool bRet = false;

        value = rcvPack->GetInt(0);

        bRet = TedMipiWriteReg07(value);

        //PRINTF("[%s] WREG0=0x05,0x%02X ", Debug::FuncNameStack().c_str(), addr);
        //CLOGI("WREG0=0x05,0x%02X\t%s", addr, Debug::FuncNameStack().c_str());
        Debug::ExecelTxtPrint("WREG0=0x07,0x%02X", value);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, value);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);
#endif
        return true;
    }
};