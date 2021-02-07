#include "RemotePython.hpp"
#include <TED/Api.h>

using namespace TESys::Net;

namespace RemotePython {

    bool Pattern::SetCommand(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

        int cmdBufByteSize;
        unsigned char* cmdBuf;
        bool bRet = false;

        cmdBufByteSize = rcvPack->GetInt(0);
        cmdBuf = new unsigned char[cmdBufByteSize];
        assert(cmdBuf);

        rcvPack->GetData(cmdBuf, cmdBufByteSize);

        bRet = true; // TedMipiReadReg(addr, byteOffset, readCount, regValue, readCount);
        CLOGI("PTRN_SET=%s\t%s", cmdBuf, Debug::FuncNameStack().c_str());
        Debug::ExecelTxtPrint("PTRN_SET=%s", cmdBuf);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, cmdBufByteSize);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        delete[] cmdBuf;

        return true;
    }


};