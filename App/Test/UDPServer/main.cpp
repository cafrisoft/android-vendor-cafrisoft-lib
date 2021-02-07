#include <Comm/Global/BuildOptions.h>
#include <Comm/Socket/UDP/UDPServer.hpp>

/*
�� ���α׷��� UDP Server Socket��  ����ϴ� LoopBack ���� ���α׷��̴�.
Ŭ���̾�Ʈ�κ��� ������ ����Ÿ�� ��������, Ŭ���̾�Ʈ�� �ٽ� Back�ϸ�,  ���� ������ ������  ������� �ֿܼ� ����Ѵ�.
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


