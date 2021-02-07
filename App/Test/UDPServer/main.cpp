#include <Comm/Global/BuildOptions.h>
#include <Comm/Socket/UDP/UDPServer.hpp>

/*
이 프로그램은 UDP Server Socket을  사용하는 LoopBack 서버 프로그램이다.
클라이언트로부터 수신한 데이타를 가공없이, 클라이언트에 다시 Back하며,  수신 성능을 측정해  결과값을 콘솔에 출력한다.
*/
using namespace Comm;


int main(int argc, char* argv[]) {

    struct Socket::UDP::Server::CreateConfig  crateConfig = {
        9829,
        4096, //_ReceiveBufSize
        1000, // MaxClientSize 
    };

    std::shared_ptr<Socket::UDP::Server> server = Socket::UDP::Server::CreateObject(crateConfig);
    assert(server);

    server->LogStart();
    server->ServiceStart();

    int dataSize;
    int dataMaxSize = 1024 * 16;
    unsigned char* data = new unsigned char[dataMaxSize];
    while (true) {
        server->ServiceReadData(data, 1024 * 16, &dataSize);
        if (dataSize > 0) {
        
        }
        else {
            OAL::Thread::Sleep(1);
        }
    }

    

    return 0;
}


