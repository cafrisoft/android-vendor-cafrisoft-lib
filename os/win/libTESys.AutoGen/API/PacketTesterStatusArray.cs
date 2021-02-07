using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security.Cryptography.X509Certificates;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.API
{
    public class PacketTesterStatusArray
    {
#if false
        //#define PACKET_TESTER_STATUS_ARRAY_MAX_COUNT 500
        struct PacketTesterStatusArray {
            int _ArrayCount;
            int _Res;
            struct TESys::Data::Status::Tester _TesterStatus[PACKET_TESTER_STATUS_ARRAY_MAX_COUNT];
        };
#endif
        private int _ArrayCount;
        private int _Res;
        private Data.Status.Tester[] _TesterStatusArray;

        public PacketTesterStatusArray(IntPtr rawByteData)
        {
            int dataOffset = 0;
            int sizeOfTesterStatus = API.Property.GetInt((int)API.Property.Data.ByteSize_Of_TESys_Data_Status_Struct_Tester);

            _ArrayCount = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _Res = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            
            _TesterStatusArray = new Data.Status.Tester[_ArrayCount];
            for (int i = 0; i < _ArrayCount; i++)
            {
                _TesterStatusArray[i] = new Data.Status.Tester(rawByteData, dataOffset);
                dataOffset += sizeOfTesterStatus;
            }
    
            
        }

        public int Count {  get { return _ArrayCount;  } }

        public Data.Status.Tester this[int idx]
        {
            get
            {
                return _TesterStatusArray[idx];
            }
        }
    }
}
