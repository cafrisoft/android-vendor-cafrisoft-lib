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

namespace AppTEDAgingOperator
{
    public partial class FormFrameWnd : Form
    {
        private enum ToolID
        {
            TesterStatus = 0,
            AgingMonitor

        };

        private Dictionary<ToolID, Form> FormTools = new Dictionary<ToolID, Form>();

        //TestAging Item
        FormDlgSelectAgingPython.PyiFileType _TestAgingPyFileType;
        int _TestAgingPyFileID;

        public FormFrameWnd()
        {
            InitializeComponent();
        }

        private void FormToolCreate(ToolID tid)
        {
            Form form = null;

            Func<ToolID, int> AlloceAndAddToCollection = (toolid) =>
            {
                switch (toolid)
                {
                    case ToolID.TesterStatus:
                        form = new FormToolTesterStatus();
                        break;

                    case ToolID.AgingMonitor:
                        form = new FormAgingMonitor();
                        break;
                }

                form.MdiParent = this;
                FormTools.Add(toolid, form);

                return 0;
            };


            try
            {
                form = FormTools[tid];

                // Form이 이미 생성되어 있으나, Disposed된 상태인지 체크 
                if (form.IsDisposed)
                {
                    //Disposed이면  ObjectDisposedException 을 던진다.
                    throw new ObjectDisposedException(tid.ToString());
                }
            }
            catch (KeyNotFoundException)
            {
                AlloceAndAddToCollection(tid);
            }
            catch (ObjectDisposedException)
            {
                FormTools.Remove(tid);
                AlloceAndAddToCollection(tid);
            }

        }

        private void FormToolShow(ToolID tid)
        {
            try
            {
                Form form = FormTools[tid];
                form.Show();
                form.Activate();

            }
            catch (KeyNotFoundException)
            {
                Console.WriteLine($"[FormToolShow] ToolID={tid} is not in Dictionary.");
            }

        }

        private void FormToolCreateAndShow(ToolID tid)
        {
            FormToolCreate(tid);
            FormToolShow(tid);
        }


        private void FormFrameWnd_Load(object sender, EventArgs e)
        {
            FormToolCreateAndShow(ToolID.TesterStatus);
        }

        private void connectToTESysCtrlHubToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(!AppGlobal.Inst.Operator.IsConnect())
            {
                AppGlobal.Inst.Operator.Connect();
            }

        }

        private void disconnectFormTESysCtrlHubToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (AppGlobal.Inst.Operator.IsConnect())
            {
                AppGlobal.Inst.Operator.Disconnect();
            }
        }

        private void timerNotifyTesterStatus_Tick(object sender, EventArgs e)
        {
            if (AppGlobal.Inst.Operator.IsConnect())
            {

            }

        }

        private void runFileSyncToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (AppGlobal.Inst.Operator.IsConnect())
            {
                AppGlobal.Inst.Operator.C_OHT_RunFileSync();
                AppGlobal.Inst.Operator.C_OH_RunHubCalCRC();
                AppGlobal.Inst.Operator.FileSyncRun();
            }
        }

        private void fWUpgradeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (AppGlobal.Inst.Operator.IsConnect())
            {
                AppGlobal.Inst.Operator.C_OHT_RunFWUpgrade();
            }
        }

        private void runTCToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (AppGlobal.Inst.Operator.IsConnect())
            {
                using (FormDlgSelectAgingPython dlg = new FormDlgSelectAgingPython())
                {
                    DialogResult res = dlg.ShowDialog();
                    if (res == DialogResult.OK)
                    {
                        if (dlg.SelectedPyFileType == FormDlgSelectAgingPython.PyiFileType.JOB)
                        {
                            AppGlobal.Inst.Operator.C_OHT_RunPythonJOB(dlg.SelectedPyFileID /*jobNo*/);
                        }
                        else if (dlg.SelectedPyFileType == FormDlgSelectAgingPython.PyiFileType.SC)
                        {
                            AppGlobal.Inst.Operator.C_OHT_RunPythonSC(dlg.SelectedPyFileID /*scNo*/);
                        }
                        else if (dlg.SelectedPyFileType == FormDlgSelectAgingPython.PyiFileType.TC)
                        {
                            AppGlobal.Inst.Operator.C_OHT_RunPythonTC(dlg.SelectedPyFileID /*tcNo*/);
                        }
                        
                    }
                }

                
            }
                        

        }

        private void timerTestAging_Tick(object sender, EventArgs e)
        {
            if (AppGlobal.Inst.Operator.IsConnect())
            {
                if (_TestAgingPyFileType == FormDlgSelectAgingPython.PyiFileType.JOB)
                {
                    AppGlobal.Inst.Operator.C_OHT_RunPythonJOB(_TestAgingPyFileID /*jobNo*/);
                }
                else if (_TestAgingPyFileType == FormDlgSelectAgingPython.PyiFileType.SC)
                {
                    AppGlobal.Inst.Operator.C_OHT_RunPythonSC(_TestAgingPyFileID /*scNo*/);
                }
                else if (_TestAgingPyFileType == FormDlgSelectAgingPython.PyiFileType.TC)
                {
                    AppGlobal.Inst.Operator.C_OHT_RunPythonTC(_TestAgingPyFileID /*tcNo*/);
                }
            }
            else
            {
                this.timerTestAging.Stop();
                MessageBox.Show("CmdSocket 접속이 끊어졌습니다. Aging을 종료합니다.");
            }
            
        }

        private void startTestAgingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (AppGlobal.Inst.Operator.IsConnect())
            {
                using (FormDlgSelectAgingPython dlg = new FormDlgSelectAgingPython())
                {
                    DialogResult res = dlg.ShowDialog();
                    if (res == DialogResult.OK)
                    {
                        this._TestAgingPyFileID = dlg.SelectedPyFileID;
                        this._TestAgingPyFileType = dlg.SelectedPyFileType;

                        //Debug.Print("Aging");
                        this.timerTestAging.Start();
                    }
                }
            }
        }

        private void stopTestAgingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.timerTestAging.Stop();
        }

        private void testerStatusWindowToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FormToolCreateAndShow(ToolID.TesterStatus);
        }

        private void agingMonitorWindowToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FormToolCreateAndShow(ToolID.AgingMonitor);
        }
    }

} //namespace AppTEDAgingOperator
