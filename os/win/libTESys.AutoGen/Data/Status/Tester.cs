using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.Data.Status
{
    public class Tester
    {
#if false
            //#define TESYS_DATA_STATUS_TESTER_KEY  0x98290100
            struct Tester {
                struct TesterHeader Header;
                struct Board Board;
                struct Aging Aging;
                struct FileSync FileSync;
            };
#endif

        private Data.Status.TesterHeader _TesterHeader;
        private Data.Status.Board _Board;
        private Data.Status.Aging _Aging;
        private Data.Status.FileSync _FileSync;

        public Tester(IntPtr rawByteData, int dataOffset)
        {
            int byteSize_Of_TESys_Data_Status_Struct_TesterHeader = API.Property.GetInt((int)API.Property.Data.ByteSize_Of_TESys_Data_Status_Struct_TesterHeader);
            int byteSize_Of_TESys_Data_Status_Struct_Board = API.Property.GetInt((int)API.Property.Data.ByteSize_Of_TESys_Data_Status_Struct_Board);
            int byteSize_Of_TESys_Data_Status_Struct_Aging = API.Property.GetInt((int)API.Property.Data.ByteSize_Of_TESys_Data_Status_Struct_Aging);
            int byteSize_Of_TESys_Data_Status_Struct_FileSync = API.Property.GetInt((int)API.Property.Data.ByteSize_Of_TESys_Data_Status_Struct_FileSync);


            _TesterHeader = new Data.Status.TesterHeader(rawByteData, dataOffset); dataOffset += byteSize_Of_TESys_Data_Status_Struct_TesterHeader;
            _Board = new Data.Status.Board(rawByteData, dataOffset); dataOffset += byteSize_Of_TESys_Data_Status_Struct_Board;
            _Aging = new Data.Status.Aging(rawByteData, dataOffset); dataOffset += byteSize_Of_TESys_Data_Status_Struct_Aging;
            _FileSync = new Data.Status.FileSync(rawByteData, dataOffset); dataOffset += byteSize_Of_TESys_Data_Status_Struct_FileSync;
        }

        public Data.Status.TesterHeader TesterHeader { get { return _TesterHeader; } }
        public Data.Status.Board Board { get { return _Board; } }
        public Data.Status.FileSync FileSync { get { return _FileSync; } }
        public Data.Status.Aging Aging { get { return _Aging; } }
    }
}
