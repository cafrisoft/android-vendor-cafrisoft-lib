using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.API
{
    public static class Property
    {
        private enum Group
        {
            ApiPacket = 0x1000,
            Data = 0x2000,
            Tester = 0x3000,
            FileSync = 0x4000,
            Hub = 0x5000,
        };

        public enum ApiPacket
        {
            Base = (int)Group.ApiPacket,

            Size_Of_TESys_API_PacketTesterStatusArray,
        };

        public enum Data
        {
            Base = (int)Group.Data,

            //struct Aging
            ByteSize_Of_TESys_Data_Status_Struct_Aging,

            //struct FileSync
            ByteSize_Of_TESys_Data_Status_Struct_FileSync,
            ByteSize_Of_TESys_Data_Status_Struct_FileSYnc_FtpDnCurFileName,

            //struct Board
            ByteSize_Of_TESys_Data_Status_Struct_Board,
            ByteSize_Of_TESys_Data_Status_Struct_Board_FWVer,

            //struct TesterHeader
            ByteSize_Of_TESys_Data_Status_Struct_TesterHeader,

            //struct Tester
            ByteSize_Of_TESys_Data_Status_Struct_Tester,
        };

        public enum Tester
        {
            Base = (int)Group.Tester,

            AvailableTEDBoardMaxCount,
            AvailableBoardMaxCount,
        };

        public enum FileSync
        {
            Base = (int)Group.FileSync,

            AppStatusString,
            IsThisAppStatus_Downloading,
            IsThisAppStatus_CalCRC,
        };

        public enum Hub
        {
            Base = (int)Group.Hub,

            AppStatusString,
            IsThisAppStatus_CalCRC,
        };


        public static int GetInt(int propId, int valueID=-1)
        {
            return DLL.Property.GetInt(propId, valueID);
        }

        
        public static unsafe string GetString(int propId, int valueID = -1)
        {
            var respBytes = Marshal.AllocHGlobal(1024);
            string strValue;
            bool bRet;


            bRet = DLL.Property.GetString(propId, valueID, (byte*)respBytes);
            if (bRet)
            {
                strValue = Marshal.PtrToStringAnsi(respBytes);
            }
            else
            {
                strValue = "???";
            }
            Marshal.FreeHGlobal(respBytes);

            return strValue;
        }
    }
}
