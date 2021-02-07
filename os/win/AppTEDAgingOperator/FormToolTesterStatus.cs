using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using TESys = libTESys.AutoGen;

namespace AppTEDAgingOperator
{
    public partial class FormToolTesterStatus : Form
    {
        private TESys.Grid.TesterStatus _TesterStatusGrid;

        private IntPtr _DataConsumerTesterStatusHandle = IntPtr.Zero;
        private IntPtr _DataConsumerHubStatusHandle = IntPtr.Zero;

        public FormToolTesterStatus()
        {
            InitializeComponent();

            _TesterStatusGrid = new TESys.Grid.TesterStatus(this.grid,
                                                                     TESys.API.Property.GetInt((int)TESys.API.Property.Tester.AvailableBoardMaxCount));

            //DataConsumer Tester 생성 
            _DataConsumerTesterStatusHandle = AppGlobal.Inst.Operator.DataConsumerTesterStatusCreate();

            //DataConsumer Hub 생성 
            _DataConsumerHubStatusHandle = AppGlobal.Inst.Operator.DataConsumerHubStatusCreate();
        }

        private void FormToolTesterStatus_Load(object sender, EventArgs e)
        {
            _TesterStatusGrid.SetupGrid();
            this.timerUpdateStatus.Start();
            this.timerTesterNodeUpdate.Start();
        }

        private void timerUpdateStatus_Tick(object sender, EventArgs e)
        {
            //Get HubStatus
            TESys.Data.Status.Hub hubStatus = AppGlobal.Inst.Operator.DataConsumerHubStatusGetApiData(this._DataConsumerHubStatusHandle);

            //Get TesterStatus
            TESys.API.PacketTesterStatusArray packetTesterStatusArray = AppGlobal.Inst.Operator.DataConsumerTesterStatusGetApiData(_DataConsumerTesterStatusHandle);
            //Debug.WriteLine($"itemCnt={packetTesterStatusArray.Count}");

            for (int i = 0; i < packetTesterStatusArray.Count; i++)
            {
                TESys.Data.Status.Tester tstrStat = packetTesterStatusArray[i];
              //  Debug.WriteLine($"BoardID={tstrStat.Board.BoardID} ");

                _TesterStatusGrid.UpdateData(tstrStat, hubStatus);
            }

            if (packetTesterStatusArray.Count > 0)
            {
                _TesterStatusGrid.Invalidate();
            }

        }

        private void timerTesterNodeUpdate_Tick(object sender, EventArgs e)
        {
            for(int boardID = 1; boardID <=500; boardID++)
            {
                int diff = AppGlobal.Inst.Operator.TesterMonitorGetLastNotifyTickDiff(boardID);
                this.testerNode.UpdateData_NotifyTickDiff(boardID, diff);
            }

            this.testerNode.UpdateScreen();
        }
    }
}
