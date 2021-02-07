using libTESys.AutoGen.Native;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.DLL
{
    static public class Property
    {
        //TESYSMODULE_API int TESysPropertyGetInt(int propId, int valueID);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int GetIntDelegate(int propId, int valueID);
        public static GetIntDelegate GetInt = (int propId, int valueID) =>
        {
            string funcName = "TESysPropertyGetInt";
            GetInt = FunctionLoader.GetFunctionDelegate<GetIntDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (GetInt == null)
            {
                GetInt = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return GetInt(propId, valueID);
        };

        //TESYSMODULE_API int TESysPropertyGetString(int propId, int valueID,/*OUT*/char * szProp);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public unsafe delegate bool GetStringDelegate(int propId, int valueID, /*OUT*/ byte* szProp);
        public static unsafe GetStringDelegate GetString = (int propId, int valueID, /*OUT*/ byte* szProp) =>
        {
            string funcName = "TESysPropertyGetString";
            GetString = FunctionLoader.GetFunctionDelegate<GetStringDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (GetString == null)
            {
                GetString = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return GetString(propId, valueID, szProp);
        };

    }
}
