namespace AppTEDAgingOperator
{
    partial class FormToolTesterStatus
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
            this.tabControl = new System.Windows.Forms.TabControl();
            this.tabPageGrid = new System.Windows.Forms.TabPage();
            this.grid = new SourceGrid.Grid();
            this.tabPageNode = new System.Windows.Forms.TabPage();
            this.timerUpdateStatus = new System.Windows.Forms.Timer(this.components);
            this.testerNode = new libFormCtrlTesterStatus.TesterNode();
            this.timerTesterNodeUpdate = new System.Windows.Forms.Timer(this.components);
            this.tabControl.SuspendLayout();
            this.tabPageGrid.SuspendLayout();
            this.tabPageNode.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl
            // 
            this.tabControl.Controls.Add(this.tabPageGrid);
            this.tabControl.Controls.Add(this.tabPageNode);
            this.tabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl.Location = new System.Drawing.Point(0, 0);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(890, 555);
            this.tabControl.TabIndex = 0;
            // 
            // tabPageGrid
            // 
            this.tabPageGrid.Controls.Add(this.grid);
            this.tabPageGrid.Location = new System.Drawing.Point(4, 22);
            this.tabPageGrid.Name = "tabPageGrid";
            this.tabPageGrid.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageGrid.Size = new System.Drawing.Size(882, 529);
            this.tabPageGrid.TabIndex = 0;
            this.tabPageGrid.Text = "Grid";
            this.tabPageGrid.UseVisualStyleBackColor = true;
            // 
            // grid
            // 
            this.grid.Dock = System.Windows.Forms.DockStyle.Fill;
            this.grid.EnableSort = true;
            this.grid.Location = new System.Drawing.Point(3, 3);
            this.grid.Name = "grid";
            this.grid.OptimizeMode = SourceGrid.CellOptimizeMode.ForRows;
            this.grid.SelectionMode = SourceGrid.GridSelectionMode.Cell;
            this.grid.Size = new System.Drawing.Size(876, 523);
            this.grid.TabIndex = 0;
            this.grid.TabStop = true;
            this.grid.ToolTipText = "";
            // 
            // tabPageNode
            // 
            this.tabPageNode.Controls.Add(this.testerNode);
            this.tabPageNode.Location = new System.Drawing.Point(4, 22);
            this.tabPageNode.Name = "tabPageNode";
            this.tabPageNode.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageNode.Size = new System.Drawing.Size(882, 529);
            this.tabPageNode.TabIndex = 1;
            this.tabPageNode.Text = "Node";
            this.tabPageNode.UseVisualStyleBackColor = true;
            // 
            // timerUpdateStatus
            // 
            this.timerUpdateStatus.Interval = 1000;
            this.timerUpdateStatus.Tick += new System.EventHandler(this.timerUpdateStatus_Tick);
            // 
            // testerNode
            // 
            this.testerNode.Dock = System.Windows.Forms.DockStyle.Fill;
            this.testerNode.Location = new System.Drawing.Point(3, 3);
            this.testerNode.Name = "testerNode";
            this.testerNode.Size = new System.Drawing.Size(876, 523);
            this.testerNode.TabIndex = 0;
            // 
            // timerTesterNodeUpdate
            // 
            this.timerTesterNodeUpdate.Interval = 1000;
            this.timerTesterNodeUpdate.Tick += new System.EventHandler(this.timerTesterNodeUpdate_Tick);
            // 
            // FormToolTesterStatus
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(890, 555);
            this.Controls.Add(this.tabControl);
            this.Name = "FormToolTesterStatus";
            this.Text = "FormToolTesterStatus";
            this.Load += new System.EventHandler(this.FormToolTesterStatus_Load);
            this.tabControl.ResumeLayout(false);
            this.tabPageGrid.ResumeLayout(false);
            this.tabPageNode.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl;
        private System.Windows.Forms.TabPage tabPageGrid;
        private System.Windows.Forms.TabPage tabPageNode;
        private SourceGrid.Grid grid;
        private System.Windows.Forms.Timer timerUpdateStatus;
        private libFormCtrlTesterStatus.TesterNode testerNode;
        private System.Windows.Forms.Timer timerTesterNodeUpdate;
    }
}