#include <Comm/Socket/NetPacketFixed.hpp>
#include <Comm/Utils/CRC.hpp>

namespace Comm {
    namespace Socket {

        NetPacketFixed::NetPacketFixed(int packByteSize, int hdrSize, const unsigned char* data) :
        
            _PackByteSize(packByteSize)
            , _HeaderByteSize(hdrSize)

        {

            _PackData = new unsigned char[packByteSize];
            assert(_PackData);

            if (data != NULL) {
                memcpy(_PackData, data, _PackByteSize);
            }
            else {
                memset(_PackData, 0x00, packByteSize);
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
        unsigned char* NetPacketFixed::GetPtr() {

            return this->GetHeaderPtr();
        }

        unsigned char* NetPacketFixed::GetHeaderPtr() {
        
            unsigned char* ptr = &_PackData[0];
            return ptr;
        }

        unsigned char* NetPacketFixed::GetPayloadPtr() {
            unsigned char* ptr = &_PackData[_HeaderByteSize];
            return ptr;
        }
                
        int NetPacketFixed::GetByteSize() {
            
            return _PackByteSize;
        }


        bool NetPacketFixed::SetNetPacketData(unsigned char* packData, int packDataByteSize) {

            bool bRet = true;

            //패킷 크기 체크 
            if (bRet) {
                if (packDataByteSize != this->GetByteSize()) {
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

