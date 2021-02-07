using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.Data.Status
{
    public class FileSync
    {
#if false
            //#define TESYS_DATA_STATUS_FILESYNC_FtpDnCurFileName_ByteSize 128
            struct FileSync {
                
                //FileSync 명령이 시작되고 종료된 시간이다. 
                time_t AppStartUtcTime;
                time_t AppStopUtcTime;

                int AppStatus;
                int LocalLatestCRC;
                long long FtpDnTotalByteSize;
                long long FtpDnCurDownloadingByteSize;
                char FtpDnCurFileName[TESYS_DATA_STATUS_FILESYNC_FtpDnCurFileName_ByteSize];
                long long FtpDnCurFileByteSize;
                long long FtpDnCurFileDownloadingByteSize;
                long long LocalTotalFileByteSize;
                long long LocalCurCalculatedCRCByteSize;
                /*
                   주의) 하위버젼 호환을 위해 Param추가시  구조체 맨아래에 추가해야 한다. 8byte Align 유의
                */
            };
#endif

        private long _AppStartUtcTime;
        private long _AppStopUtcTime;

        private int _AppStatus;
        private int _LocalLatestCRC;
        private long _FtpDnTotalByteSize;
        private long _FtpDnCurDownloadingByteSize;
        private string _FtpDnCurFileName;
        private long _FtpDnCurFileByteSize;
        private long _FtpDnCurFileDownloadingByteSize;

        private long _LocalTotalFileByteSize;
        private long _LocalCurCalculatedCRCByteSize;

        public FileSync(IntPtr rawByteData, int dataOffset)
        {
            int byteSize_Of_TESys_Data_Status_Struct_FileSYnc_FtpDnCurFileName = API.Property.GetInt((int)API.Property.Data.ByteSize_Of_TESys_Data_Status_Struct_FileSYnc_FtpDnCurFileName);

            _AppStartUtcTime = Marshal.ReadInt64(rawByteData, dataOffset); dataOffset += 8;
            _AppStopUtcTime = Marshal.ReadInt64(rawByteData, dataOffset); dataOffset += 8;
            _AppStatus = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _LocalLatestCRC = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _FtpDnTotalByteSize = Marshal.ReadInt64(rawByteData, dataOffset); dataOffset += 8;
            _FtpDnCurDownloadingByteSize = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 8;
            _FtpDnCurFileName = Marshal.PtrToStringAnsi(Marshal.ReadIntPtr(rawByteData, dataOffset)); dataOffset += byteSize_Of_TESys_Data_Status_Struct_FileSYnc_FtpDnCurFileName;
            _FtpDnCurFileByteSize = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 8;
            _FtpDnCurFileDownloadingByteSize = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 8;
            _LocalTotalFileByteSize = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 8;
            _LocalCurCalculatedCRCByteSize = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 8;
        }

        public string AppStatus
        {
            get
            {
                string strStatus="";
                string strAppStatus = API.Property.GetString((int)API.Property.FileSync.AppStatusString, _AppStatus);
                long rate = 0;

                //strStatus = string.Format($"{API.Utils.GetDateTimeString(_AppStartUtcTime)}~{API.Utils.GetDateTimeString(_AppStopUtcTime)} " );  

                if (API.Property.GetInt((int)API.Property.FileSync.IsThisAppStatus_Downloading, _AppStatus) == 1)
                {
                    //Downloading
                    if(_FtpDnTotalByteSize != 0)
                    {
                        rate = (_FtpDnCurDownloadingByteSize * 100) / _FtpDnTotalByteSize;
                    }

                    strStatus += string.Format($"{strAppStatus}({rate}%)");
                }
                else if (API.Property.GetInt((int)API.Property.FileSync.IsThisAppStatus_CalCRC, _AppStatus) == 1)
                {
                    //CalCRC
                    if(_LocalTotalFileByteSize!=0)
                    {
                        rate = (_LocalCurCalculatedCRCByteSize * 100) / _LocalTotalFileByteSize;
                    }
                    strStatus += string.Format($"{strAppStatus}({rate}%)");
                }
                else
                {
                    strStatus += strAppStatus;
                }

                return strStatus;
            }
        }

        public int CrcSum
        {
            get
            {
                return _LocalLatestCRC;
            }
        }
    }
}
