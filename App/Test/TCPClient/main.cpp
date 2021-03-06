#include <Comm/Global/BuildOptions.h>
#include <Comm/Socket/TCP/TCPServer.hpp>
#include <Comm/Utils/IntegerCount.hpp>

using namespace Comm;

//#pragma comment (lib, "Ws2_32.lib")

#define BUFSIZE 1024
#define TEST_DUR_SEC 3600
#define TEST_DUR_TICK (TEST_DUR_SEC*1000)

int main(int argc, char* argv[]) {

    bool bRet;
    unsigned char buf[BUFSIZE];
    long long startTick = OAL::System::GetTickCount64();
    long long beforeTick = startTick;
    long long curTick;
    
    Utils::IntegerCount sendCnt;
    Utils::IntegerCount rcvCnt;


    //std::shared_ptr<Socket::TCP::Client> client = Socket::TCP::Client::CreateObject("192.168.100.1", 9829);
    std::shared_ptr<Socket::TCP::Client> client = Socket::TCP::Client::CreateObject("192.168.100.73", 9829);
    assert(client);

    bRet = client->Connect();
    if (bRet) {
        
        PRINTF("OK : connect \n");

        while (true) {
        
            int rdsz = 0;

            memset(buf, 0x00, BUFSIZE);
            client->Send((const unsigned char*)buf, BUFSIZE);
            //client->Receive(buf, BUFSIZE, &rdsz);

            sendCnt += BUFSIZE;
            rcvCnt += rdsz;


            curTick = OAL::System::GetTickCount64();
            if ((curTick - startTick) > (TEST_DUR_TICK)) {
                break;
            }

            if ((curTick - beforeTick) > 1000LL) {
                PRINTF("%lld. send=%d rcv=%d ", (curTick - startTick) / 1000LL, sendCnt.GetCount(), rcvCnt.GetCount());
                sendCnt.Reset();
                rcvCnt.Reset();
                beforeTick = curTick;
            }
        }
        

        client->Disconnect();
    }
    else {
        PRINTF("FAIL : connect \n");
    }

    return 0;
}
