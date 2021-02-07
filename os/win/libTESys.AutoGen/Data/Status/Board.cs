using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.Data.Status
{
    public class Board
    {
#if false
            //#define TESYS_DATA_STATUS_BOARD_FWVer_ByteSize 48
            struct Board {
                
                int BoardID;       //Board ID
                int TESysSWVer;  //TESys Version 
                int TESysHWVer;  //Board HW Version
                int NetIPAddrI32;
                char FWVer[TESYS_DATA_STATUS_BOARD_FWVer_ByteSize];

                time_t StartUtcTime;  //보드 시작 시간 
                /*
                   주의) 하위버젼 호환을 위해 Param추가시  구조체 맨아래에 추가해야 한다. 8byte Align 유의
                */
            };
#endif

        private int _BoardID;       //Board ID
        private int _TESysSWVer;  //TESys Version 
        private int _TESysHWVer;  //Board HW Version
        private int _NetIPAddrI32;
        private string _FWVer;

        private long _StartUtcTime;  //보드 시작 시간 
        private long _ErrFlag;       // 보드 ErrFlag

        private string _ReportFWVer;

        public Board(IntPtr rawByteData, int dataOffset)
        {
            int byteSize_Of_TESys_Data_Status_Struct_Board_FWVer = API.Property.GetInt((int)API.Property.Data.ByteSize_Of_TESys_Data_Status_Struct_Board_FWVer);

            _BoardID = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _TESysSWVer = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _TESysHWVer = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _NetIPAddrI32 = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _FWVer = Marshal.PtrToStringAnsi(rawByteData+dataOffset); dataOffset += byteSize_Of_TESys_Data_Status_Struct_Board_FWVer;
            _StartUtcTime = Marshal.ReadInt64(rawByteData, dataOffset); dataOffset += 8;
            _ErrFlag = Marshal.ReadInt64(rawByteData, dataOffset); dataOffset += 8;

            _ReportFWVer = string.Format($"{_FWVer}-{_TESysSWVer:X3}-{_TESysHWVer:X3}");
        }

        public int BoardID {  get { return _BoardID;  } }
        public string FWVer { 
            get 
            {
                return _ReportFWVer;
            } 
        }
        public string IPAddrString 
        { 
            get 
            {
                return API.Utils.ConvertIPAddrI32ToString(_NetIPAddrI32);
            } 
        }
        public long ErrFlag {  get { return _ErrFlag;  } }
        public string ErrFlagString 
        { 
            get 
            {
                string str;
                str = string.Format($"0x{_ErrFlag:X16}");
                return str;
            } 
        }
    }
}
