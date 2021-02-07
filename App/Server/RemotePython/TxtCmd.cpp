#include "RemotePython.hpp"
#include <TED/Api.h>

using namespace TESys::Net;

namespace RemotePython {

    bool TxtCmd::Send(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

        int txtCmdBufByteSize;
        unsigned char* txtCmd;
        bool bRet = false;

        txtCmdBufByteSize = rcvPack->GetInt(0);
        txtCmd = new unsigned char[txtCmdBufByteSize];
        assert(txtCmd);

        rcvPack->GetData(txtCmd, txtCmdBufByteSize);

        bRet = true; // TedMipiReadReg(addr, byteOffset, readCount, regValue, readCount);
        CLOGI("%s\t%s", txtCmd, Debug::FuncNameStack().c_str());
        Debug::ExecelTxtPrint("%s", txtCmd);

        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(Command::Python::TxtCmdSend);
        sendPack->SetInt(0, bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        delete[] txtCmd;

        return true;
    }


};