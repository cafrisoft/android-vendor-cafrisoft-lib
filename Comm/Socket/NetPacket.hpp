#ifndef COMM_SOCKET_NETPACKET_HPP__
#define COMM_SOCKET_NETPACKET_HPP__

#include <Comm/Base/Object.hpp>

namespace Comm {
    namespace Socket {
        
        class NetPacket : public Base::Object {

        protected:
            NetPacket();
            virtual ~NetPacket();

        protected:
            virtual unsigned char* GetPtr() = 0;
            virtual unsigned char* GetHeaderPtr() = 0;
            virtual unsigned char* GetPayloadPtr() = 0;

        public:
            virtual int GetByteSize() = 0;  //패킷 크기값 리턴
            
            //네트워크로부터 수신한 패킷데이타를 입력한다. CRC체크와 패킷크기 체크를 수행한다. 
            virtual bool SetNetPacketData(unsigned char* packData, int packDataByteSize) = 0;
            bool GetNetPacketData(unsigned char* packData);
            
            //현재 패킷끝 2바이트에 CRC값을 쓴다.  패킷구성완료시 이 함수 반드시 호출해야 한다. 
            virtual bool GenCRC();    

        public:
            /* Static 함수 */
            static bool GenCRC(unsigned char* packData, int packDataByteSize);
            static bool IsMatchCRC(unsigned char* packData, int packDataByteSize);
        };

        
    }; //namespace Socket {
}; // namespace Comm {

#endif //COMM_DATAEX_PRODUCER_HPP__
