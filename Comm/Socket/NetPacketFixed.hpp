#ifndef COMM_SOCKET_NETFIXEDPACKET_HPP__
#define COMM_SOCKET_NETFIXEDPACKET_HPP__

#include <Comm/Socket/NetPacket.hpp>

namespace Comm {
    namespace Socket {
        
        class NetPacketFixed : public NetPacket {

        private:
            static const int _FristHeaderByteSize = 16;

            struct FirstHeader {
                time_t _UtcTime;
                int  _MileSec;
            };

        private:
            int _PackByteSize;
            int _HeaderByteSize;
            int _PayloadByteSize;
            unsigned char* _PackData;

            struct FirstHeader* _FirstHeader;

        protected:
            NetPacketFixed(int packByteSize, int hdrSize, int payloadSize, const unsigned char* data=NULL);
            NetPacketFixed(std::shared_ptr<NetPacketFixed> pack);
            virtual ~NetPacketFixed();

        protected:
            virtual unsigned char* GetBufPtr();
            virtual unsigned char* GetHeaderPtr();
            virtual unsigned char* GetPayloadPtr();

        public:
            virtual int GetBufByteSize();
            virtual void GenPacketTime();
            virtual time_t GetUtcTime();
            virtual void SetUtcTime(time_t t);
            virtual int GetMileSec();
                    
            //네트워크로부터 수신한 패킷데이타를 입력한다. CRC체크와 패킷크기 체크를 수행한다. 
            virtual bool SetNetPacketData(unsigned char* packData, int packDataByteSize);

        protected:
            static inline int GetHeaderByteOffset() {
                return _FristHeaderByteSize;
            }
        };

        
    }; //namespace Socket {
}; // namespace Comm {

#endif //#ifndef COMM_SOCKET_NETFIXEDPACKET_HPP__
