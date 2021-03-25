#define CLOG_TAG "CommSocketNetPacketFixed"
#include <Comm/Socket/NetPacketFixed.hpp>
#include <Comm/Utils/CRC.hpp>
#include <Comm/OAL/DateTime.hpp>
#include <Comm/OAL/System.hpp>
#include <Comm/OAL/Log.hpp>

namespace Comm {
    namespace Socket {

        NetPacketFixed::NetPacketFixed(int packByteSize, int hdrSize, int payloadSize, const unsigned char* data) :

            _PackByteSize(packByteSize)
            , _HeaderByteSize(hdrSize)
            , _PayloadByteSize(payloadSize)

        {
            //CLOGI("packByteSize = %d", packByteSize);
            //CLOGI("hdrSize = %d", hdrSize);
            //CLOGI("payloadSize = %d", payloadSize);
            //CLOGI("_FristHeaderByteSize + hdrSize + payloadSize + _CrcByteSize = %d", _FristHeaderByteSize + hdrSize + payloadSize + _CrcByteSize);

            assert((int)sizeof(struct FirstHeader) <= _FristHeaderByteSize);
            assert((_FristHeaderByteSize + hdrSize + payloadSize + _CrcByteSize) <= packByteSize);

            _PackData = new unsigned char[packByteSize];
            assert(_PackData);
            _FirstHeader = (struct FirstHeader*)_PackData;

            if (data != NULL) {
                memcpy(_PackData, data, _PackByteSize);
            }
            else {
                memset(_PackData, 0x00, packByteSize);
                this->GenPacketTime();
            }
        }


        NetPacketFixed::NetPacketFixed(std::shared_ptr<NetPacketFixed> pack) :
            _PackByteSize(pack->_PackByteSize)
            , _HeaderByteSize(pack->_HeaderByteSize)
        {
        
            _PackData = new unsigned char[_PackByteSize];
            assert(_PackData);

            
            if (pack->_PackData != NULL) {
                memcpy(_PackData, pack->_PackData, _PackByteSize);
            }
            else {
                memset(_PackData, 0x00, _PackByteSize);
            }

        }

        NetPacketFixed::~NetPacketFixed() {

            if (_PackData) {
                delete[] _PackData;
            }
        }
        unsigned char* NetPacketFixed::GetBufPtr() {

            unsigned char* ptr = &_PackData[0];
            return ptr;
        }
        
        unsigned char* NetPacketFixed::GetHeaderPtr() {
        
            unsigned char* ptr = &_PackData[NetPacketFixed::GetHeaderByteOffset()];
            return ptr;
        }

        unsigned char* NetPacketFixed::GetPayloadPtr() {
            unsigned char* ptr = &_PackData[_FristHeaderByteSize + _HeaderByteSize];
            return ptr;
        }
                
        int NetPacketFixed::GetBufByteSize() {
            
            return _PackByteSize;
        }

        void NetPacketFixed::GenPacketTime() {
        
            _FirstHeader->_UtcTime = Comm::OAL::DateTime::GetUtcTime();
            _FirstHeader->_MileSec = Comm::OAL::System::GetTickCount32() % 1000;
        }

        time_t NetPacketFixed::GetUtcTime() {

            return _FirstHeader->_UtcTime;
        }

        void NetPacketFixed::SetUtcTime(time_t t) {
        
            _FirstHeader->_UtcTime = t;
        }

        int NetPacketFixed::GetMileSec() {
        
            return _FirstHeader->_MileSec;
        }

        bool NetPacketFixed::SetNetPacketData(unsigned char* packData, int packDataByteSize) {

            bool bRet = true;

            //패킷 크기 체크 
            if (bRet) {
                if (packDataByteSize != this->GetBufByteSize()) {
                    bRet = false;
                }
            }

            //CRC체크
            if (bRet) {
                bRet = NetPacket::IsMatchCRC(packData, packDataByteSize);
            }

            if (bRet) {
                memcpy(_PackData, packData, packDataByteSize);
            }

            return bRet;
        }

        
    }; //namespace Socket {
}; // namespace Comm {

