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
            virtual int GetByteSize() = 0;  //��Ŷ ũ�Ⱚ ����
            
            //��Ʈ��ũ�κ��� ������ ��Ŷ����Ÿ�� �Է��Ѵ�. CRCüũ�� ��Ŷũ�� üũ�� �����Ѵ�. 
            virtual bool SetNetPacketData(unsigned char* packData, int packDataByteSize) = 0;
            bool GetNetPacketData(unsigned char* packData);
            
            //���� ��Ŷ�� 2����Ʈ�� CRC���� ����.  ��Ŷ�����Ϸ�� �� �Լ� �ݵ�� ȣ���ؾ� �Ѵ�. 
            virtual bool GenCRC();    

        public:
            /* Static �Լ� */
            static bool GenCRC(unsigned char* packData, int packDataByteSize);
            static bool IsMatchCRC(unsigned char* packData, int packDataByteSize);
        };

        
    }; //namespace Socket {
}; // namespace Comm {

#endif //COMM_DATAEX_PRODUCER_HPP__
