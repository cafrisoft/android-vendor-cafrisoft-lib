using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.Control
{
    public class Operator : IDisposable
    {
        private IntPtr _OperatorHandle = IntPtr.Zero;

        public Operator()
        {
            _OperatorHandle = DLL.Operator.Create();
            if (_OperatorHandle.Equals(IntPtr.Zero))
            {
                //int lastErr = TSC.Property.Debug.LastError;
                throw new FileNotFoundException($"FAIL to create TESysControlOperator");
            }
        }

        ~Operator()
        {
            Dispose();
        }

        public void Dispose()
        {
            if (!_OperatorHandle.Equals(IntPtr.Zero))
            {
                DLL.Operator.Destroy(_OperatorHandle);
                _OperatorHandle = IntPtr.Zero;
            }
        }

        public bool Connect()
        {
            return DLL.Operator.Connect(_OperatorHandle);
        }

        public bool Disconnect()
        {
            return DLL.Operator.Disconnect(_OperatorHandle);
        }

        public bool IsConnect()
        {
            return DLL.Operator.IsConnect(_OperatorHandle);
        }

        //TESYSMODULE_API int TESysOperator_C_OH_RunHubCalCRC(void* objHandle);
        public bool C_OH_RunHubCalCRC()
        {
            return DLL.Operator.C_OH_RunHubCalCRC(_OperatorHandle);
        }

        //TESYSMODULE_API int TESysOperator_C_OHT_RunFileSync(void* objHandle);
        public bool C_OHT_RunFileSync()
        {
            return DLL.Operator.C_OHT_RunFileSync(_OperatorHandle);
        }

        //TESYSMODULE_API int TESysOperator_C_OHT_RunPythonTC(void* objHandle, int tcNo);
        public bool C_OHT_RunPythonTC(int tcNo)
        {
            return DLL.Operator.C_OHT_RunPythonTC(_OperatorHandle, tcNo);
        }

        //TESYSMODULE_API int TESysOperator_C_OHT_RunPythonSC(void* objHandle, int scNo);
        public bool C_OHT_RunPythonSC(int scNo)
        {
            return DLL.Operator.C_OHT_RunPythonSC(_OperatorHandle, scNo);
        }

        //TESYSMODULE_API int TESysOperator_C_OHT_RunPythonJOB(void* objHandle, int jobNo);
        public bool C_OHT_RunPythonJOB(int jobNo)
        {
            return DLL.Operator.C_OHT_RunPythonJOB(_OperatorHandle, jobNo);
        }

        //TESYSMODULE_API int TESysOperator_C_OHT_RunFWUpgrade(void* objHandle);
        public bool C_OHT_RunFWUpgrade()
        {
            return DLL.Operator.C_OHT_RunFWUpgrade(_OperatorHandle);
        }

        public IntPtr DataConsumerTesterStatusCreate()
        {
            return DLL.Operator.DataConsumerTesterStatusCreate(_OperatorHandle);
        }
        public bool DataConsumerTesterStatusDestroy(IntPtr dataConsumerHandle)
        {
            return DLL.Operator.DataConsumerTesterStatusDestroy(_OperatorHandle, dataConsumerHandle);
        }

        unsafe public API.PacketTesterStatusArray DataConsumerTesterStatusGetApiData(IntPtr dataConsumerHandle)
        {
            //버퍼 할당
            int rawByteDataSize = API.Property.GetInt((int)API.Property.ApiPacket.Size_Of_TESys_API_PacketTesterStatusArray);
            IntPtr rawByteData = Marshal.AllocHGlobal(rawByteDataSize);

            //버퍼에 정보 받아오기 
            DLL.Operator.DataConsumerTesterStatusGetApiData(_OperatorHandle, dataConsumerHandle, (byte*)rawByteData);

            //버퍼 데이타 파싱
            API.PacketTesterStatusArray packetTesterStatusArray = new API.PacketTesterStatusArray(rawByteData);

            //버퍼해제 
            Marshal.FreeHGlobal(rawByteData);

            //결과 리턴 
            return packetTesterStatusArray;
        }


        public IntPtr DataConsumerHubStatusCreate()
        {
            return DLL.Operator.DataConsumerHubStatusCreate(_OperatorHandle);
        }
        public bool DataConsumerHubStatusDestroy(IntPtr dataConsumerHandle)
        {
            return DLL.Operator.DataConsumerHubStatusDestroy(_OperatorHandle, dataConsumerHandle);
        }

        unsafe public Data.Status.Hub DataConsumerHubStatusGetApiData(IntPtr dataConsumerHandle)
        {
            //버퍼 할당
            int rawByteDataSize = 4096;// API.Property.GetInt((int)API.Property.ApiPacket.Size_Of_TESys_API_PacketTesterStatusArray);
            IntPtr rawByteData = Marshal.AllocHGlobal(rawByteDataSize);

            //버퍼에 정보 받아오기 
            DLL.Operator.DataConsumerHubStatusGetApiData(_OperatorHandle, dataConsumerHandle, (byte*)rawByteData);

            //버퍼 데이타 파싱
            Data.Status.Hub hubStatus = new Data.Status.Hub(rawByteData);

            //버퍼해제 
            Marshal.FreeHGlobal(rawByteData);

            //결과 리턴 
            return hubStatus;
        }

        //TESYSMODULE_API bool TESysOperatorFileSyncRun(void* objHandle);
        public bool FileSyncRun()
        {
            return DLL.Operator.FileSyncRun(_OperatorHandle);
        }

        //TESYSMODULE_API bool TESysOperatorFileSyncIsDone(void* objHandle);
        public bool FileSyncIsDone
        {
            get {
                return DLL.Operator.FileSyncIsDone(_OperatorHandle);
            }
            
        }

        //TESYSMODULE_API int TESysOperatorFileSyncGetJobID(void* objHandle, int idx);
        public int FileSyncGetJobID(int idx)
        {
            return DLL.Operator.FileSyncGetJobID(_OperatorHandle, idx);
        }

        //TESYSMODULE_API int TESysOperatorFileSyncGetJobCount(void* objHandle);
        public int FileSyncJobCount
        {
            get
            {
                return DLL.Operator.FileSyncGetJobCount(_OperatorHandle);
            }
            
        }

        //TESYSMODULE_API int TESysOperatorFileSyncGetScID(void* objHandle, int idx);
        public int FileSyncGetScID(int idx)
        {
            return DLL.Operator.FileSyncGetScID(_OperatorHandle, idx);
        }

        //TESYSMODULE_API int TESysOperatorFileSyncGetScCount(void* objHandle);
        public int FileSyncScCount
        {
            get
            {
                return DLL.Operator.FileSyncGetScCount(_OperatorHandle);
            }
            
        }

        //TESYSMODULE_API int TESysOperatorFileSyncGetTcID(void* objHandle, int idx);
        public int FileSyncGetTcID(int idx)
        {
            return DLL.Operator.FileSyncGetTcID(_OperatorHandle, idx);
        }

        //TESYSMODULE_API int TESysOperatorFileSyncGetTcCount(void* objHandle);
        public int FileSyncTcCount
        {
            get
            {
                return DLL.Operator.FileSyncGetTcCount(_OperatorHandle);
            }
            
        }

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetJobID(void* objHandle, int boardID, int dutIdx);
        public int AgingMonitorGetJobID(int boardID, int dutIdx)
        {
            return DLL.Operator.AgingMonitorGetJobID(_OperatorHandle, boardID, dutIdx);
        }

        //TESYSMODULE_API bool TESysOperatorAgingMonitorGetJobStatusString(void* objHandle, int boardID, int dutIdx, /*OUT*/char* statusString);
        public unsafe string AgingMonitorGetJobStatusString(int boardID, int dutIdx)
        {
            var respBytes = Marshal.AllocHGlobal(1024);
            string strValue;
            bool bRet;

            bRet = DLL.Operator.AgingMonitorGetJobStatusString(_OperatorHandle, boardID, dutIdx, (byte*)respBytes);
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

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetScID(void* objHandle, int boardID, int dutIdx);
        public int AgingMonitorGetScID(int boardID, int dutIdx)
        {
            return DLL.Operator.AgingMonitorGetScID(_OperatorHandle, boardID, dutIdx);
        }

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetScIndex(void* objHandle, int boardID, int dutIdx);
        public int AgingMonitorGetScIndex(int boardID, int dutIdx)
        {
            return DLL.Operator.AgingMonitorGetScIndex(_OperatorHandle, boardID, dutIdx);
        }

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetScCount(void* objHandle, int boardID, int dutIdx);
        public int AgingMonitorGetScCount(int boardID, int dutIdx)
        {
            return DLL.Operator.AgingMonitorGetScCount(_OperatorHandle, boardID, dutIdx);
        }

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetTcID(void* objHandle, int boardID, int dutIdx);
        public int AgingMonitorGetTcID(int boardID, int dutIdx)
        {
            return DLL.Operator.AgingMonitorGetTcID(_OperatorHandle, boardID, dutIdx);
        }

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetTcIndex(void* objHandle, int boardID, int dutIdx);
        public int AgingMonitorGetTcIndex(int boardID, int dutIdx)
        {
            return DLL.Operator.AgingMonitorGetTcIndex(_OperatorHandle, boardID, dutIdx);
        }


        //TESYSMODULE_API int TESysOperatorAgingMonitorGetTcCount(void* objHandle, int boardID, int dutIdx);
        public int AgingMonitorGetTcCount(int boardID, int dutIdx)
        {
            return DLL.Operator.AgingMonitorGetTcCount(_OperatorHandle, boardID, dutIdx);
        }

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetTcStepID(void* objHandle, int boardID, int dutIdx);
        public int AgingMonitorGetTcStepID(int boardID, int dutIdx)
        {
            return DLL.Operator.AgingMonitorGetTcStepID(_OperatorHandle, boardID, dutIdx);
        }

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetTcStepIndex(void* objHandle, int boardID, int dutIdx);
        public int AgingMonitorGetTcStepIndex(int boardID, int dutIdx)
        {
            return DLL.Operator.AgingMonitorGetTcStepIndex(_OperatorHandle, boardID, dutIdx);
        }

        //TESYSMODULE_API int TESysOperatorAgingMonitorGetTcStepCount(void* objHandle, int boardID, int dutIdx);
        public int AgingMonitorGetTcStepCount(int boardID, int dutIdx)
        {
            return DLL.Operator.AgingMonitorGetTcStepCount(_OperatorHandle, boardID, dutIdx);
        }

        //TESYSMODULE_API bool TESysOperatorAgingMonitorIsRunPython(void* objHandle, int boardID, int dutIdx);
        public bool AgingMonitorIsRunPython(int boardID, int dutIdx)
        {
            return DLL.Operator.AgingMonitorIsRunPython(_OperatorHandle, boardID, dutIdx);
        }

        //TESYSMODULE_API bool TESysOperatorAgingMonitorIsLastActionError(void* objHandle, int boardID, int dutIdx);
        public bool AgingMonitorIsLastActionError(int boardID, int dutIdx)
        {
            return DLL.Operator.AgingMonitorIsLastActionError(_OperatorHandle, boardID, dutIdx);
        }


        //TESYSMODULE_API int TESysOperatorTesterMonitorGetLastNotifyTickDiff(void* objHandle, int boardID);
        public int TesterMonitorGetLastNotifyTickDiff(int boardID)
        {
            return DLL.Operator.TesterMonitorGetLastNotifyTickDiff(_OperatorHandle, boardID);
        }


    }

}
