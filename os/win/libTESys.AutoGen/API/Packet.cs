using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.API
{
    public abstract class Packet
    {
#if false
        struct PacketHdr
        {
            int _HeaderByteSize;
            int _PayloadByteSize;

            long long _ReceiveTime;  // x64/x32 모두 8 byte
            unsigned int _ReceiveTick;

            int res;  //8byte align을 맞춰야 한다. 
        };
#endif
        private int _HeaderByteSize;
        private int _PayloadByteSize;

        private long _ReceiveTime;  // x64/x32 모두 8 byte
        private int _ReceiveTick;

        protected Packet(IntPtr rawData, int dataOffset)
        {
            
            _HeaderByteSize = Marshal.ReadInt32(rawData, dataOffset); dataOffset += 4;
            _PayloadByteSize = Marshal.ReadInt32(rawData, dataOffset); dataOffset += 4;
            _ReceiveTime = Marshal.ReadInt64(rawData, dataOffset); dataOffset += 8;
            _ReceiveTick = Marshal.ReadInt32(rawData, dataOffset); dataOffset += 4;

        }
    }
}
