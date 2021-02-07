using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using TESys = libTESys.AutoGen;

namespace AppTEDAgingOperator
{
    public partial class FormAgingMonitor : Form
    {
        private TESys.Grid.AgingMonitor _AgingMonitorGrid;
        private int _BoardMaxCount;
        private int _DutMaxCount;

        public FormAgingMonitor()
        {
            InitializeComponent();

            _BoardMaxCount = TESys.API.Property.GetInt((int)TESys.API.Property.Tester.AvailableBoardMaxCount);
            _DutMaxCount = 2;

            _AgingMonitorGrid = new TESys.Grid.AgingMonitor(this.gridAgingMonitor,
                                                            _BoardMaxCount,
                                                            _DutMaxCount /*dutCount */
                                                            );

        }

        private void FormAgingMonitor_Load(object sender, EventArgs e)
        {
            _AgingMonitorGrid.SetupGrid();
            this.timerAgingStatusUpdate.Start();
        }

        private void timerAgingStatusUpdate_Tick(object sender, EventArgs e)
        {
#if true
            for(int boardID = 1; boardID <= _BoardMaxCount; boardID++)
            {
                for(int dutIdx = 0; dutIdx < _DutMaxCount; dutIdx++)
                {
                    int jobID = AppGlobal.Inst.Operator.AgingMonitorGetJobID(boardID, dutIdx);
                    string strStatus = AppGlobal.Inst.Operator.AgingMonitorGetJobStatusString(boardID, dutIdx);
                    _AgingMonitorGrid.UpdateDataJob(boardID, dutIdx, jobID, strStatus);

                    int scID = AppGlobal.Inst.Operator.AgingMonitorGetScID(boardID, dutIdx);
                    int scIdx = AppGlobal.Inst.Operator.AgingMonitorGetScIndex(boardID, dutIdx);
                    int scCnt = AppGlobal.Inst.Operator.AgingMonitorGetScCount(boardID, dutIdx);
                    _AgingMonitorGrid.UpdateDataSc(boardID, dutIdx, scID, scIdx, scCnt);

                    int tcID = AppGlobal.Inst.Operator.AgingMonitorGetTcID(boardID, dutIdx);
                    int tcIdx = AppGlobal.Inst.Operator.AgingMonitorGetTcIndex(boardID, dutIdx);
                    int tcCnt = AppGlobal.Inst.Operator.AgingMonitorGetTcCount(boardID, dutIdx);
                    _AgingMonitorGrid.UpdateDataTc(boardID, dutIdx, tcID, tcIdx, tcCnt);

                    int tcStepID = AppGlobal.Inst.Operator.AgingMonitorGetTcStepID(boardID, dutIdx);
                    int tcStepIdx = AppGlobal.Inst.Operator.AgingMonitorGetTcStepIndex(boardID, dutIdx);
                    int tcStepCnt = AppGlobal.Inst.Operator.AgingMonitorGetTcStepCount(boardID, dutIdx);
                    _AgingMonitorGrid.UpdateDataTcStep(boardID, dutIdx, tcStepID, tcStepIdx, tcStepCnt);

                    bool isRunPython = AppGlobal.Inst.Operator.AgingMonitorIsRunPython(boardID, dutIdx);
                    bool isLastActionError = AppGlobal.Inst.Operator.AgingMonitorIsLastActionError(boardID, dutIdx);

                    this.dutNode.UpdateNode(boardID, dutIdx, isRunPython, isLastActionError);
                }
            }

            _AgingMonitorGrid.Invalidate();
            this.dutNode.UpdateScreen();
#endif
        }
    }
}
