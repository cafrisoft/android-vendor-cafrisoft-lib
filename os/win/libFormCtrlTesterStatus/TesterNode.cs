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
using System.Diagnostics;

namespace libFormCtrlTesterStatus
{
    public partial class TesterNode : UserControl
    {
        private const int _LabelGapWidth = 30;
        private const int _LabelGapHeight = 20;
        private const int _NodeColumnCount = 25;
        private const int _NodeRowCount = 20;

        private Bitmap _BitmapBackground = null;
        private Bitmap _BitmapForeground = null;

        private SolidBrush _BackgroundBrush;  // Background brush

        private SolidBrush _GridDataBrush;
        private SolidBrush _GridRowBrush;// = new SolidBrush(Color.Turquoise);
        private SolidBrush _GridColBrush;// = new SolidBrush(Color.Yellow);
        private Pen _Grid_pen;// = new Pen(System.Drawing.Color.Black, 2);
        private Font _Grid_cell_font;// = new Font(FontFamily.GenericSansSerif, 6.5F, FontStyle.Bold);

        private const int _TimerDiffMaxCount = 10;
        private SolidBrush [] _NodeBrushTimerDiff;

        private bool _IsUpdatedForgroundBitmap = false;
        private int[] _NotifyTickDiffBeforeValueArray;


        public TesterNode()
        {
            _BackgroundBrush = new SolidBrush(Color.White);
            _NodeBrushTimerDiff = new SolidBrush[_TimerDiffMaxCount];
            for (int i = 0; i < _TimerDiffMaxCount; i++)
            {
                //int c = 255 - i*25;
                //_NodeBrushTimerDiff[i] = new SolidBrush(Color.FromArgb(255, c, c, c));

                int c = i * 25;// 255 - i * 25;
                if(i==(_TimerDiffMaxCount-1))
                {
                    c = 255;
                }

                _NodeBrushTimerDiff[i] = new SolidBrush(Color.FromArgb(c, c, 255));
            }
            
            _GridColBrush = new SolidBrush(Color.DarkBlue);
            _GridRowBrush = new SolidBrush(Color.Magenta);
            _GridDataBrush = new SolidBrush(Color.MediumPurple); //filtering raw data

            _Grid_pen = new Pen(System.Drawing.Color.Black, 2);
            _Grid_cell_font = new Font(FontFamily.GenericSansSerif, 6.5F, FontStyle.Bold);


            _NotifyTickDiffBeforeValueArray = new int[_NodeColumnCount * _NodeRowCount];
            for (int i = 0; i < _NodeColumnCount * _NodeRowCount; i++)
            {
                _NotifyTickDiffBeforeValueArray[i] = 0xFFFFFF;
            }
                
            InitializeComponent();

            //this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.UserPaint, true);
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
        }

        private void TesterNode_Load(object sender, EventArgs e)
        {

        }

        private void TesterNode_SizeChanged(object sender, EventArgs e)
        {

        }

        private void TesterNode_Paint(object sender, PaintEventArgs e)
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

            //Draw Label
            for (int i = 0; i < nCapH; i++)
            {
                //Label : Drive line
                g.DrawString("R" + (i + 1), _Grid_cell_font, _GridRowBrush,
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


        private void TesterNode_Resize(object sender, EventArgs e)
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

            _NotifyTickDiffBeforeValueArray = new int[_NodeColumnCount * _NodeRowCount];
            for (int i = 0; i < _NodeColumnCount * _NodeRowCount; i++)
            {
                _NotifyTickDiffBeforeValueArray[i] = 0xFFFFFF;
            }


            this.Refresh();
        }

        public void UpdateData_NotifyTickDiff(int boardID, int diff)
        {
            //Debug.WriteLine($"BID={boardID}, Diff={diff}");

            int brushIdx = diff;
            if (diff >= _TimerDiffMaxCount)
            {
                brushIdx = _TimerDiffMaxCount - 1;
            }
            else if (diff < 0)
            {
                brushIdx = 0;
            }

            if ( (_BitmapForeground != null)  && (_NotifyTickDiffBeforeValueArray[boardID - 1]!= brushIdx) )
            {
                using (Graphics gr = Graphics.FromImage(_BitmapForeground))
                {
                    int _xPt = this.Bounds.Width / (_NodeColumnCount + 1); //Drive line
                    int _yPt = this.Bounds.Height / (_NodeRowCount + 1); //Sense line
                    int xIdx = (boardID - 1) % _NodeColumnCount;
                    int yIdx = ((boardID - 1) / _NodeColumnCount);

                    

                    gr.FillRectangle(_NodeBrushTimerDiff[brushIdx],
                                    _LabelGapWidth + (_xPt * xIdx) + 2,
                                    _LabelGapHeight + (_yPt * yIdx) + 2,
                                    (int)_xPt - 3, (int)_yPt - 3);

                    //filtering raw data
                    gr.DrawString(Convert.ToString(boardID),
                                  _Grid_cell_font,
                                  _GridDataBrush,
                                  (_LabelGapWidth) + (_xPt * xIdx) + 2,
                                  (_LabelGapHeight) + (_yPt * yIdx) + 7);


                    _IsUpdatedForgroundBitmap = true;
                    _NotifyTickDiffBeforeValueArray[boardID - 1] = brushIdx;
                }
            }

        }

        public void UpdateScreen()
        {
            if (_BitmapForeground != null && _IsUpdatedForgroundBitmap)
            {
                this.Refresh();
                _IsUpdatedForgroundBitmap = false;
            }
        }

    }
}
