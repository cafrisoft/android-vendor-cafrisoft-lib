using libTESys.AutoGen.Native;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.DLL
{
    static public class Operator 
    {
#if false
        private const string ROOTPATH = @"."; // string.Empty;
        private static string DLLNAME = "AnapassTESysModule";

        private static IntPtr DLL.Base.LoadLibrary()
        {
            //var dependencies = LibraryDependenciesMap[libraryName];
            //dependencies.ForEach(x => GetOrLoadLibrary(x));
            var version = 1;// LibraryVersionMap[libraryName];
            var ptr = LibraryLoader.LoadNativeLibrary(Operator.ROOTPATH, Operator.DLLNAME, version);
            if (ptr == IntPtr.Zero)
            {
                throw new DllNotFoundException($"Unable to load DLL '{Operator.DLLNAME}.dll': The specified module could not be found."
                    + "\n " + StringLib.TESysModuelLoadFail
                    );
            }
            return ptr;
        }
#endif

        //TESYSMODULE_API void* TESysOperatorCreate();
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate IntPtr CreateDelegate();
        public static CreateDelegate Create = () =>
        {
            string funcName = "TESysOperatorCreate";
            Create = FunctionLoader.GetFunctionDelegate<CreateDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (Create == null)
            {
                Create = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return Create();
        };

        //TESYSMODULE_API int TESysOperatorDestroy(void* objHandle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate bool DestroyDelegate(IntPtr objectHandle);
        public static DestroyDelegate Destroy = (IntPtr objectHandle) =>
        {
            string funcName = "TESysOperatorDestroy";
            Destroy = FunctionLoader.GetFunctionDelegate<DestroyDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (Destroy == null)
            {
                Destroy = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return Destroy(objectHandle);
        };


        //TESYSMODULE_API int TESysOperatorConnect(void* objHandle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate bool ConnectDelegate(IntPtr objectHandle);
        public static ConnectDelegate Connect = (IntPtr objectHandle) =>
        {
            string funcName = "TESysOperatorConnect";
            Connect = FunctionLoader.GetFunctionDelegate<ConnectDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (Connect == null)
            {
                Connect = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return Connect(objectHandle);
        };


        //TESYSMODULE_API int TESysOperatorDisconnect(void* objHandle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate bool DisconnectDelegate(IntPtr objectHandle);
        public static DisconnectDelegate Disconnect = (IntPtr objectHandle) =>
        {
            string funcName = "TESysOperatorDisconnect";
            Disconnect = FunctionLoader.GetFunctionDelegate<DisconnectDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (Disconnect == null)
            {
                Disconnect = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return Disconnect(objectHandle);
        };

        //TESYSMODULE_API int TESysOperatorIsConnect(void* objHandle)
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate bool IsConnectDelegate(IntPtr objectHandle);
        public static IsConnectDelegate IsConnect = (IntPtr objectHandle) =>
        {
            string funcName = "TESysOperatorIsConnect";
            IsConnect = FunctionLoader.GetFunctionDelegate<IsConnectDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (IsConnect == null)
            {
                IsConnect = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return IsConnect(objectHandle);
        };


        //TESYSMODULE_API int TESysOperator_C_OH_RunHubCalCRC(void* objHandle);
        public delegate bool C_OH_RunHubCalCRCDelegate(IntPtr objectHandle);
        public static C_OH_RunHubCalCRCDelegate C_OH_RunHubCalCRC = (IntPtr objectHandle) =>
        {
            string funcName = "TESysOperator_C_OH_RunHubCalCRC";
            C_OH_RunHubCalCRC = FunctionLoader.GetFunctionDelegate<C_OH_RunHubCalCRCDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (C_OH_RunHubCalCRC == null)
            {
                C_OH_RunHubCalCRC = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return C_OH_RunHubCalCRC(objectHandle);
        };

        //TESYSMODULE_API int TESysOperator_C_OHT_RunFileSync(void* objHandle);
        public delegate bool C_OHT_RunFileSyncDelegate(IntPtr objectHandle);
        public static C_OHT_RunFileSyncDelegate C_OHT_RunFileSync = (IntPtr objectHandle) =>
        {
            string funcName = "TESysOperator_C_OHT_RunFileSync";
            C_OHT_RunFileSync = FunctionLoader.GetFunctionDelegate<C_OHT_RunFileSyncDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (C_OHT_RunFileSync == null)
            {
                C_OHT_RunFileSync = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return C_OHT_RunFileSync(objectHandle);
        };

        //TESYSMODULE_API int TESysOperator_C_OHT_RunPythonTC(void* objHandle, int tcNo);
        public delegate bool C_OHT_RunPythonTCDelegate(IntPtr objectHandle, int tcNo);
        public static C_OHT_RunPythonTCDelegate C_OHT_RunPythonTC = (IntPtr objectHandle, int tcNo) =>
        {
            string funcName = "TESysOperator_C_OHT_RunPythonTC";
            C_OHT_RunPythonTC = FunctionLoader.GetFunctionDelegate<C_OHT_RunPythonTCDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (C_OHT_RunPythonTC == null)
            {
                C_OHT_RunPythonTC = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return C_OHT_RunPythonTC(objectHandle, tcNo);
        };

        //TESYSMODULE_API int TESysOperator_C_OHT_RunPythonSC(void* objHandle, int scNo);
        public delegate bool C_OHT_RunPythonSCDelegate(IntPtr objectHandle, int scNo);
        public static C_OHT_RunPythonSCDelegate C_OHT_RunPythonSC = (IntPtr objectHandle, int scNo) =>
        {
            string funcName = "TESysOperator_C_OHT_RunPythonSC";
            C_OHT_RunPythonSC = FunctionLoader.GetFunctionDelegate<C_OHT_RunPythonSCDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (C_OHT_RunPythonSC == null)
            {
                C_OHT_RunPythonSC = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return C_OHT_RunPythonSC(objectHandle, scNo);
        };

        //TESYSMODULE_API int TESysOperator_C_OHT_RunPythonJOB(void* objHandle, int jobNo);
        public delegate bool C_OHT_RunPythonJOBDelegate(IntPtr objectHandle, int jobNo);
        public static C_OHT_RunPythonJOBDelegate C_OHT_RunPythonJOB = (IntPtr objectHandle, int jobNo) =>
        {
            string funcName = "TESysOperator_C_OHT_RunPythonJOB";
            C_OHT_RunPythonJOB = FunctionLoader.GetFunctionDelegate<C_OHT_RunPythonJOBDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (C_OHT_RunPythonJOB == null)
            {
                C_OHT_RunPythonJOB = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return C_OHT_RunPythonJOB(objectHandle, jobNo);
        };

        //TESYSMODULE_API int TESysOperator_C_OHT_RunFWUpgrade(void* objHandle);
        public delegate bool C_OHT_RunFWUpgradeDelegate(IntPtr objectHandle);
        public static C_OHT_RunFWUpgradeDelegate C_OHT_RunFWUpgrade = (IntPtr objectHandle) =>
        {
            string funcName = "TESysOperator_C_OHT_RunFWUpgrade";
            C_OHT_RunFWUpgrade = FunctionLoader.GetFunctionDelegate<C_OHT_RunFWUpgradeDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (C_OHT_RunFWUpgrade == null)
            {
                C_OHT_RunFWUpgrade = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return C_OHT_RunFWUpgrade(objectHandle);
        };



        //TESYSMODULE_API void* TESysOperatorDataConsumerTesterStatusCreate(void* objHandle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate IntPtr DataConsumerTesterStatusCreateDelegate(IntPtr objectHandle);
        public static DataConsumerTesterStatusCreateDelegate DataConsumerTesterStatusCreate = (IntPtr objectHandle) =>
        {
            string funcName = "TESysOperatorDataConsumerTesterStatusCreate";
            DataConsumerTesterStatusCreate = FunctionLoader.GetFunctionDelegate<DataConsumerTesterStatusCreateDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (DataConsumerTesterStatusCreate == null)
            {
                DataConsumerTesterStatusCreate = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return DataConsumerTesterStatusCreate(objectHandle);
        };

        //TESYSMODULE_API bool TESysOperatorDataConsumerTesterStatusDestroy(void* objHandle, void* dataComsumerHandle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate bool DataConsumerTesterStatusDestroyDelegate(IntPtr objectHandle, IntPtr dataComsumerHandle);
        public static DataConsumerTesterStatusDestroyDelegate DataConsumerTesterStatusDestroy = (IntPtr objectHandle, IntPtr dataComsumerHandle) =>
        {
            string funcName = "TESysOperatorDataConsumerTesterStatusDestroy";
            DataConsumerTesterStatusDestroy = FunctionLoader.GetFunctionDelegate<DataConsumerTesterStatusDestroyDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (DataConsumerTesterStatusDestroy == null)
            {
                DataConsumerTesterStatusDestroy = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return DataConsumerTesterStatusDestroy(objectHandle, dataComsumerHandle);
        };


        //TESYSMODULE_API bool TESysOperatorDataConsumerTesterStatusGetApiData(void* objHandle, void* dataComsumerHandle, /*OUT*/unsigned char* packetTesterStatusArray /*struct TESys::API::PacketTesterStatusArray* */ );
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public unsafe delegate bool DataConsumerTesterStatusGetApiDataDelegate(IntPtr objectHandle, IntPtr dataComsumerHandle, /*OUT*/byte* data);
        public static unsafe DataConsumerTesterStatusGetApiDataDelegate DataConsumerTesterStatusGetApiData = (IntPtr objectHandle, IntPtr dataComsumerHandle, /*OUT*/byte* data) =>
        {
            string funcName = "TESysOperatorDataConsumerTesterStatusGetApiData";
            DataConsumerTesterStatusGetApiData = FunctionLoader.GetFunctionDelegate<DataConsumerTesterStatusGetApiDataDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (DataConsumerTesterStatusGetApiData == null)
            {
                DataConsumerTesterStatusGetApiData = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return DataConsumerTesterStatusGetApiData(objectHandle, dataComsumerHandle, data);
        };


        //TESYSMODULE_API void* TESysOperatorDataConsumerHubStatusCreate(void* objHandle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate IntPtr DataConsumerHubStatusCreateDelegate(IntPtr objectHandle);
        public static DataConsumerHubStatusCreateDelegate DataConsumerHubStatusCreate = (IntPtr objectHandle) =>
        {
            string funcName = "TESysOperatorDataConsumerHubStatusCreate";
            DataConsumerHubStatusCreate = FunctionLoader.GetFunctionDelegate<DataConsumerHubStatusCreateDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (DataConsumerHubStatusCreate == null)
            {
                DataConsumerHubStatusCreate = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return DataConsumerHubStatusCreate(objectHandle);
        };


        //TESYSMODULE_API bool TESysOperatorDataConsumerHubStatusDestroy(void* objHandle, void* dataComsumerHandle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate bool DataConsumerHubStatusDestroyDelegate(IntPtr objectHandle, IntPtr dataComsumerHandle);
        public static DataConsumerHubStatusDestroyDelegate DataConsumerHubStatusDestroy = (IntPtr objectHandle, IntPtr dataComsumerHandle) =>
        {
            string funcName = "TESysOperatorDataConsumerHubStatusDestroy";
            DataConsumerHubStatusDestroy = FunctionLoader.GetFunctionDelegate<DataConsumerHubStatusDestroyDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (DataConsumerHubStatusDestroy == null)
            {
                DataConsumerHubStatusDestroy = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return DataConsumerHubStatusDestroy(objectHandle, dataComsumerHandle);
        };


        //TESYSMODULE_API bool TESysOperatorDataConsumerHubStatusGetApiData(void* objHandle, void* dataComsumerHandle, /*OUT*/unsigned char* pHubStatus /*struct TESys::Data::Status::Hub* pHubStatus */);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public unsafe delegate bool DataConsumerHubStatusGetApiDataDelegate(IntPtr objectHandle, IntPtr dataComsumerHandle, /*OUT*/byte* data);
        public static unsafe DataConsumerHubStatusGetApiDataDelegate DataConsumerHubStatusGetApiData = (IntPtr objectHandle, IntPtr dataComsumerHandle, /*OUT*/byte* data) =>
        {
            string funcName = "TESysOperatorDataConsumerHubStatusGetApiData";
            DataConsumerHubStatusGetApiData = FunctionLoader.GetFunctionDelegate<DataConsumerHubStatusGetApiDataDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (DataConsumerHubStatusGetApiData == null)
            {
                DataConsumerHubStatusGetApiData = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return DataConsumerHubStatusGetApiData(objectHandle, dataComsumerHandle, data);
        };

        //TESYSMODULE_API bool TESysOperatorFileSyncRun(void* objHandle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate bool FileSyncRunDelegate(IntPtr objectHandle);
        public static FileSyncRunDelegate FileSyncRun = (IntPtr objectHandle) =>
        {
            string funcName = "TESysOperatorFileSyncRun";
            FileSyncRun = FunctionLoader.GetFunctionDelegate<FileSyncRunDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (FileSyncRun == null)
            {
                FileSyncRun = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return FileSyncRun(objectHandle);
        };

        //TESYSMODULE_API bool TESysOperatorFileSyncIsDone(void* objHandle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate bool FileSyncIsDoneDelegate(IntPtr objectHandle);
        public static FileSyncIsDoneDelegate FileSyncIsDone = (IntPtr objectHandle) =>
        {
            string funcName = "TESysOperatorFileSyncIsDone";
            FileSyncIsDone = FunctionLoader.GetFunctionDelegate<FileSyncIsDoneDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (FileSyncIsDone == null)
            {
                FileSyncIsDone = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return FileSyncIsDone(objectHandle);
        };

        //TESYSMODULE_API int TESysOperatorFileSyncGetJobID(void* objHandle, int idx);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int FileSyncGetJobIDDelegate(IntPtr objectHandle, int idx);
        public static FileSyncGetJobIDDelegate FileSyncGetJobID = (IntPtr objectHandle, int idx) =>
        {
            string funcName = "TESysOperatorFileSyncGetJobID";
            FileSyncGetJobID = FunctionLoader.GetFunctionDelegate<FileSyncGetJobIDDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (FileSyncGetJobID == null)
            {
                FileSyncGetJobID = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return FileSyncGetJobID(objectHandle, idx);
        };


        //TESYSMODULE_API int TESysOperatorFileSyncGetJobCount(void* objHandle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int FileSyncGetJobCountDelegate(IntPtr objectHandle);
        public static FileSyncGetJobCountDelegate FileSyncGetJobCount = (IntPtr objectHandle) =>
        {
            string funcName = "TESysOperatorFileSyncGetJobCount";
            FileSyncGetJobCount = FunctionLoader.GetFunctionDelegate<FileSyncGetJobCountDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (FileSyncGetJobCount == null)
            {
                FileSyncGetJobCount = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return FileSyncGetJobCount(objectHandle);
        };

        //TESYSMODULE_API int TESysOperatorFileSyncGetScID(void* objHandle, int idx);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int FileSyncGetScIDDelegate(IntPtr objectHandle, int idx);
        public static FileSyncGetScIDDelegate FileSyncGetScID = (IntPtr objectHandle, int idx) =>
        {
            string funcName = "TESysOperatorFileSyncGetScID";
            FileSyncGetScID = FunctionLoader.GetFunctionDelegate<FileSyncGetScIDDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (FileSyncGetScID == null)
            {
                FileSyncGetScID = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return FileSyncGetScID(objectHandle, idx);
        };

        //TESYSMODULE_API int TESysOperatorFileSyncGetScCount(void* objHandle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int FileSyncGetScCountDelegate(IntPtr objectHandle);
        public static FileSyncGetScCountDelegate FileSyncGetScCount = (IntPtr objectHandle) =>
        {
            string funcName = "TESysOperatorFileSyncGetScCount";
            FileSyncGetScCount = FunctionLoader.GetFunctionDelegate<FileSyncGetScCountDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (FileSyncGetScCount == null)
            {
                FileSyncGetScCount = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return FileSyncGetScCount(objectHandle);
        };

        //TESYSMODULE_API int TESysOperatorFileSyncGetTcID(void* objHandle, int idx);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int FileSyncGetTcIDDelegate(IntPtr objectHandle, int idx);
        public static FileSyncGetTcIDDelegate FileSyncGetTcID = (IntPtr objectHandle, int idx) =>
        {
            string funcName = "TESysOperatorFileSyncGetTcID";
            FileSyncGetTcID = FunctionLoader.GetFunctionDelegate<FileSyncGetTcIDDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (FileSyncGetTcID == null)
            {
                FileSyncGetTcID = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return FileSyncGetTcID(objectHandle, idx);
        };

        //TESYSMODULE_API int TESysOperatorFileSyncGetTcCount(void* objHandle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int FileSyncGetTcCountDelegate(IntPtr objectHandle);
        public static FileSyncGetTcCountDelegate FileSyncGetTcCount = (IntPtr objectHandle) =>
        {
            string funcName = "TESysOperatorFileSyncGetTcCount";
            FileSyncGetTcCount = FunctionLoader.GetFunctionDelegate<FileSyncGetTcCountDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (FileSyncGetTcCount == null)
            {
                FileSyncGetTcCount = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return FileSyncGetTcCount(objectHandle);
        };

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetJobID(void* objHandle, int boardID, int dutIdx);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int AgingMonitorGetJobIDDelegate(IntPtr objectHandle, int boardID, int dutIdx);
        public static AgingMonitorGetJobIDDelegate AgingMonitorGetJobID = (IntPtr objectHandle, int boardID, int dutIdx) =>
        {
            string funcName = "TESysOperatorAgingMonitorGetJobID";
            AgingMonitorGetJobID = FunctionLoader.GetFunctionDelegate<AgingMonitorGetJobIDDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (AgingMonitorGetJobID == null)
            {
                AgingMonitorGetJobID = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return AgingMonitorGetJobID(objectHandle, boardID, dutIdx);
        };

        //TESYSMODULE_API bool TESysOperatorAgingMonitorGetJobStatusString(void* objHandle, int boardID, int dutIdx, /*OUT*/char* statusString);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public unsafe delegate bool AgingMonitorGetJobStatusStringDelegate(IntPtr objectHandle, int boardID, int dutIdx, /*OUT*/ byte* strStatus);
        public static unsafe AgingMonitorGetJobStatusStringDelegate AgingMonitorGetJobStatusString = (IntPtr objectHandle, int boardID, int dutIdx, /*OUT*/ byte* strStatus) =>
        {
            string funcName = "TESysOperatorAgingMonitorGetJobStatusString";
            AgingMonitorGetJobStatusString = FunctionLoader.GetFunctionDelegate<AgingMonitorGetJobStatusStringDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (AgingMonitorGetJobStatusString == null)
            {
                AgingMonitorGetJobStatusString = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return AgingMonitorGetJobStatusString(objectHandle, boardID, dutIdx, /*OUT*/strStatus);
        };

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetScID(void* objHandle, int boardID, int dutIdx);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int AgingMonitorGetScIDDelegate(IntPtr objectHandle, int boardID, int dutIdx);
        public static AgingMonitorGetScIDDelegate AgingMonitorGetScID = (IntPtr objectHandle, int boardID, int dutIdx) =>
        {
            string funcName = "TESysOperatorAgingMonitorGetScID";
            AgingMonitorGetScID = FunctionLoader.GetFunctionDelegate<AgingMonitorGetScIDDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (AgingMonitorGetScID == null)
            {
                AgingMonitorGetScID = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return AgingMonitorGetScID(objectHandle, boardID, dutIdx);
        };

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetScIndex(void* objHandle, int boardID, int dutIdx);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int AgingMonitorGetScIndexDelegate(IntPtr objectHandle, int boardID, int dutIdx);
        public static AgingMonitorGetScIndexDelegate AgingMonitorGetScIndex = (IntPtr objectHandle, int boardID, int dutIdx) =>
        {
            string funcName = "TESysOperatorAgingMonitorGetScIndex";
            AgingMonitorGetScIndex = FunctionLoader.GetFunctionDelegate<AgingMonitorGetScIndexDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (AgingMonitorGetScIndex == null)
            {
                AgingMonitorGetScIndex = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return AgingMonitorGetScIndex(objectHandle, boardID, dutIdx);
        };

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetScCount(void* objHandle, int boardID, int dutIdx);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int AgingMonitorGetScCountDelegate(IntPtr objectHandle, int boardID, int dutIdx);
        public static AgingMonitorGetScCountDelegate AgingMonitorGetScCount = (IntPtr objectHandle, int boardID, int dutIdx) =>
        {
            string funcName = "TESysOperatorAgingMonitorGetScCount";
            AgingMonitorGetScCount = FunctionLoader.GetFunctionDelegate<AgingMonitorGetScCountDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (AgingMonitorGetScCount == null)
            {
                AgingMonitorGetScCount = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return AgingMonitorGetScCount(objectHandle, boardID, dutIdx);
        };

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetTcID(void* objHandle, int boardID, int dutIdx);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int AgingMonitorGetTcIDDelegate(IntPtr objectHandle, int boardID, int dutIdx);
        public static AgingMonitorGetTcIDDelegate AgingMonitorGetTcID = (IntPtr objectHandle, int boardID, int dutIdx) =>
        {
            string funcName = "TESysOperatorAgingMonitorGetTcID";
            AgingMonitorGetTcID = FunctionLoader.GetFunctionDelegate<AgingMonitorGetTcIDDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (AgingMonitorGetTcID == null)
            {
                AgingMonitorGetTcID = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return AgingMonitorGetTcID(objectHandle, boardID, dutIdx);
        };

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetTcIndex(void* objHandle, int boardID, int dutIdx);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int AgingMonitorGetTcIndexDelegate(IntPtr objectHandle, int boardID, int dutIdx);
        public static AgingMonitorGetTcIndexDelegate AgingMonitorGetTcIndex = (IntPtr objectHandle, int boardID, int dutIdx) =>
        {
            string funcName = "TESysOperatorAgingMonitorGetTcIndex";
            AgingMonitorGetTcIndex = FunctionLoader.GetFunctionDelegate<AgingMonitorGetTcIndexDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (AgingMonitorGetTcIndex == null)
            {
                AgingMonitorGetTcIndex = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return AgingMonitorGetTcIndex(objectHandle, boardID, dutIdx);
        };


        //TESYSMODULE_API int TESysOperatorAgingMonitorGetTcCount(void* objHandle, int boardID, int dutIdx);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int AgingMonitorGetTcCountDelegate(IntPtr objectHandle, int boardID, int dutIdx);
        public static AgingMonitorGetTcCountDelegate AgingMonitorGetTcCount = (IntPtr objectHandle, int boardID, int dutIdx) =>
        {
            string funcName = "TESysOperatorAgingMonitorGetTcCount";
            AgingMonitorGetTcCount = FunctionLoader.GetFunctionDelegate<AgingMonitorGetTcCountDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (AgingMonitorGetTcCount == null)
            {
                AgingMonitorGetTcCount = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return AgingMonitorGetTcCount(objectHandle, boardID, dutIdx);
        };

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetTcStepID(void* objHandle, int boardID, int dutIdx);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int AgingMonitorGetTcStepIDDelegate(IntPtr objectHandle, int boardID, int dutIdx);
        public static AgingMonitorGetTcStepIDDelegate AgingMonitorGetTcStepID = (IntPtr objectHandle, int boardID, int dutIdx) =>
        {
            string funcName = "TESysOperatorAgingMonitorGetTcStepID";
            AgingMonitorGetTcStepID = FunctionLoader.GetFunctionDelegate<AgingMonitorGetTcStepIDDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (AgingMonitorGetTcStepID == null)
            {
                AgingMonitorGetTcStepID = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return AgingMonitorGetTcStepID(objectHandle, boardID, dutIdx);
        };

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetTcStepIndex(void* objHandle, int boardID, int dutIdx);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int AgingMonitorGetTcStepIndexDelegate(IntPtr objectHandle, int boardID, int dutIdx);
        public static AgingMonitorGetTcStepIndexDelegate AgingMonitorGetTcStepIndex = (IntPtr objectHandle, int boardID, int dutIdx) =>
        {
            string funcName = "TESysOperatorAgingMonitorGetTcStepIndex";
            AgingMonitorGetTcStepIndex = FunctionLoader.GetFunctionDelegate<AgingMonitorGetTcStepIndexDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (AgingMonitorGetTcStepIndex == null)
            {
                AgingMonitorGetTcStepIndex = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return AgingMonitorGetTcStepIndex(objectHandle, boardID, dutIdx);
        };


        //TESYSMODULE_API int TESysOperatorAgingMonitorGetTcStepCount(void* objHandle, int boardID, int dutIdx);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int AgingMonitorGetTcStepCountDelegate(IntPtr objectHandle, int boardID, int dutIdx);
        public static AgingMonitorGetTcStepCountDelegate AgingMonitorGetTcStepCount = (IntPtr objectHandle, int boardID, int dutIdx) =>
        {
            string funcName = "TESysOperatorAgingMonitorGetTcStepCount";
            AgingMonitorGetTcStepCount = FunctionLoader.GetFunctionDelegate<AgingMonitorGetTcStepCountDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (AgingMonitorGetTcStepCount == null)
            {
                AgingMonitorGetTcStepCount = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return AgingMonitorGetTcStepCount(objectHandle, boardID, dutIdx);
        };


        //TESYSMODULE_API bool TESysOperatorAgingMonitorIsRunPython(void* objHandle, int boardID, int dutIdx);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate bool AgingMonitorIsRunPythonDelegate(IntPtr objectHandle, int boardID, int dutIdx);
        public static AgingMonitorIsRunPythonDelegate AgingMonitorIsRunPython = (IntPtr objectHandle, int boardID, int dutIdx) =>
        {
            string funcName = "TESysOperatorAgingMonitorIsRunPython";
            AgingMonitorIsRunPython = FunctionLoader.GetFunctionDelegate<AgingMonitorIsRunPythonDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (AgingMonitorIsRunPython == null)
            {
                AgingMonitorIsRunPython = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return AgingMonitorIsRunPython(objectHandle, boardID, dutIdx);
        };

        //TESYSMODULE_API bool TESysOperatorAgingMonitorIsLastActionError(void* objHandle, int boardID, int dutIdx);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate bool AgingMonitorIsLastActionErrorDelegate(IntPtr objectHandle, int boardID, int dutIdx);
        public static AgingMonitorIsLastActionErrorDelegate AgingMonitorIsLastActionError = (IntPtr objectHandle, int boardID, int dutIdx) =>
        {
            string funcName = "TESysOperatorAgingMonitorIsLastActionError";
            AgingMonitorIsLastActionError = FunctionLoader.GetFunctionDelegate<AgingMonitorIsLastActionErrorDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (AgingMonitorIsLastActionError == null)
            {
                AgingMonitorIsLastActionError = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return AgingMonitorIsLastActionError(objectHandle, boardID, dutIdx);
        };


        //TESYSMODULE_API int TESysOperatorTesterMonitorGetLastNotifyTickDiff(void* objHandle, int boardID);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public delegate int TesterMonitorGetLastNotifyTickDiffDelegate(IntPtr objectHandle, int boardID);
        public static TesterMonitorGetLastNotifyTickDiffDelegate TesterMonitorGetLastNotifyTickDiff = (IntPtr objectHandle, int boardID) =>
        {
            string funcName = "TESysOperatorTesterMonitorGetLastNotifyTickDiff";
            TesterMonitorGetLastNotifyTickDiff = FunctionLoader.GetFunctionDelegate<TesterMonitorGetLastNotifyTickDiffDelegate>(DLL.Base.LoadLibrary(), funcName);
            if (TesterMonitorGetLastNotifyTickDiff == null)
            {
                TesterMonitorGetLastNotifyTickDiff = delegate
                {
                    throw new PlatformNotSupportedException($"FAIL to Loading DLL:  {DLL.Base.DLLNAME}.{funcName} ");
                };
            }
            return TesterMonitorGetLastNotifyTickDiff(objectHandle, boardID);
        };
    }
}
