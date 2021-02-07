using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace libFormCtrlAgingMonitor
{
    public partial class DutNode: UserControl
    {
        private const int _LabelGapWidth = 30;
        private const int _LabelGapHeight = 20;
        private const int _NodeColumnCount = 50;
        private const int _NodeRowCount = 20;

        private Bitmap _BitmapBackground = null;
        private Bitmap _BitmapForeground = null;
        
        private SolidBrush _BackgroundBrush;  // Background brush

        private SolidBrush _GridDataBrush;
        private SolidBrush _GridRowBrush;// = new SolidBrush(Color.Turquoise);
        private SolidBrush _GridColBrush;// = new SolidBrush(Color.Yellow);
        private Pen _Grid_pen;// = new Pen(System.Drawing.Color.Black, 2);
        private Font _Grid_cell_font;// = new Font(FontFamily.GenericSansSerif, 6.5F, FontStyle.Bold);

        private SolidBrush [] _NodeBrush;
        //private SolidBrush _NodeBrushRunPython;
        //private SolidBrush _NodeBrushIsLastActionError;
        //private SolidBrush _NodeBrushNormal;
        private int[] _NodeBrushBeforeIndexArray;

        private bool _IsUpdatedForgroundBitmap = false;

        public DutNode()
        {
            _BackgroundBrush = new SolidBrush(Color.White);

            _NodeBrush = new SolidBrush[3];
            _NodeBrush[0] = new SolidBrush(Color.Green);
            _NodeBrush[1] = new SolidBrush(Color.Red);
            _NodeBrush[2] = new SolidBrush(Color.White);
            _NodeBrushBeforeIndexArray = new int[_NodeColumnCount * _NodeRowCount];
            for(int i = 0; i < _NodeColumnCount * _NodeRowCount; i++)
            {
                _NodeBrushBeforeIndexArray[i] = -1;
            }
            //_NodeBrushRunPython = new SolidBrush(Color.Green);
            //_NodeBrushIsLastActionError = new SolidBrush(Color.Red);
            //_NodeBrushNormal = new SolidBrush(Color.White);

            _GridColBrush = new SolidBrush(Color.DarkBlue);
            _GridRowBrush = new SolidBrush(Color.Magenta);
            _GridDataBrush = new SolidBrush(Color.MediumPurple); //filtering raw data

            _Grid_pen = new Pen(System.Drawing.Color.Black, 2);
            _Grid_cell_font = new Font(FontFamily.GenericSansSerif, 6.5F, FontStyle.Bold);

            InitializeComponent();

            //this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.UserPaint, true);
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
        }

        private void DutNode_Paint(object sender, PaintEventArgs e)
        {
            if (_BitmapBackground == null)
            {
                _BitmapBackground = new Bitmap(this.ClientSize.Width, this.ClientSize.Height);
                using (Graphics gr = Graphics.FromImage(_BitmapBackground))
                {
                    // Draw background
                    Rectangle bounds = new Rectangle(0, 0, this.ClientSize.Width, this.ClientSize.Height);
                    gr.FillRectangle(_BackgroundBrush, bounds);
                    DrawGrid(gr, _NodeColumnCount, _NodeRowCount);
                }
                _BitmapForeground = (Bitmap)_BitmapBackground.Clone();
            }

            if (_BitmapForeground != null)
            {
                e.Graphics.DrawImage(_BitmapForeground, e.ClipRectangle, e.ClipRectangle, GraphicsUnit.Pixel);
            }
        }

        private void DrawGrid(Graphics g, int nCapW, int nCapH)
        {
            int _xPt = this.Bounds.Width / (nCapW + 1); //Drive line
            int _yPt = this.Bounds.Height / (nCapH + 1); //Sense line

            //가로 라벨링
            for (int j = 0; j < nCapW; j++)
            {
                // 오른쪽부터 D12 ~ D1 순으로 라벨링 작업
                g.DrawString("C" + (j + 1), _Grid_cell_font, _GridColBrush, new Rectangle(5 + _LabelGapWidth + (_xPt * j), 2, _xPt, _LabelGapHeight));
            }

            //세로 라벨링
            for (int i = 0; i < nCapH; i++)
            {
                //Label : Drive line
                g.DrawString("Dut" + (i%2), _Grid_cell_font, _GridRowBrush,
                    new Rectangle(2, _LabelGapHeight + (_yPt * i) + 5, _LabelGapWidth, _yPt));

            }
            
            //Draw Node
            for (int i = 0; i < nCapH; i++)
            {
                for (int j = 0; j < nCapW; j++)
                {
                    g.DrawRectangle(_Grid_pen, _LabelGapWidth + _xPt * j, _LabelGapHeight + _yPt * i, _xPt, _yPt);
                }
            }
                        
        }

        private void DutNode_Resize(object sender, EventArgs e)
        {
            if (_BitmapForeground != null)
            {
                _BitmapForeground.Dispose();
                _BitmapForeground = null;
            }

            if (_BitmapBackground != null)
            {
                _BitmapBackground.Dispose();
                _BitmapBackground = null;
            }

            for (int i = 0; i < _NodeColumnCount * _NodeRowCount; i++)
            {
                _NodeBrushBeforeIndexArray[i] = -1;
            }


            this.Refresh();
        }

        public void UpdateNode(int boardID, int dutIdx, bool isRunPython, bool isLastActionError)
        {
            int nodeBrushIdx;
            int xIdx = (boardID - 1) % _NodeColumnCount;
            int yIdx = ((boardID - 1) / _NodeColumnCount) * 2 + dutIdx;
            int arrIdx = yIdx * _NodeColumnCount + xIdx;

            if (isRunPython)
            {
                nodeBrushIdx = 0;
                //nodeBrush = _NodeBrushRunPython;
            }
            else if (isLastActionError)
            {
                nodeBrushIdx = 1;
                //nodeBrush = _NodeBrushIsLastActionError;
            }
            else
            {
                nodeBrushIdx = 2;
                //nodeBrush = _NodeBrushNormal;
            }

            if ( (_BitmapForeground != null)  && (_NodeBrushBeforeIndexArray[arrIdx] != nodeBrushIdx) )
            {
                using (Graphics gr = Graphics.FromImage(_BitmapForeground))
                {
                    int _xPt = this.Bounds.Width / (_NodeColumnCount + 1); //Drive line
                    int _yPt = this.Bounds.Height / (_NodeRowCount + 1); //Sense line
                    
                    Brush nodeBrush = _NodeBrush[nodeBrushIdx];
                    

                    gr.FillRectangle(nodeBrush,
                                    _LabelGapWidth + (_xPt * xIdx) + 2,
                                    _LabelGapHeight + (_yPt * yIdx) + 2,
                                    (int)_xPt - 3, (int)_yPt - 3);

                    gr.DrawString(Convert.ToString(boardID),
                                  _Grid_cell_font,
                                  _GridDataBrush,
                                  (_LabelGapWidth) + (_xPt * xIdx) + 2,
                                  (_LabelGapHeight) + (_yPt * yIdx) + 7);

                    _IsUpdatedForgroundBitmap = true;
                    _NodeBrushBeforeIndexArray[arrIdx] = nodeBrushIdx;
                }
            }

        }

        public void UpdateScreen()
        {
            if (_BitmapForeground != null && _IsUpdatedForgroundBitmap)
            {
                this.Invalidate();
                _IsUpdatedForgroundBitmap = false;
            }
        }

    }
}
