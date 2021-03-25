#define CLOG_TAG "SocketNetPacket"
#include <Comm/Socket/NetPacket.hpp>
#include <Comm/Utils/HeaderFiles.hpp>
#include <Comm/OAL/Log.hpp>

namespace Comm {
    namespace Socket {

        NetPacket::NetPacket() {

        }

        NetPacket::~NetPacket() {

        }
                
        bool NetPacket::GenCRC() {

            bool bRet;

            bRet = NetPacket::GenCRC(this->GetBufPtr(), this->GetBufByteSize());
            return bRet;
        }

        bool NetPacket::GetNetPacketData(unsigned char* packData) {
            
            memcpy(packData, this->GetBufPtr(), this->GetBufByteSize());
            return true;
        }

        bool NetPacket::IsMatchCRC(unsigned char* packData, int packDataByteSize) {
        
            //int crc16Cal = Comm::Utils::CRC16((char*)packData, packDataByteSize - 2, 0);
            unsigned short crc16Cal = Comm::Utils::CheckSum16Bit((char*)packData, packDataByteSize - 2, 0);
            unsigned short crc0, crc1, crc16;
            bool bRet;

            crc0 = (unsigned short)packData[packDataByteSize - 2]&0xFF;
            crc1 = (unsigned short)packData[packDataByteSize - 1]&0xFF;

            crc16 = crc0 | ((crc1 << 8) & 0xFF00);

            if (crc16 == crc16Cal) {
                bRet = true;
            }
            else {
                bRet = false;
            }

            return bRet;
        }

        bool NetPacket::GenCRC(unsigned char* packData, int packDataByteSize) {
        
            //int crc16 = Comm::Utils::CRC16((char*)packData, packDataByteSize - 2, 0);
            unsigned short crc16 = Comm::Utils::CheckSum16Bit((char*)packData, packDataByteSize - 2, 0);
            packData[packDataByteSize - 2] = crc16 & 0xFF;
            packData[packDataByteSize - 1] = (crc16 >> 8) & 0xFF;

            return true;
        }

    }; //namespace Socket {
}; // namespace Comm {

