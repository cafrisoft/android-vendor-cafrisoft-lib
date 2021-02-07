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
    public partial class FormDlgSelectAgingPython : Form
    {
        public enum PyiFileType
        {
            Unknown,
            JOB,
            SC,
            TC
        };

        private PyiFileType _SelectedPyFileType = PyiFileType.Unknown;
        private int _SelectedPyFileID = -1;

        public FormDlgSelectAgingPython()
        {
            InitializeComponent();
        }

        public PyiFileType SelectedPyFileType
        {
            get 
            {
                 return _SelectedPyFileType;
            }
        }

        public  int SelectedPyFileID
        {
            get
            {
                return _SelectedPyFileID;
            }
        }
                
        private void FormDlgSelectAgingPython_Load(object sender, EventArgs e)
        {
            if (!AppGlobal.Inst.Operator.FileSyncIsDone) {

                AppGlobal.Inst.Operator.FileSyncRun();
                
            }
            this.timerFileSyncReadCheck.Start();
        }

        private void UpdateUI()
        {
            this.listBoxPython.DataSource = null;
            this.listBoxPython.Items.Clear();
            DataTable dataTable = new DataTable("dataTable");
            dataTable.Columns.Add("Value", typeof(int));
            dataTable.Columns.Add("Display", typeof(string));

            if (this.radioButtonJob.Checked)
            {
                int cnt = AppGlobal.Inst.Operator.FileSyncJobCount;
                for (int i = 0; i < cnt; i++)
                {
                    int id = AppGlobal.Inst.Operator.FileSyncGetJobID(i);
                    //Debug.WriteLine($"jobid={id}");
                    //this.listBoxPython.Items.Add(string.Format($"JOB_{id:D4}.py"));
                    DataRow row = dataTable.NewRow();
                    row["Value"] = id;
                    row["Display"] = string.Format($"JOB_{id:D4}.py");
                    dataTable.Rows.Add(row);
                }
            }
            else if (this.radioButtonSC.Checked)
            {
                int cnt = AppGlobal.Inst.Operator.FileSyncScCount;
                for (int i = 0; i < cnt; i++)
                {
                    int id = AppGlobal.Inst.Operator.FileSyncGetScID(i);
                    //Debug.WriteLine($"Scid={id}");
                    //this.listBoxPython.Items.Add(string.Format($"SC_{id:D4}.py"));
                    DataRow row = dataTable.NewRow();
                    row["Value"] = id;
                    row["Display"] = string.Format($"SC_{id:D4}.py");
                    dataTable.Rows.Add(row);
                }
            }
            else if (this.radioButtonTC.Checked)
            {
                int cnt = AppGlobal.Inst.Operator.FileSyncTcCount;
                for (int i = 0; i < cnt; i++)
                {
                    int id = AppGlobal.Inst.Operator.FileSyncGetTcID(i);
                    //Debug.WriteLine($"Tcid={id}");
                    //this.listBoxPython.Items.Add(string.Format($"TC_{id:D4}.py"));

                    DataRow row = dataTable.NewRow();
                    row["Value"] = id;
                    row["Display"] = string.Format($"TC_{id:D4}.py");
                    dataTable.Rows.Add(row);
                }
            }

            this.listBoxPython.DataSource = dataTable;
            this.listBoxPython.DisplayMember = "Display";
            this.listBoxPython.ValueMember = "Value";
            this.listBoxPython.SelectedIndex = 0;
        }

        private void timerFileSyncReadCheck_Tick(object sender, EventArgs e)
        {
            if (AppGlobal.Inst.Operator.FileSyncIsDone)
            {
                this.timerFileSyncReadCheck.Stop();
                UpdateUI();
                this.labelFileSyncStatus.Text = "FileSync Done";
            }
            else {
                this.labelFileSyncStatus.Text = "waiting...";
            }
        }

        private void radioButtonJob_CheckedChanged(object sender, EventArgs e)
        {
            if (AppGlobal.Inst.Operator.FileSyncIsDone)
            {
                UpdateUI();
            }
        }

        private void radioButtonSC_CheckedChanged(object sender, EventArgs e)
        {
            if (AppGlobal.Inst.Operator.FileSyncIsDone)
            {
                UpdateUI();
            }
        }

        private void radioButtonTC_CheckedChanged(object sender, EventArgs e)
        {
            if (AppGlobal.Inst.Operator.FileSyncIsDone)
            {
                UpdateUI();
            }
        }

        private void listBoxPython_SelectedIndexChanged(object sender, EventArgs e)
        {
            //Debug.WriteLine("Select");
        }

        private void buttonSelectPython_Click(object sender, EventArgs e)
        {
            if (AppGlobal.Inst.Operator.FileSyncIsDone)
            {
                if (this.radioButtonJob.Checked)
                {
                    Debug.WriteLine($"SelectBtn : JOB {this.listBoxPython.SelectedValue}");
                    _SelectedPyFileType = PyiFileType.JOB;
                    _SelectedPyFileID = (int)this.listBoxPython.SelectedValue;

                    this.DialogResult = DialogResult.OK;
                    this.Close();
                }
                else if (this.radioButtonSC.Checked)
                {
                    Debug.WriteLine($"SelectBtn : SC {this.listBoxPython.SelectedValue}");
                    _SelectedPyFileType = PyiFileType.SC;
                    _SelectedPyFileID = (int)this.listBoxPython.SelectedValue;

                    this.DialogResult = DialogResult.OK;
                    this.Close();
                }
                else if (this.radioButtonTC.Checked)
                {
                    Debug.WriteLine($"SelectBtn : TC {this.listBoxPython.SelectedValue}");
                    _SelectedPyFileType = PyiFileType.TC;
                    _SelectedPyFileID = (int)this.listBoxPython.SelectedValue;

                    this.DialogResult = DialogResult.OK;
                    this.Close();
                }
            }
                
        }

        private void checkBoxAging_CheckedChanged(object sender, EventArgs e)
        {

        }
    }
}
