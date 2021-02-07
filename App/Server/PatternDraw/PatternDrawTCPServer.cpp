#include "PatternDraw.hpp"
#include <TESys/Property/Hub.hpp>
#include <TESys/Property/Net.hpp>
#include <Comm/Socket/MyRILPacket.h>


PatternDraw::TCPServer::TCPServer(PatternDraw* notifier) :
    
    _PatternDraw(notifier)
{
    //Packet Queue¡íy¨ù¨¬
    _PacketQueue = std::make_shared<Comm::Utils::SyncQueue<std::shared_ptr<TESys::Net::PacketDataAcq>>>();
    assert(_PacketQueue);
    CLOGI("[PatternDraw::TCPServer] PacketQueue Create ... OK");

    /*
        TCPServer Notify TCP ¨ù¡©©öo ¨ùOAI ¡íy¨ù¨¬
    */
    struct Comm::Socket::TCP::Server::CreateConfig  createConfig = {
        TESys::Property::Net::GetPatternDrawAppTcpPort(),
        512,
        500,
        PatternDraw::TCPServer::CallbackAcceptStub,
        PatternDraw::TCPServer::CallbackReceiveStub,
        PatternDraw::TCPServer::CallbackCloseStub,
        this
    };

    _SrvTcpSock = Comm::Socket::TCP::Server::CreateObject(createConfig);
    assert(_SrvTcpSock);

    _SrvTcpSock->SelectLoop(true);
    CLOGI("[PatternDraw::TCPServer] TCPServerSocket Create ... OK (Port=%d)", _SrvTcpSock->GetPortNum());


    //ThreadService Start
    //_ThreadService = std::make_shared<Comm::OAL::ThreadService>(this);
    //assert(_ThreadService);
}

bool PatternDraw::TCPServer::BroadCast(std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack) {
    
    _PacketQueue->Push(notifyPack);
    return true;
}


void PatternDraw::TCPServer::CallbackAcceptStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> client) {
    PatternDraw::TCPServer* pObj = (PatternDraw::TCPServer*)arg;
    pObj->CallbackAccept(client);
}

void PatternDraw::TCPServer::CallbackReceiveStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> client, const unsigned char* data, int dataSize) {
    PatternDraw::TCPServer* pObj = (PatternDraw::TCPServer*)arg;
    pObj->CallbackReceive(client, data, dataSize);
}

void PatternDraw::TCPServer::CallbackCloseStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> client) {
    PatternDraw::TCPServer* pObj = (PatternDraw::TCPServer*)arg;
    pObj->CallbackClose(client);
}

void PatternDraw::TCPServer::CallbackAccept(std::shared_ptr<Comm::Socket::TCP::Client> client) {
    
    CLOGI("[PatternDraw::TCPServer] Accept from DataAcqTCPServer (ID-%d RcvBuf=%d SendBuf=%d)", client->GetID(), client->GetRcvSocketBufferByteSize(), client->GetSendSocketBufferByteSize());
}

void PatternDraw::TCPServer::CallbackReceive(std::shared_ptr<Comm::Socket::TCP::Client> client, const unsigned char* data, int dataSize) {
    
    CLOGI("[PatternDraw::TCPServer] Receive %d bytes", dataSize);

    unsigned char pack_buf[RIL_SRV_PACKET_BUF_SIZE];
    int rdsz = 0;
    struct ril_srv_packet_header* p_header_req;
    struct ril_srv_packet_payload_req* p_payload_req;


    //client->Receive(pack_buf, RIL_SRV_PACKET_BUF_SIZE, &rdsz);

    if (dataSize == RIL_SRV_PACKET_BUF_SIZE) {
        
        if (RIL_SRV_PACKET_IS_VALID(data)) {
            //printf("[rilsrv_worker::service(sock:%d)] invalid packet \n", m_fd_socket);
            //continue;

            p_header_req = (struct ril_srv_packet_header*)RIL_SRV_PACKET_GET_HEADER_PTR((unsigned char*)data);
            //p_header->token = m_fd_socket;
            //RIL_SRV_PACKET_UPDATE_CHECKSUM(pack_buf);
            p_payload_req = (struct ril_srv_packet_payload_req*)RIL_SRV_PACKET_GET_PAYLOAD_PTR((unsigned char*)data);
            //scr_id = p_payload_req->int_param[0];
            //par1 = p_payload_req->int_param[1];
            //par2 = p_payload_req->int_param[2];
            int szlen = p_payload_req->int_param[1];
            char* cmd = (char*)p_payload_req->data1;

            CLOGI("[PatternDraw::TCPServer] CMD=[%s] ", cmd);

            unsigned int msg = RIL_SRV_USIMOTA_RESP_DISPLAY_SCREEN;
            unsigned int token = p_header_req->token;
            unsigned int payload_size = sizeof(struct ril_srv_packet_payload_resp);
            struct ril_srv_packet_payload_resp payload_resp;
            payload_resp.res = 0; //SUCCESS
            RIL_SRV_PACKET_MAKE(pack_buf, token, msg, payload_size, (struct ril_srv_packet_payload_req*)&payload_resp);
            client->Send(pack_buf, RIL_SRV_PACKET_BUF_SIZE);
        }

    }


}

void PatternDraw::TCPServer::CallbackClose(std::shared_ptr<Comm::Socket::TCP::Client> client) {
    
}

void PatternDraw::TCPServer::Service() {
    
    
}

void PatternDraw::TCPServer::WaitForNextService() {
    
}

bool PatternDraw::TCPServer::IsServiceRun() {
    return false;
}

    
    
