#include <Comm/Global/BuildOptions.h>
#define CLOG_TAG "SocketTossWorker"
#include <Comm/Socket/Toss/Worker.hpp>

namespace Comm {
    namespace Socket {
        namespace Toss {

            Worker::Worker(int secondaryQueueCount) :
                _IsServiceRun(true)
                , _SecondaryQueueCount(secondaryQueueCount)
            {
                _PacketQueue = std::make_shared<Comm::Utils::SyncQueue<std::shared_ptr<Socket::NetPacket>>>();
                assert(_PacketQueue);


                for (int i = 0; i < _SecondaryQueueCount; i++) {
                    std::shared_ptr<Comm::Utils::SyncQueue<std::shared_ptr<Comm::Socket::NetPacket>>> q = std::make_shared<Comm::Utils::SyncQueue<std::shared_ptr<Socket::NetPacket>>>();
                    _PacketQueueSecondary[i] = q;
                    assert(_PacketQueueSecondary[i]);
                }

                /*
                    ThreadService Start
                */
                _ThreadService = std::make_shared<OAL::ThreadService>(this);
                assert(_ThreadService);
            }

            Worker::~Worker() {

                _IsServiceRun = false;
                _PacketQueue->Push(NULL);
                _ThreadService.reset();

                for (int i = 0; i < _SecondaryQueueCount; i++) {
                    _PacketQueueSecondary[i].reset();
                }

            }
                        
            bool Worker::IsServiceRun() {
                return _IsServiceRun;
            }

            void Worker::WaitForNextService() {

            }

            void Worker::Service() {

                std::shared_ptr<Comm::Socket::NetPacket> pack = _PacketQueue->Pop();
                if (pack) {
                    this->CallbackReceiveFromOtherThread(pack);
                    _TotalReceivedPacketCount++;
                    _ReceivedPacketCount++;
                }
            }

            void Worker::PostPacket(std::shared_ptr<Comm::Socket::NetPacket> pack) {
            
                _PacketQueue->Push(pack);
            }
            
            void Worker::PostPacketToSecondaryQueue(int queuIdx, std::shared_ptr<Comm::Socket::NetPacket> pack) {

                assert((queuIdx >= 0) && (queuIdx < _SecondaryQueueCount));
                _PacketQueueSecondary[queuIdx]->Push(pack);
            }
                        
            std::shared_ptr<Comm::Socket::NetPacket> Worker::ReceivePacketFromSecondaryQueue(int queuIdx) {
                assert((queuIdx >= 0) && (queuIdx < _SecondaryQueueCount));
                return _PacketQueueSecondary[queuIdx]->Pop();
            }

        }; // namespace Toss  
    }; // namespace Socket
};// namespace Comm

