using libTESys.AutoGen.Native;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.DLL
{
    static public class Utils
    {
        //TESYSMODULE_API int TESysUtilsGetDateTimeString(time_t utcTime, /*OUT*/char* szDateTime)
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public unsafe delegate int GetDateTimeStringDelegate(long utcTime, /*OUT*/ byte* @devName);
        public static unsafe GetDateTimeStringDelegate GetDateTimeString = (long utcTime, /*OUT*/ byte* @devName) =>
        {
            string funcName = "TESysUtilsGetDateTimeString";
            GetDateTimeString = FunctionLoader.GetFunctionDelegate<GetDateTimeStringDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (GetDateTimeString == null)
            {
                GetDateTimeString = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return GetDateTimeString(utcTime, @devName);
        };

        //TESYSMODULE_API bool TESysUtilsConvertIPAddrI32ToString(unsigned int ipAddrI32, /*OUT*/char* szIPAddr)
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public unsafe delegate int ConvertIPAddrI32ToStringDelegate(int ipAddrI32, /*OUT*/ byte* @devName);
        public static unsafe ConvertIPAddrI32ToStringDelegate ConvertIPAddrI32ToString = (int ipAddrI32, /*OUT*/ byte* @devName) =>
        {
            string funcName = "TESysUtilsConvertIPAddrI32ToString";
            ConvertIPAddrI32ToString = FunctionLoader.GetFunctionDelegate<ConvertIPAddrI32ToStringDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (ConvertIPAddrI32ToString == null)
            {
                ConvertIPAddrI32ToString = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return ConvertIPAddrI32ToString(ipAddrI32, @devName);
        };


    }
}
