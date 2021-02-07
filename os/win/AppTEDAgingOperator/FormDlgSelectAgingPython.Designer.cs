namespace AppTEDAgingOperator
{
    partial class FormDlgSelectAgingPython
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.radioButtonSC = new System.Windows.Forms.RadioButton();
            this.radioButtonJob = new System.Windows.Forms.RadioButton();
            this.radioButtonTC = new System.Windows.Forms.RadioButton();
            this.timerFileSyncReadCheck = new System.Windows.Forms.Timer(this.components);
            this.listBoxPython = new System.Windows.Forms.ListBox();
            this.labelFileSyncStatus = new System.Windows.Forms.Label();
            this.buttonSelectPython = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // radioButtonSC
            // 
            this.radioButtonSC.AutoSize = true;
            this.radioButtonSC.Location = new System.Drawing.Point(76, 26);
            this.radioButtonSC.Name = "radioButtonSC";
            this.radioButtonSC.Size = new System.Drawing.Size(40, 16);
            this.radioButtonSC.TabIndex = 1;
            this.radioButtonSC.TabStop = true;
            this.radioButtonSC.Text = "SC";
            this.radioButtonSC.UseVisualStyleBackColor = true;
            this.radioButtonSC.CheckedChanged += new System.EventHandler(this.radioButtonSC_CheckedChanged);
            // 
            // radioButtonJob
            // 
            this.radioButtonJob.AutoSize = true;
            this.radioButtonJob.Location = new System.Drawing.Point(24, 26);
            this.radioButtonJob.Name = "radioButtonJob";
            this.radioButtonJob.Size = new System.Drawing.Size(46, 16);
            this.radioButtonJob.TabIndex = 0;
            this.radioButtonJob.TabStop = true;
            this.radioButtonJob.Text = "JOB";
            this.radioButtonJob.UseVisualStyleBackColor = true;
            this.radioButtonJob.CheckedChanged += new System.EventHandler(this.radioButtonJob_CheckedChanged);
            // 
            // radioButtonTC
            // 
            this.radioButtonTC.AutoSize = true;
            this.radioButtonTC.Location = new System.Drawing.Point(122, 26);
            this.radioButtonTC.Name = "radioButtonTC";
            this.radioButtonTC.Size = new System.Drawing.Size(40, 16);
            this.radioButtonTC.TabIndex = 2;
            this.radioButtonTC.TabStop = true;
            this.radioButtonTC.Text = "TC";
            this.radioButtonTC.UseVisualStyleBackColor = true;
            this.radioButtonTC.CheckedChanged += new System.EventHandler(this.radioButtonTC_CheckedChanged);
            // 
            // timerFileSyncReadCheck
            // 
            this.timerFileSyncReadCheck.Interval = 500;
            this.timerFileSyncReadCheck.Tick += new System.EventHandler(this.timerFileSyncReadCheck_Tick);
            // 
            // listBoxPython
            // 
            this.listBoxPython.FormattingEnabled = true;
            this.listBoxPython.ItemHeight = 12;
            this.listBoxPython.Location = new System.Drawing.Point(25, 65);
            this.listBoxPython.Name = "listBoxPython";
            this.listBoxPython.Size = new System.Drawing.Size(195, 244);
            this.listBoxPython.TabIndex = 3;
            this.listBoxPython.SelectedIndexChanged += new System.EventHandler(this.listBoxPython_SelectedIndexChanged);
            // 
            // labelFileSyncStatus
            // 
            this.labelFileSyncStatus.AutoSize = true;
            this.labelFileSyncStatus.Location = new System.Drawing.Point(31, 330);
            this.labelFileSyncStatus.Name = "labelFileSyncStatus";
            this.labelFileSyncStatus.Size = new System.Drawing.Size(23, 12);
            this.labelFileSyncStatus.TabIndex = 4;
            this.labelFileSyncStatus.Text = "---";
            // 
            // buttonSelectPython
            // 
            this.buttonSelectPython.Location = new System.Drawing.Point(251, 74);
            this.buttonSelectPython.Name = "buttonSelectPython";
            this.buttonSelectPython.Size = new System.Drawing.Size(96, 37);
            this.buttonSelectPython.TabIndex = 5;
            this.buttonSelectPython.Text = "Select";
            this.buttonSelectPython.UseVisualStyleBackColor = true;
            this.buttonSelectPython.Click += new System.EventHandler(this.buttonSelectPython_Click);
            // 
            // FormDlgSelectAgingPython
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(405, 377);
            this.Controls.Add(this.buttonSelectPython);
            this.Controls.Add(this.labelFileSyncStatus);
            this.Controls.Add(this.listBoxPython);
            this.Controls.Add(this.radioButtonJob);
            this.Controls.Add(this.radioButtonTC);
            this.Controls.Add(this.radioButtonSC);
            this.Name = "FormDlgSelectAgingPython";
            this.Text = "FormDlgSelectAgingPython";
            this.Load += new System.EventHandler(this.FormDlgSelectAgingPython_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton radioButtonSC;
        private System.Windows.Forms.RadioButton radioButtonJob;
        private System.Windows.Forms.RadioButton radioButtonTC;
        private System.Windows.Forms.Timer timerFileSyncReadCheck;
        private System.Windows.Forms.ListBox listBoxPython;
        private System.Windows.Forms.Label labelFileSyncStatus;
        private System.Windows.Forms.Button buttonSelectPython;
    }
}