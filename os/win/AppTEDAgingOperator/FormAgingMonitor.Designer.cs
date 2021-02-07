namespace AppTEDAgingOperator
{
    partial class FormAgingMonitor
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
            this.gridAgingMonitor = new SourceGrid.Grid();
            this.timerAgingStatusUpdate = new System.Windows.Forms.Timer(this.components);
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPageGrid = new System.Windows.Forms.TabPage();
            this.tabPageNode = new System.Windows.Forms.TabPage();
            this.dutNode = new libFormCtrlAgingMonitor.DutNode();
            this.tabControl1.SuspendLayout();
            this.tabPageGrid.SuspendLayout();
            this.tabPageNode.SuspendLayout();
            this.SuspendLayout();
            // 
            // gridAgingMonitor
            // 
            this.gridAgingMonitor.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gridAgingMonitor.EnableSort = true;
            this.gridAgingMonitor.Location = new System.Drawing.Point(3, 3);
            this.gridAgingMonitor.Name = "gridAgingMonitor";
            this.gridAgingMonitor.OptimizeMode = SourceGrid.CellOptimizeMode.ForRows;
            this.gridAgingMonitor.SelectionMode = SourceGrid.GridSelectionMode.Cell;
            this.gridAgingMonitor.Size = new System.Drawing.Size(786, 418);
            this.gridAgingMonitor.TabIndex = 1;
            this.gridAgingMonitor.TabStop = true;
            this.gridAgingMonitor.ToolTipText = "";
            // 
            // timerAgingStatusUpdate
            // 
            this.timerAgingStatusUpdate.Interval = 1000;
            this.timerAgingStatusUpdate.Tick += new System.EventHandler(this.timerAgingStatusUpdate_Tick);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPageGrid);
            this.tabControl1.Controls.Add(this.tabPageNode);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(800, 450);
            this.tabControl1.TabIndex = 2;
            // 
            // tabPageGrid
            // 
            this.tabPageGrid.Controls.Add(this.gridAgingMonitor);
            this.tabPageGrid.Location = new System.Drawing.Point(4, 22);
            this.tabPageGrid.Name = "tabPageGrid";
            this.tabPageGrid.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageGrid.Size = new System.Drawing.Size(792, 424);
            this.tabPageGrid.TabIndex = 0;
            this.tabPageGrid.Text = "Grid";
            this.tabPageGrid.UseVisualStyleBackColor = true;
            // 
            // tabPageNode
            // 
            this.tabPageNode.Controls.Add(this.dutNode);
            this.tabPageNode.Location = new System.Drawing.Point(4, 22);
            this.tabPageNode.Name = "tabPageNode";
            this.tabPageNode.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageNode.Size = new System.Drawing.Size(792, 424);
            this.tabPageNode.TabIndex = 1;
            this.tabPageNode.Text = "Node";
            this.tabPageNode.UseVisualStyleBackColor = true;
            // 
            // dutNode
            // 
            this.dutNode.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dutNode.Location = new System.Drawing.Point(3, 3);
            this.dutNode.Name = "dutNode";
            this.dutNode.Size = new System.Drawing.Size(786, 418);
            this.dutNode.TabIndex = 0;
            // 
            // FormAgingMonitor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.tabControl1);
            this.Name = "FormAgingMonitor";
            this.Text = "FormAgingMonitor";
            this.Load += new System.EventHandler(this.FormAgingMonitor_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPageGrid.ResumeLayout(false);
            this.tabPageNode.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private SourceGrid.Grid gridAgingMonitor;
        private System.Windows.Forms.Timer timerAgingStatusUpdate;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPageGrid;
        private System.Windows.Forms.TabPage tabPageNode;
        private libFormCtrlAgingMonitor.DutNode dutNode;
    }
}