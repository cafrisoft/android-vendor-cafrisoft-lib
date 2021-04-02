#include <Comm/Global/BuildOptions.h>
#define CLOG_TAG "CommSocketTCPClient"
#include <Comm/Socket/TCP/TCPClient.hpp>
#include <Comm/Socket/TCP/TCPClientWin.hpp>
#include <Comm/Socket/TCP/TCPClientLinux.hpp>
#include <Comm/OAL/Lock.hpp>
#include <Comm/OAL/Log.hpp>

namespace Comm {
    namespace Socket {
        namespace TCP {

            std::shared_ptr<Client> Client::CreateObject(const char* serverAddr, int portNum) {

                std::shared_ptr<Client> obj;
#if (CommOS==CommOS_WIN)
                obj = std::make_shared<ClientWin>(serverAddr, portNum);
#elif (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)
                obj = std::make_shared<ClientLinux>(serverAddr, portNum);
#else
#error "OS is not defined"
#endif
                assert(obj);

            
                return obj;
            }


            Client::Client(const char* serverAddr, int portNum, int id) :
                _PortNum(portNum)
                ,_ID(id)

                , _RcvPackQueueFront(0)
                , _RcvPackQueueRear(0)
            {
                if (serverAddr != NULL) {
                    strcpy(_ServerAddr, serverAddr);
                }
                else {
                    strcpy(_ServerAddr, "0.0.0.0");
                }

                _CsRcvPackSync = Comm::OAL::CriticalSection::CreateObject();
                assert(_CsRcvPackSync);
            }
            
            Client::~Client() {

            }

            int Client::GetID() {
                return _ID;
            }

            int Client::GetPortNum() {
                return _PortNum;
            }

            const char* Client::GetServerAddr() {
            
                strcpy(_ServerAddrBuff, _ServerAddr);
                return (const char* )_ServerAddrBuff;
            }

            bool Client::SetServerAddr(const char* serverIPAddr) {

                bool bRet = false;

                if (!this->IsConnect()) {
                    strcpy(_ServerAddr, serverIPAddr);
                    bRet = true;
                }

                return true;
            }

            bool Client::Send(std::shared_ptr<NetPacket> pack) {
            
                bool bRet;
                int packByteSize = pack->GetBufByteSize();
                unsigned char* packData = new unsigned char[packByteSize];
                assert(packData);

                pack->GetNetPacketData(packData);
                bRet = this->Send(packData, packByteSize);

                delete[] packData;

                return bRet;
            }

            bool Client::Receive(std::shared_ptr<NetPacket> pack) {
            
                bool bRet = false;
                int rcvByteSize = 0;
                int packByteSize = pack->GetBufByteSize();
                unsigned char* buf = new unsigned char[packByteSize];
                assert(buf);

                bRet = this->Receive(buf, packByteSize, &rcvByteSize);
                if (bRet) {
                    bRet = pack->SetNetPacketData(buf, rcvByteSize);
                }
                delete[] buf;

                return bRet;
            }

            #define RCVPACKQUEUE_BYTESIZE() (_RcvPackQueueRear>=_RcvPackQueueFront) ? \
                            (_RcvPackQueueRear-_RcvPackQueueFront) : \
                            ((_RcvPackQueueBufByteSize-_RcvPackQueueFront)+_RcvPackQueueRear)

            
            //��û�ϴ� ũ�⸸ŭ �޾ƿ��� ���� �����Ѵ�. 
            bool Client::ReceiveSync(/*out*/ unsigned char* data, int reqPackByteSize) {
            
                bool isSocketAbort = false;
                int queueByteSize;
                unsigned char* sockRcvBuf = new unsigned char[reqPackByteSize];
                assert(sockRcvBuf);
                Comm::OAL::Lock lock(_CsRcvPackSync);

                queueByteSize = RCVPACKQUEUE_BYTESIZE();

                //CLOGD("F:%d R:%d queSz:%d ", _RcvPackQueueFront, _RcvPackQueueRear, queueByteSize);

                //ť�� ����ִ� ������, ��û�ϴ� ũ�⺸�� �ݵ�� Ŀ�� �Ѵ�.
                assert( (reqPackByteSize+128) < (_RcvPackQueueBufByteSize- queueByteSize) );
                                
                while (true) {
                    
                    queueByteSize = RCVPACKQUEUE_BYTESIZE();
                    
                    //ť�� ����� ����Ÿ ũ�Ⱑ �䱸�ϴ� ũ�⺸�� �����Ƿ�, �����κ��� ����Ÿ�� �޴´�. 
                    if (queueByteSize < reqPackByteSize) {
                        bool bRet;
                        int rdsz;
                        bRet = this->Receive(sockRcvBuf, reqPackByteSize, &rdsz);
                        if (bRet) {

                            //CLOGD("Add0 F:%d R:%d queSz:%d rdsz:%d ", _RcvPackQueueFront, _RcvPackQueueRear, queueByteSize, rdsz);

                            if ( (_RcvPackQueueRear + rdsz) >= _RcvPackQueueBufByteSize) {
                                 /*
                                      ������ ����Ÿ�� �׳� �����ϸ� Overflow�� �߻��ϹǷ� ����� ���� 
                                 */
                                int copyByteSize1st = _RcvPackQueueBufByteSize - _RcvPackQueueRear;
                                int copyByteSize2nd = rdsz - copyByteSize1st;
                                memcpy(&_RcvPackQueuBuf[_RcvPackQueueRear], &sockRcvBuf[0], copyByteSize1st);
                                if (copyByteSize2nd > 0) {
                                    memcpy(&_RcvPackQueuBuf[0], &sockRcvBuf[copyByteSize1st], copyByteSize2nd);
                                }
                                _RcvPackQueueRear = copyByteSize2nd;
                            }
                            else {
                                /*
                                     ������ ����Ÿ�� �׳� �����ϰ�, RearPtr�� �����ȴ�. 
                                */
                                memcpy(&_RcvPackQueuBuf[_RcvPackQueueRear], &sockRcvBuf[0], rdsz);
                                _RcvPackQueueRear += rdsz;
                            }

                            //CLOGD("Add1 F:%d R:%d queSz:%d rdsz:%d ", _RcvPackQueueFront, _RcvPackQueueRear, RCVPACKQUEUE_BYTESIZE(), rdsz);
                        }
                        else {
                            isSocketAbort = true;
                            break;
                        }
                    }
                    else {
                        break;
                    }

                }

                if (isSocketAbort == false) {

                    queueByteSize = RCVPACKQUEUE_BYTESIZE();

                    //ť�� �ʿ��� ���۵���Ÿ�� �ݵ�� ä���� �־�� �Ѵ�. 
                    assert(queueByteSize >= reqPackByteSize);

                    //CLOGD("Del0 F:%d R:%d queSz:%d ", _RcvPackQueueFront, _RcvPackQueueRear, RCVPACKQUEUE_BYTESIZE());

                    if (_RcvPackQueueRear >= _RcvPackQueueFront) {

                        /*
                            ...  [Front_Ptr] ....[Rear_Ptr] ...  [EndBuf]

                            [Front_Ptr] ���� [Rer_Ptrf] ���� �䱸�ϴ� ����ũ�⺸�� ũ�ų� ���� ���, �ѹ��� �����ϸ� ��
                        */

                        memcpy(data, &_RcvPackQueuBuf[_RcvPackQueueFront], reqPackByteSize);
                        _RcvPackQueueFront += reqPackByteSize;
                    }
                    else {

                        if ((_RcvPackQueueBufByteSize - _RcvPackQueueFront) >= reqPackByteSize) {

                            /*
                                    [Rear_Ptr] ...  [Front_Ptr] .......  [EndBuf]

                                    [Front_Ptr] ���� [EndBuf] ���� �䱸�ϴ� ����ũ�⺸�� ũ�ų� ���� ���, �ѹ��� �����ϸ� ��
                            */
                            memcpy(data, &_RcvPackQueuBuf[_RcvPackQueueFront], reqPackByteSize);
                            _RcvPackQueueFront += reqPackByteSize;
                        }
                        else {

                            /*
                                    [Rear_Ptr] ...  [Front_Ptr] .......  [EndBuf]

                                    [Front_Ptr] ���� [EndBuf] ������ �䱸�ϴ� ����ũ�⺸�� �����Ƿ�,  �ι� �����ؾ� �Ѵ�.
                            */

                            int copyByteSize1st = _RcvPackQueueBufByteSize - _RcvPackQueueFront;
                            int copyByteSize2nd = reqPackByteSize - copyByteSize1st;

                            memcpy(&data[0], &_RcvPackQueuBuf[_RcvPackQueueFront], copyByteSize1st);
                            memcpy(&data[copyByteSize1st], &_RcvPackQueuBuf[0], copyByteSize2nd);
                            _RcvPackQueueFront = copyByteSize2nd;  //Front Ptr�� �ѹ��� ����. 
                        }

                    }

                    //CLOGD("Del1 F:%d R:%d queSz:%d ", _RcvPackQueueFront, _RcvPackQueueRear, RCVPACKQUEUE_BYTESIZE());

                }  // end of if (isSocketAbort == false) {

                delete[] sockRcvBuf;

                return !isSocketAbort;
            }

        }; //namespace TCP
    }; //namespace Socket {
}; // namespace Comm {

