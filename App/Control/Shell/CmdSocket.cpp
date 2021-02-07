#include "Cmd.hpp"
#include <TESys/Property/Tester.hpp>
#include <TESys/Net/PacketControl.hpp>
#include <Comm/Utils/Queue.hpp>
#include <TESys/Property/FileSync.hpp>
#include <TESys/Property/Tester.hpp>
#include <Comm/Utils/Android.hpp>
#include <Comm/Property/Path.hpp>
#include <TESys/Property/PatternDraw.hpp>
#include <Comm/Socket/UDP/UDPServer.hpp>
#include <TESys/Net/PacketDataAcq.hpp>
#include <Comm/Utils/Android.hpp>

namespace AppControlShell {
    namespace Cmd {
        
        bool Socket::ChkBufSize(int argc, const char** argv) {
        
            //PRINTF("Ckh::BufSize\n");

            Comm::Socket::UDP::Server::CheckSocketBuffer();
            
            return true;
        }

        // TESys::Net::DataAcq Packet ºÐ¼®
        bool Socket::TESysNetDataAcqPacketAnalysis(int argc, const char** argv) {
        
            PRINTF("TESys::Net::PacketDataAcq::GetFixedPacketByteSize() =  %d byte\n", TESys::Net::PacketDataAcq::GetFixedPacketByteSize());
            PRINTF("TESys::Net::PacketDataAcq::GetMaxHeaderByteSize() =  %d byte\n", TESys::Net::PacketDataAcq::GetMaxHeaderByteSize());
            PRINTF("TESys::Net::PacketDataAcq::GetRealHeaderByteSize() =  %d byte\n", TESys::Net::PacketDataAcq::GetRealHeaderByteSize());
            PRINTF("TESys::Net::PacketDataAcq::GetRealPayloadByteSize() =  %d byte\n", TESys::Net::PacketDataAcq::GetRealPayloadByteSize());

            PRINTF("Payload Reserve Byte Size :  %d byte\n", 
                TESys::Net::PacketDataAcq::GetFixedPacketByteSize() - TESys::Net::PacketDataAcq::GetRealHeaderByteSize() - TESys::Net::PacketDataAcq::GetRealPayloadByteSize() -2);

            PRINTF("\n");

            PRINTF("sizeof(unsigned char) = %d byte \n", (int)sizeof(unsigned char));
            PRINTF("sizeof(unsigned short) = %d byte \n", (int)sizeof(unsigned short));
            PRINTF("sizeof(unsigned int) = %d byte \n", (int)sizeof(unsigned int));
            PRINTF("sizeof(long long) = %d byte \n", (int)sizeof(long long));

            return true;
        }

        bool Socket::DisplayInfo(int argc, const char** argv) {
        
            std::string strIP = Comm::Utils::Android::GetIpAddrString("eth0");
            unsigned int intIP = Comm::Utils::Android::GetIpAddrI32("eth0");
            
            PRINTF("IPAddr : %s \n", strIP.c_str());
            PRINTF("IPAddr : 0x%08X \n", intIP);

            return true;
        }
    };
};


