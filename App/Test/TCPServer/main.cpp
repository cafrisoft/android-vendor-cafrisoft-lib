#include <Comm/Global/BuildOptions.h>
#include <Comm/Socket/TCP/TCPServer.hpp>

/*
이 프로그램은 TCP Server Socket을  사용하는 LoopBack 서버 프로그램이다. 
클라이언트로부터 수신한 데이타를 가공없이, 클라이언트에 다시 Back하며,  수신 성능을 측정해  결과값을 콘솔에 출력한다. 
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


