#include "RemotePython.hpp"
#include <TESys/Property/Net.hpp>

/*
이 프로그램은 TCP Server Socket을  사용하는 LoopBack 서버 프로그램이다.
클라이언트로부터 수신한 데이타를 가공없이, 클라이언트에 다시 Back하며,  수신 성능을 측정해  결과값을 콘솔에 출력한다.
*/
using namespace Comm;

static void TCPServerAcceptCallBackStub(void* arg, std::shared_ptr<Socket::TCP::Client> client) {

    PRINTF("Accept ID=%d \n", client->GetID());
}

static void TCPServerReceiveCallBackStub(void* arg, std::shared_ptr<Socket::TCP::Client> client, const unsigned char* data, int dataSize) {

    //PRINTF("Receive ID=%d \n", client->GetID());
    //client->Send(data, dataSize);
    std::shared_ptr<TESys::Net::PacketPython> pack = std::make_shared<TESys::Net::PacketPython>(data);
    switch (pack->GetCommand()) {

        //System
        case TESys::Net::Command::Python::SysDelay: RemotePython::Sys::Delay(client, pack);  break;
        case TESys::Net::Command::Python::SysSetBoardID: RemotePython::Sys::SetBoardID(client, pack);  break;
        case TESys::Net::Command::Python::SysNotifyPyStart: RemotePython::Sys::NotifyPyStart(client, pack);  break;
        case TESys::Net::Command::Python::SysNotifyPyStop: RemotePython::Sys::NotifyPyStop(client, pack);  break;

        //Mipi
        case TESys::Net::Command::Python::MipiReadReg: RemotePython::Mipi::ReadReg(client, pack);  break;
        case TESys::Net::Command::Python::MipiWriteReg:  RemotePython::Mipi::WriteReg(client, pack);  break;
        
        case TESys::Net::Command::Python::MipiWriteReg39:  RemotePython::Mipi::WriteReg39(client, pack);  break;   //WREG0=0x39, [Addr], [regVal0], [regVal1].....
        case TESys::Net::Command::Python::MipiWriteReg15:  RemotePython::Mipi::WriteReg15(client, pack);  break;   //WREG0=0x15, [Addr], [regVal]
        case TESys::Net::Command::Python::MipiWriteReg05:  RemotePython::Mipi::WriteReg05(client, pack);  break;   //WREG0=0x05, [Addr]
        case TESys::Net::Command::Python::MipiWriteReg07:  RemotePython::Mipi::WriteReg07(client, pack);  break;   //WREG0=0x05, [Addr]

        //DD(Display Driver) Command
        case TESys::Net::Command::Python::DD_set_fb0_blank:  RemotePython::DD::set_fb0_blank(client, pack);  break;
        case TESys::Net::Command::Python::DD_set_dsim_manual_ctrl:  RemotePython::DD::set_dsim_manual_ctrl(client, pack);  break;

        //TxtCmd
        case TESys::Net::Command::Python::TxtCmdSend:  RemotePython::TxtCmd::Send(client, pack);  break;

        //Pattern
        case TESys::Net::Command::Python::PatternSetCommand:  RemotePython::Pattern::SetCommand(client, pack);  break;

        //Debug
        case TESys::Net::Command::Python::DebugFuncEnter:  RemotePython::Debug::FuncEnter(client, pack);  break;
        case TESys::Net::Command::Python::DebugFuncLeave:  RemotePython::Debug::FuncLeave(client, pack);  break;
        case TESys::Net::Command::Python::DebugMessage:  RemotePython::Debug::Message(client, pack);  break;

        //VLIN1_ADC
        case TESys::Net::Command::Python::Vlin1AdcSetSamples:    RemotePython::Vlin1Adc::SetSamples(client, pack);  break;
        case TESys::Net::Command::Python::Vlin1AdcSetInterval:   RemotePython::Vlin1Adc::SetInterval(client, pack);  break;
        case TESys::Net::Command::Python::Vlin1AdcSetChannelOn:  RemotePython::Vlin1Adc::SetChannelOn(client, pack);  break;
        case TESys::Net::Command::Python::Vlin1AdcSetChannelOff: RemotePython::Vlin1Adc::SetChannelOff(client, pack);  break;
        case TESys::Net::Command::Python::Vlin1AdcSetMode:       RemotePython::Vlin1Adc::SetMode(client, pack);  break;

        case TESys::Net::Command::Python::Vlin1AdcGetVoltage:      RemotePython::Vlin1Adc::GetVoltage(client, pack);  break;
        case TESys::Net::Command::Python::Vlin1AdcGetVoltageVLIN1: RemotePython::Vlin1Adc::GetVoltageVLIN1(client, pack);  break;
        case TESys::Net::Command::Python::Vlin1AdcGetVoltageVBAT:  RemotePython::Vlin1Adc::GetVoltageVBAT(client, pack);  break;
        case TESys::Net::Command::Python::Vlin1AdcGetVoltageELVDD: RemotePython::Vlin1Adc::GetVoltageELVDD(client, pack);  break;
        case TESys::Net::Command::Python::Vlin1AdcGetCurrent:      RemotePython::Vlin1Adc::GetCurrent(client, pack);  break;
        case TESys::Net::Command::Python::Vlin1AdcGetCurrentVLIN1: RemotePython::Vlin1Adc::GetCurrentVLIN1(client, pack);  break;
        case TESys::Net::Command::Python::Vlin1AdcGetCurrentVBAT:  RemotePython::Vlin1Adc::GetCurrentVBAT(client, pack);  break;
        case TESys::Net::Command::Python::Vlin1AdcGetCurrentELVDD: RemotePython::Vlin1Adc::GetCurrentELVDD(client, pack);  break;


        //VCI_ADC
        case TESys::Net::Command::Python::VciAdcSetSamples:    RemotePython::VciAdc::SetSamples(client, pack);  break;
        case TESys::Net::Command::Python::VciAdcSetInterval:   RemotePython::VciAdc::SetInterval(client, pack);  break;
        case TESys::Net::Command::Python::VciAdcSetChannelOn:  RemotePython::VciAdc::SetChannelOn(client, pack);  break;
        case TESys::Net::Command::Python::VciAdcSetChannelOff: RemotePython::VciAdc::SetChannelOff(client, pack);  break;
        case TESys::Net::Command::Python::VciAdcSetMode:       RemotePython::VciAdc::SetMode(client, pack);  break;

        case TESys::Net::Command::Python::VciAdcGetVoltage:      RemotePython::VciAdc::GetVoltage(client, pack);  break;
        case TESys::Net::Command::Python::VciAdcGetVoltageVCI: RemotePython::VciAdc::GetVoltageVCI(client, pack);  break;
        case TESys::Net::Command::Python::VciAdcGetVoltageVDDR:  RemotePython::VciAdc::GetVoltageVDDR(client, pack);  break;
        case TESys::Net::Command::Python::VciAdcGetVoltageVDDI: RemotePython::VciAdc::GetVoltageVDDI(client, pack);  break;
        case TESys::Net::Command::Python::VciAdcGetCurrent:      RemotePython::VciAdc::GetCurrent(client, pack);  break;
        case TESys::Net::Command::Python::VciAdcGetCurrentVCI: RemotePython::VciAdc::GetCurrentVCI(client, pack);  break;
        case TESys::Net::Command::Python::VciAdcGetCurrentVDDR:  RemotePython::VciAdc::GetCurrentVDDR(client, pack);  break;
        case TESys::Net::Command::Python::VciAdcGetCurrentVDDI: RemotePython::VciAdc::GetCurrentVDDI(client, pack);  break;

        //SDOUT ADC
        case TESys::Net::Command::Python::SoutAdcSetDevConfig:    RemotePython::SoutAdc::SetDevConfig(client, pack);  break;
        case TESys::Net::Command::Python::SoutAdcSetInConfig:    RemotePython::SoutAdc::SetInConfig(client, pack);  break;
        case TESys::Net::Command::Python::SoutAdcSetRBSel:    RemotePython::SoutAdc::SetRBSel(client, pack);  break;
        case TESys::Net::Command::Python::SoutAdcGetChannelCount:    RemotePython::SoutAdc::GetChannelCount(client, pack);  break;
        case TESys::Net::Command::Python::SoutAdcGetVoltage:    RemotePython::SoutAdc::GetVoltage(client, pack);  break;
        case TESys::Net::Command::Python::SoutAdcGetAllVoltage:    RemotePython::SoutAdc::GetAllVoltage(client, pack);  break;

        //LDO ADC
        case TESys::Net::Command::Python::LdoAdcSetInConfig:    RemotePython::LdoAdc::SetInConfig(client, pack);  break;
        case TESys::Net::Command::Python::LdoAdcGetChannelCount:    RemotePython::LdoAdc::GetChannelCount(client, pack);  break;
        case TESys::Net::Command::Python::LdoAdcGetVoltage:    RemotePython::LdoAdc::GetVoltage(client, pack);  break;
        case TESys::Net::Command::Python::LdoAdcGetAllVoltage:    RemotePython::LdoAdc::GetAllVoltage(client, pack);  break;

        //REG ADC
        case TESys::Net::Command::Python::RegAdcSetInConfig:    RemotePython::RegAdc::SetInConfig(client, pack);  break;
        case TESys::Net::Command::Python::RegAdcGetChannelCount:    RemotePython::RegAdc::GetChannelCount(client, pack);  break;
        case TESys::Net::Command::Python::RegAdcGetVoltage:    RemotePython::RegAdc::GetVoltage(client, pack);  break;
        case TESys::Net::Command::Python::RegAdcGetAllVoltage:    RemotePython::RegAdc::GetAllVoltage(client, pack);  break;

        //Measure
        case TESys::Net::Command::Python::AgingMeasureADC:    RemotePython::Aging::MeasureADC(client, pack);  break;
        case TESys::Net::Command::Python::AgingSetCurJobInfo:    RemotePython::Aging::SetCurJobInfo(client, pack);  break;
        case TESys::Net::Command::Python::AgingSetCurSCInfo:    RemotePython::Aging::SetCurSCInfo(client, pack);  break;
        case TESys::Net::Command::Python::AgingSetCurTCInfo:    RemotePython::Aging::SetCurTCInfo(client, pack);  break;

        case TESys::Net::Command::Python::AgingSetCurTCStepInfo:    RemotePython::Aging::SetCurTCStepInfo(client, pack);  break;
    }

}

static void TCPServerCloseCallBackStub(void* arg, std::shared_ptr<Socket::TCP::Client> client) {

    PRINTF("Close ID=%d \n", client->GetID());
}

int main(int argc, char* argv[]) {

    struct Socket::TCP::Server::CreateConfig  crateConfig = {
        TESys::Property::Net::GetRemotePythonTcpPort(),
        TESys::Net::PacketPython::GetFixedPacketByteSize(), // 서버가 packet단위로 데이타를 읽을수 있도록 한다. 
        10, // MaxClientSize 
        TCPServerAcceptCallBackStub,
        TCPServerReceiveCallBackStub,
        TCPServerCloseCallBackStub
    };

    Comm::OAL::System::SocketInit();
    Comm::OAL::Log::SysLogOpen(CLOG_TAG);
    Comm::OAL::Log::EnableDebug();


    std::shared_ptr<Socket::TCP::Server> server = Socket::TCP::Server::CreateObject(crateConfig);
    assert(server);

    CLOGI("Server Start..   Port(%d) ", TESys::Property::Net::GetRemotePythonTcpPort());

    //server->LogStart();
    server->SelectLoop();

    Comm::OAL::Log::SysLogClose();

    return 0;
}


