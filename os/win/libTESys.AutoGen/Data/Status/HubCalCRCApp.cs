using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.Data.Status
{
    public class HubCalCRCApp
    {
#if false

            struct HubCalCRCApp {
                int AppStatus;
                int FtpStorageLatestCRC;        // 로칼에 있는 전체 파일 크기 
                long long FtpStorageTotalFileByteSize; // 현재 CRC 계산완료된 FileByte길이 
                long long FtpStorageCurCalculatedCRCByteSize;                // 최종 CRC값 
            };

#endif
        long _NotifyUtcTime = 0;

        private int _AppStatus;
        private int _FtpStorageLatestCRC;        // 로칼에 있는 전체 파일 크기 
        private long _FtpStorageTotalFileByteSize; // 현재 CRC 계산완료된 FileByte길이 
        private long _FtpStorageCurCalculatedCRCByteSize;                // 최종 CRC값 

        public HubCalCRCApp(long utcTime, IntPtr rawByteData, int dataOffset)
        {
            _NotifyUtcTime = utcTime;

            _AppStatus = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _FtpStorageLatestCRC = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _FtpStorageTotalFileByteSize = Marshal.ReadInt64(rawByteData, dataOffset); dataOffset += 8;
            _FtpStorageCurCalculatedCRCByteSize = Marshal.ReadInt64(rawByteData, dataOffset); dataOffset += 8;

        }

        public int CrcSum
        {
            get
            {
                return _FtpStorageLatestCRC;
            }
        }

        public string AppStatus
        {
            get
            {
#if true
                string strStatus;

                if (_NotifyUtcTime != 0) 
                { 

                    string strAppStatus = API.Property.GetString((int)API.Property.Hub.AppStatusString, _AppStatus);
                    long rate;

                    if (API.Property.GetInt((int)API.Property.Hub.IsThisAppStatus_CalCRC, _AppStatus) == 1)
                    {
                        //CalCRC
                        if (_FtpStorageTotalFileByteSize != 0) 
                        {
                            rate = (_FtpStorageCurCalculatedCRCByteSize * 100) / _FtpStorageTotalFileByteSize;
                        }
                        else
                        {
                            rate = 0;
                        }
                        
                    
                        strStatus = string.Format($"{strAppStatus}({rate}%)");
                    }
                    else
                    {
                        strStatus = strAppStatus;
                    }
                }
                else
                {
                    strStatus = "";
                }

                return strStatus;
#else
                return "???";
#endif
            }
        }
    }
}
