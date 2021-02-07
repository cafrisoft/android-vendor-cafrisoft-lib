#ifndef COMM_API_PACKET_HPP__
#define COMM_API_PACKET_HPP__

namespace Comm {
    namespace API {

        struct PacketHdr {
            int _HeaderByteSize;
            int _PayloadByteSize;

            long long _ReceiveTime;  // x64/x32 모두 8 byte
            unsigned int _ReceiveTick;

            int res;  //8byte align을 맞춰야 한다. 
        };

    };
};


#endif

