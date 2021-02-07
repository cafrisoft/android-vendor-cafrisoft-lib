using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.Data.Status
{
    public class Aging
    {
#if false
        struct Aging
        {
            //Python Aging File이 시작되고 종료된 시간이다. 
            time_t PyStartUtcTime;
            time_t PyStopUtcTime;  

            //Job
            int JobID;

            //Sc
            int ScID;
            int ScIndex;
            int ScCount;

            //Tc
            int TcID;
            int TcIndex;
            int TcCount;

            //TcStep
            int TcStepID;
            int TcStepIndex;
            int TcStepCount;
        };
#endif

        //Python Aging File이 시작되고 종료된 시간이다. 
        private long _PyStartUtcTime;
        private long _PyStopUtcTime;

        //Job
        private int _JobID = -1;

        //Sc
        private int _ScID = -1;
        private int _ScIndex = -1;
        private int _ScCount = -1;

        //Tc
        private int _TcID = -1;
        private int _TcIndex = -1;
        private int _TcCount = -1;

        //TcStep
        private int _TcStepID = -1;
        private int _TcStepIndex = -1;
        private int _TcStepCount = -1;

        public Aging(IntPtr rawByteData, int dataOffset)
        {
            //Python Aging File이 시작되고 종료된 시간이다. 
            _PyStartUtcTime = Marshal.ReadInt64(rawByteData, dataOffset); dataOffset += 8;
            _PyStopUtcTime = Marshal.ReadInt64(rawByteData, dataOffset); dataOffset += 8;


            //Job
            _JobID = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;

            //Sc
            _ScID = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _ScIndex = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _ScCount = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;

            //Tc
            _TcID = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _TcIndex = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _TcCount = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;

            //TcStep
            _TcStepID = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _TcStepIndex = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
            _TcStepCount = Marshal.ReadInt32(rawByteData, dataOffset); dataOffset += 4;
        }

        public int JobID { get { return _JobID;  } }
        public int ScID { get { return _ScID; } }
        public int ScIndex { get { return _ScIndex; } }
        public int ScCount { get { return _ScCount; } }
        public int TcID { get { return _TcID; } }
        public int TcIndex { get { return _TcIndex; } }
        public int TcCount { get { return _TcCount; } }
        public int TcStepID { get { return _TcStepID; } }
        public int TcStepIndex { get { return _TcStepIndex; } }
        public int TcStepCount { get { return _TcStepCount; } }

        public string AppStatus
        {
            get
            {
                string strStatus;
                
                strStatus = string.Format($"{API.Utils.GetDateTimeString(_PyStartUtcTime)}~{API.Utils.GetDateTimeString(_PyStopUtcTime)} ");
                strStatus += string.Format($"Job={_JobID} Sc={_ScID}:{_ScIndex}/{_ScCount} Tc={_TcID}:{_TcIndex}/{_TcCount}  TcStep={_TcStepID}:{_TcStepCount} ");

                return strStatus;
            }
        }
    }
}
