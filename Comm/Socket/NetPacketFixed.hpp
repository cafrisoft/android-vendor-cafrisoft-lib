#ifndef COMM_SOCKET_NETFIXEDPACKET_HPP__
#define COMM_SOCKET_NETFIXEDPACKET_HPP__

#include <Comm/Socket/NetPacket.hpp>

namespace Comm {
    namespace Socket {
        
        class NetPacketFixed : public NetPacket {

        private:
            int _PackByteSize;
            int _HeaderByteSize;
            unsigned char* _PackData;

        protected:
            NetPacketFixed(int packByteSize, int hdrSize, const unsigned char* data=NULL);
            NetPacketFixed(std::shared_ptr<NetPacketFixed> pack);
            virtual ~NetPacketFixed();

        protected:
            virtual unsigned char* GetPtr();
            virtual unsigned char* GetHeaderPtr();
            virtual unsigned char* GetPayloadPtr();

        public:
            virtual int GetByteSize();
                    
            //네트워크로부터 수신한 패킷데이타를 입력한다. CRC체크와 패킷크기 체크를 수행한다. 
            virtual bool SetNetPacketData(unsigned char* packData, int packDataByteSize);

        };

        
    }; //namespace Socket {
}; // namespace Comm {

#endif //#ifndef COMM_SOCKET_NETFIXEDPACKET_HPP__
