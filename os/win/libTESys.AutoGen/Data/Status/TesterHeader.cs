using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.Data.Status
{
    public class TesterHeader
    {
#if false
            struct TesterHeader {
                time_t NotifyUtcTime;
                int Key;
                int StructBoardByteSize;
                int StructAgingByteSize;
                int StructFileSyncByteSize;
                /*
                   주의) 하위버젼 호환을 위해 Param추가시  구조체 맨아래에 추가해야 한다. 8byte Align 유의
                */
            };
#endif
        private long _NotifyUtcTime;
        private int _Key;
        private int _StructBoardByteSize;
        private int _StructAgingByteSize;
        private int _StructFileSyncByteSize;

        public TesterHeader(IntPtr rawByteData, int dataOffset)
        {
            _NotifyUtcTime = Marshal.ReadInt64(rawByteData, dataOffset); dataOffset += 8;
            _Key = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _StructBoardByteSize = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _StructAgingByteSize = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _StructFileSyncByteSize = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;

        }

        public long NotifyUtcTime {  get { return _NotifyUtcTime;  } }
    }
}
