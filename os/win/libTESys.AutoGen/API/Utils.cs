using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.API
{
    public static class Utils
    {
        
        public static unsafe string GetDateTimeString(long utcTime)
        {
            var respBytes = Marshal.AllocHGlobal(1024);
            string str;

            DLL.Utils.GetDateTimeString(utcTime, /*OUT*/(byte*)respBytes);
            str = Marshal.PtrToStringAnsi(respBytes);
            Marshal.FreeHGlobal(respBytes);

            return str;
        }

        public static unsafe string ConvertIPAddrI32ToString(int ipAddrI32)
        {
            var respBytes = Marshal.AllocHGlobal(1024);
            string str;

            DLL.Utils.ConvertIPAddrI32ToString(ipAddrI32, /*OUT*/(byte*)respBytes);
            str = Marshal.PtrToStringAnsi(respBytes);
            Marshal.FreeHGlobal(respBytes);

            return str;
        }
    }
}
