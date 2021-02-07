using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.Data.Status
{
    public class Hub
    {
#if false
        struct Hub
        {
            time_t NotifyUtcTime;
            struct HubCalCRCApp CalCRCApp;
        };
#endif
        long _NotifyUtcTime = 0;
        HubCalCRCApp _CalCRCApp;

        public Hub(IntPtr rawByteData, int dataOffset=0)
        {
            _NotifyUtcTime = Marshal.ReadInt64(rawByteData, dataOffset); dataOffset += 8;
            _CalCRCApp = new HubCalCRCApp(_NotifyUtcTime, rawByteData, dataOffset);
        }

        public bool IsValid
        {
            get
            {
                bool bRet;
                if(_NotifyUtcTime==0)
                {
                    bRet = false;
                }
                else
                {
                    bRet = true;
                }

                return bRet;
            }
        }

        public HubCalCRCApp CalCRCApp
        {
            get
            {
                return _CalCRCApp;
            }
        }

    }
}
