namespace AppTEDAgingOperator
{
    partial class FormFrameWnd
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.connectionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.connectToTESysCtrlHubToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.disconnectFormTESysCtrlHubToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.CommandToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.runFileSyncToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fWUpgradeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.agingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.runTCToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.testAgingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.startTestAgingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.stopTestAgingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.windowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.testerStatusWindowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.agingMonitorWindowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.timerNotifyTesterStatus = new System.Windows.Forms.Timer(this.components);
            this.timerTestAging = new System.Windows.Forms.Timer(this.components);
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.connectionToolStripMenuItem,
            this.CommandToolStripMenuItem,
            this.agingToolStripMenuItem,
            this.windowToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(845, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // connectionToolStripMenuItem
            // 
            this.connectionToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.connectToTESysCtrlHubToolStripMenuItem,
            this.disconnectFormTESysCtrlHubToolStripMenuItem});
            this.connectionToolStripMenuItem.Name = "connectionToolStripMenuItem";
            this.connectionToolStripMenuItem.Size = new System.Drawing.Size(81, 20);
            this.connectionToolStripMenuItem.Text = "Connection";
            // 
            // connectToTESysCtrlHubToolStripMenuItem
            // 
            this.connectToTESysCtrlHubToolStripMenuItem.Name = "connectToTESysCtrlHubToolStripMenuItem";
            this.connectToTESysCtrlHubToolStripMenuItem.Size = new System.Drawing.Size(232, 22);
            this.connectToTESysCtrlHubToolStripMenuItem.Text = "Connect to TESys-Server";
            this.connectToTESysCtrlHubToolStripMenuItem.Click += new System.EventHandler(this.connectToTESysCtrlHubToolStripMenuItem_Click);
            // 
            // disconnectFormTESysCtrlHubToolStripMenuItem
            // 
            this.disconnectFormTESysCtrlHubToolStripMenuItem.Name = "disconnectFormTESysCtrlHubToolStripMenuItem";
            this.disconnectFormTESysCtrlHubToolStripMenuItem.Size = new System.Drawing.Size(232, 22);
            this.disconnectFormTESysCtrlHubToolStripMenuItem.Text = "Disconnect form TESys-Sever";
            this.disconnectFormTESysCtrlHubToolStripMenuItem.Click += new System.EventHandler(this.disconnectFormTESysCtrlHubToolStripMenuItem_Click);
            // 
            // CommandToolStripMenuItem
            // 
            this.CommandToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.runFileSyncToolStripMenuItem,
            this.fWUpgradeToolStripMenuItem});
            this.CommandToolStripMenuItem.Name = "CommandToolStripMenuItem";
            this.CommandToolStripMenuItem.Size = new System.Drawing.Size(76, 20);
            this.CommandToolStripMenuItem.Text = "Command";
            // 
            // runFileSyncToolStripMenuItem
            // 
            this.runFileSyncToolStripMenuItem.Name = "runFileSyncToolStripMenuItem";
            this.runFileSyncToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
            this.runFileSyncToolStripMenuItem.Text = "Run FileSync";
            this.runFileSyncToolStripMenuItem.Click += new System.EventHandler(this.runFileSyncToolStripMenuItem_Click);
            // 
            // fWUpgradeToolStripMenuItem
            // 
            this.fWUpgradeToolStripMenuItem.Name = "fWUpgradeToolStripMenuItem";
            this.fWUpgradeToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
            this.fWUpgradeToolStripMenuItem.Text = "FW Upgrade";
            this.fWUpgradeToolStripMenuItem.Click += new System.EventHandler(this.fWUpgradeToolStripMenuItem_Click);
            // 
            // agingToolStripMenuItem
            // 
            this.agingToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.runTCToolStripMenuItem1,
            this.testAgingToolStripMenuItem});
            this.agingToolStripMenuItem.Name = "agingToolStripMenuItem";
            this.agingToolStripMenuItem.Size = new System.Drawing.Size(51, 20);
            this.agingToolStripMenuItem.Text = "Aging";
            // 
            // runTCToolStripMenuItem1
            // 
            this.runTCToolStripMenuItem1.Name = "runTCToolStripMenuItem1";
            this.runTCToolStripMenuItem1.Size = new System.Drawing.Size(132, 22);
            this.runTCToolStripMenuItem1.Text = "Run TC";
            this.runTCToolStripMenuItem1.Click += new System.EventHandler(this.runTCToolStripMenuItem1_Click);
            // 
            // testAgingToolStripMenuItem
            // 
            this.testAgingToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.startTestAgingToolStripMenuItem,
            this.stopTestAgingToolStripMenuItem});
            this.testAgingToolStripMenuItem.Name = "testAgingToolStripMenuItem";
            this.testAgingToolStripMenuItem.Size = new System.Drawing.Size(132, 22);
            this.testAgingToolStripMenuItem.Text = "Test-Aging";
            // 
            // startTestAgingToolStripMenuItem
            // 
            this.startTestAgingToolStripMenuItem.Name = "startTestAgingToolStripMenuItem";
            this.startTestAgingToolStripMenuItem.Size = new System.Drawing.Size(99, 22);
            this.startTestAgingToolStripMenuItem.Text = "Start";
            this.startTestAgingToolStripMenuItem.Click += new System.EventHandler(this.startTestAgingToolStripMenuItem_Click);
            // 
            // stopTestAgingToolStripMenuItem
            // 
            this.stopTestAgingToolStripMenuItem.Name = "stopTestAgingToolStripMenuItem";
            this.stopTestAgingToolStripMenuItem.Size = new System.Drawing.Size(99, 22);
            this.stopTestAgingToolStripMenuItem.Text = "Stop";
            this.stopTestAgingToolStripMenuItem.Click += new System.EventHandler(this.stopTestAgingToolStripMenuItem_Click);
            // 
            // windowToolStripMenuItem
            // 
            this.windowToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.testerStatusWindowToolStripMenuItem,
            this.agingMonitorWindowToolStripMenuItem});
            this.windowToolStripMenuItem.Name = "windowToolStripMenuItem";
            this.windowToolStripMenuItem.Size = new System.Drawing.Size(63, 20);
            this.windowToolStripMenuItem.Text = "Window";
            // 
            // testerStatusWindowToolStripMenuItem
            // 
            this.testerStatusWindowToolStripMenuItem.Name = "testerStatusWindowToolStripMenuItem";
            this.testerStatusWindowToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.testerStatusWindowToolStripMenuItem.Text = "Tester Status";
            this.testerStatusWindowToolStripMenuItem.Click += new System.EventHandler(this.testerStatusWindowToolStripMenuItem_Click);
            // 
            // agingMonitorWindowToolStripMenuItem
            // 
            this.agingMonitorWindowToolStripMenuItem.Name = "agingMonitorWindowToolStripMenuItem";
            this.agingMonitorWindowToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.agingMonitorWindowToolStripMenuItem.Text = "Aging Monitor";
            this.agingMonitorWindowToolStripMenuItem.Click += new System.EventHandler(this.agingMonitorWindowToolStripMenuItem_Click);
            // 
            // timerNotifyTesterStatus
            // 
            this.timerNotifyTesterStatus.Tick += new System.EventHandler(this.timerNotifyTesterStatus_Tick);
            // 
            // timerTestAging
            // 
            this.timerTestAging.Interval = 180000;
            this.timerTestAging.Tick += new System.EventHandler(this.timerTestAging_Tick);
            // 
            // FormFrameWnd
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(845, 539);
            this.Controls.Add(this.menuStrip1);
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "FormFrameWnd";
            this.Text = "FormFrameWnd";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Load += new System.EventHandler(this.FormFrameWnd_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem connectionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem connectToTESysCtrlHubToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem disconnectFormTESysCtrlHubToolStripMenuItem;
        private System.Windows.Forms.Timer timerNotifyTesterStatus;
        private System.Windows.Forms.ToolStripMenuItem CommandToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem runFileSyncToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fWUpgradeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem agingToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem runTCToolStripMenuItem1;
        private System.Windows.Forms.Timer timerTestAging;
        private System.Windows.Forms.ToolStripMenuItem testAgingToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem startTestAgingToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem stopTestAgingToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem windowToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem testerStatusWindowToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem agingMonitorWindowToolStripMenuItem;
    }
}