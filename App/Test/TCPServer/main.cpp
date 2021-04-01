#include <Comm/Global/BuildOptions.h>
#include <Comm/Socket/TCP/TCPServer.hpp>

/*
�� ���α׷��� TCP Server Socket��  ����ϴ� LoopBack ���� ���α׷��̴�. 
Ŭ���̾�Ʈ�κ��� ������ ����Ÿ�� ��������, Ŭ���̾�Ʈ�� �ٽ� Back�ϸ�,  ���� ������ ������  ������� �ֿܼ� ����Ѵ�. 
*/
using namespace Comm;

static void TCPServerAcceptCallBackStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> client) {

    PRINTF("Accept ID=%d \n", client->GetID());
}

static void TCPServerReceiveCallBackStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> client, const unsigned char* data, int dataSize) {

    //PRINTF("Receive ID=%d \n", client->GetID());
    //client->Send(data, dataSize);
}

static void TCPServerCloseCallBackStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> client) {

    PRINTF("Close ID=%d \n", client->GetID());
}

int main(int argc, char* argv[]) {

    struct Socket::TCP::Server::CreateConfig  crateConfig = {
        9829,
        4096, //_ReceiveBufSize
        1000, // MaxClientSize 
        TCPServerAcceptCallBackStub,
        TCPServerReceiveCallBackStub,
        TCPServerCloseCallBackStub
    };

    std::shared_ptr<Socket::TCP::Server> server = Socket::TCP::Server::CreateObject(crateConfig);
    assert(server);

    server->LogStart();
    server->SelectLoop(true);

    while (true) {
        Comm::OAL::Thread::Sleep(1000);
    }
    
    return 0;
}


