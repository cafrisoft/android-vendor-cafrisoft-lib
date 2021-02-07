using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace libTESys.AutoGen.Grid
{
    public class AgingMonitor
    {
        private SourceGrid.Grid _Grid;

        private enum ColumnID
        {
            BID = 0,
            DutIdx,
            JobID,
            JobSt,
            ScID,
            ScCnt,
            TcID,
            TcCnt,
            TcStepID,
            TcStepCnt
        };

        private int[] _ColumnWidthArray = { 40  /*BoardID*/,
                                            40  /*DutIdx*/,
                                            50  /*JobID*/,
                                            100 /*JobStatsu*/,

                                            50  /*ScID*/,
                                            50  /*ScCnt*/,
                                            
                                            50  /*TcID*/,
                                            50  /*TcCnt*/,

                                            50  /*TcStepID*/,
                                            50  /*TcStepCnt*/,
                                         };


        private int _BoardMaxCount;
        private int _DutMaxCount;

        private SourceGrid.Cells.Views.Cell _CellViewTitle { get; }
        private SourceGrid.Cells.Views.Cell[] _CellViewData; // captionView0 = new SourceGrid.Cells.Views.Cell();
        private SourceGrid.Cells.Views.Cell _CellViewError;
        private Color[] _ColorCellViewData { get; } = { Color.White, Color.FromArgb(255, 235, 204) };

        private SourceGrid.Cells.Views.Cell[] _CellViewDataParm { get; } // captionView0 = new SourceGrid.Cells.Views.Cell();

        private Font _FontParmLink { get; }// = new Font(Grid.Font.Name, Grid.Font.Size, System.Drawing.FontStyle.Underline);//, Grid.Font.SizeInPoints, ((byte)(0)));

        public AgingMonitor(SourceGrid.Grid grid, int testerMaxCount, int dutCount)
        {
            //System.Drawing.Color color = System.Drawing.Color.White;

            _Grid = grid;
            _BoardMaxCount = testerMaxCount;
            _DutMaxCount = dutCount;

            _FontParmLink = new Font(_Grid.Font.Name, _Grid.Font.Size, System.Drawing.FontStyle.Underline);

            //Grid Title 설정 
            _CellViewTitle = new SourceGrid.Cells.Views.Cell();
            _CellViewTitle.BackColor = System.Drawing.Color.SteelBlue;
            _CellViewTitle.ForeColor = System.Drawing.Color.White;
            _CellViewTitle.TextAlignment = DevAge.Drawing.ContentAlignment.MiddleCenter;

            _CellViewData = new SourceGrid.Cells.Views.Cell[2];
            for (int i = 0; i < _CellViewData.Length; i++)
            {
                _CellViewData[i] = new SourceGrid.Cells.Views.Cell();
                _CellViewData[i].BackColor = _ColorCellViewData[i];
                //CellViewData[0].ForeColor = Color.White;
                //_CellViewData[i].TextAlignment = DevAge.Drawing.ContentAlignment.MiddleCenter;
                _CellViewData[i].TextAlignment = DevAge.Drawing.ContentAlignment.MiddleLeft;
                //CellViewData[i].WordWrap = false;
            }

            _CellViewError = new SourceGrid.Cells.Views.Cell();
            _CellViewError.BackColor = Color.Red;
            _CellViewError.TextAlignment = DevAge.Drawing.ContentAlignment.MiddleLeft;


            _CellViewDataParm = new SourceGrid.Cells.Views.Cell[2];
            for (int i = 0; i < _CellViewData.Length; i++)
            {
                _CellViewDataParm[i] = new SourceGrid.Cells.Views.Cell();
                _CellViewDataParm[i].BackColor = _ColorCellViewData[i];
                _CellViewDataParm[i].ForeColor = Color.Blue;
                _CellViewDataParm[i].Font = _FontParmLink;
                _CellViewDataParm[i].TextAlignment = DevAge.Drawing.ContentAlignment.MiddleCenter;
                //CellViewDataParm[i].WordWrap = false;
            }

            //SetupGrid();
        }

        private int GetRowIndex(int boardID, int dutIdx)
        {
            return 1 + (boardID-1)*_DutMaxCount + dutIdx;
        }

        public void SetupGrid()
        {
            SourceGrid.Cells.Views.Cell categoryView = new SourceGrid.Cells.Views.Cell();
            categoryView.Background = new DevAge.Drawing.VisualElements.BackgroundLinearGradient(Color.RoyalBlue, Color.LightBlue, 0);
            categoryView.ForeColor = Color.FromKnownColor(KnownColor.ActiveCaptionText);
            categoryView.TextAlignment = DevAge.Drawing.ContentAlignment.MiddleCenter;
            categoryView.Border = DevAge.Drawing.RectangleBorder.NoBorder;
            categoryView.Font = new Font(_Grid.Parent.Font, FontStyle.Bold);

            // Grid Set Size
            _Grid.Redim(0, 0);
            _Grid.Redim(_BoardMaxCount*_DutMaxCount + 1, Enum.GetValues(typeof(ColumnID)).Length);


            //Start Row Setting
            int currentRow = 0;
            string strtmp = string.Format($"");
            _Grid[currentRow, 0] = new SourceGrid.Cells.Cell(strtmp);
            _Grid[currentRow, 0].View = categoryView;
            _Grid[currentRow, 0].ColumnSpan = _Grid.ColumnsCount;

            //  Column Tile Setting
            for (int ic = 0; ic < _Grid.ColumnsCount; ic++)
            {
                _Grid.Columns.SetWidth(ic, 80);
                _Grid[currentRow, ic] = new SourceGrid.Cells.Cell(Enum.GetName(typeof(ColumnID), ic));
                _Grid[currentRow, ic].View = _CellViewTitle;
            }
            currentRow++;

            for (int ir = 0; ir < _BoardMaxCount; ir++ )
            {
                for(int dutIdx=0; dutIdx < 2; dutIdx++)
                {
                    string sztmp;
                    int boardID = ir + 1;

                    SourceGrid.Cells.Views.Cell viewCaption = _CellViewData[boardID % 2];
                    
                    sztmp = string.Format($"{boardID}");
                    _Grid[currentRow, (int)ColumnID.BID] = new SourceGrid.Cells.Cell(sztmp);
                    _Grid[currentRow, (int)ColumnID.BID].View = viewCaption;
                    _Grid[currentRow, (int)ColumnID.BID].ColumnSpan = 1;

                    sztmp = string.Format($"{dutIdx}");
                    _Grid[currentRow, (int)ColumnID.DutIdx] = new SourceGrid.Cells.Cell(sztmp);
                    _Grid[currentRow, (int)ColumnID.DutIdx].View = viewCaption;
                    _Grid[currentRow, (int)ColumnID.DutIdx].ColumnSpan = 1;


                    //JOB
                    for (int ic = (int)ColumnID.JobID; ic < _Grid.ColumnsCount; ic++)
                    {
                        sztmp = string.Format("");
                        _Grid[currentRow, ic] = new SourceGrid.Cells.Cell(sztmp);
                        _Grid[currentRow, ic].View = viewCaption;
                        _Grid[currentRow, ic].ColumnSpan = 1;
                    }


                    currentRow++;
                }

            }

            // Colmn Size Setting
            for (int ic = 0; ic < _Grid.ColumnsCount; ic++)
            {
                _Grid.Columns.SetWidth(ic, _ColumnWidthArray[ic]);
            }


        }

        public void Invalidate()
        {
            _Grid.Invalidate();
        }

        public void UpdateDataJob(int boardID, int dutIdx, int jobID, string jobStatus)
        {
            string sztmp;
            int currentRow = GetRowIndex(boardID, dutIdx);
            SourceGrid.Cells.Views.Cell viewCaption = _CellViewData[boardID % 2];
            
            //Job
            sztmp = string.Format($"{jobID}");
            _Grid[currentRow, (int)ColumnID.JobID] = new SourceGrid.Cells.Cell(sztmp);
            _Grid[currentRow, (int)ColumnID.JobID].View = viewCaption;
            _Grid[currentRow, (int)ColumnID.JobID].ColumnSpan = 1;


            //JobStatus
            sztmp = jobStatus;
            _Grid[currentRow, (int)ColumnID.JobSt] = new SourceGrid.Cells.Cell(sztmp);
            _Grid[currentRow, (int)ColumnID.JobSt].View = viewCaption;
            _Grid[currentRow, (int)ColumnID.JobSt].ColumnSpan = 1;
        }

        public void UpdateDataSc(int boardID, int dutIdx, int scID, int scIdx, int scCnt)
        {
            string sztmp;
            int currentRow = GetRowIndex(boardID, dutIdx);
            SourceGrid.Cells.Views.Cell viewCaption = _CellViewData[boardID % 2];

            //ScID
            sztmp = string.Format($"{scID}");
            _Grid[currentRow, (int)ColumnID.ScID] = new SourceGrid.Cells.Cell(sztmp);
            _Grid[currentRow, (int)ColumnID.ScID].View = viewCaption;
            _Grid[currentRow, (int)ColumnID.ScID].ColumnSpan = 1;

            //ScCnt
            sztmp = string.Format($"{scIdx + 1}/{scCnt}");
            _Grid[currentRow, (int)ColumnID.ScCnt] = new SourceGrid.Cells.Cell(sztmp);
            _Grid[currentRow, (int)ColumnID.ScCnt].View = viewCaption;
            _Grid[currentRow, (int)ColumnID.ScCnt].ColumnSpan = 1;

        }

        public void UpdateDataTc(int boardID, int dutIdx, int tcID, int tcIdx, int tcCnt)
        {
            string sztmp;
            int currentRow = GetRowIndex(boardID, dutIdx);
            SourceGrid.Cells.Views.Cell viewCaption = _CellViewData[boardID % 2];

            //ScID
            sztmp = string.Format($"{tcID}");
            _Grid[currentRow, (int)ColumnID.TcID] = new SourceGrid.Cells.Cell(sztmp);
            _Grid[currentRow, (int)ColumnID.TcID].View = viewCaption;
            _Grid[currentRow, (int)ColumnID.TcID].ColumnSpan = 1;

            //ScCnt
            sztmp = string.Format($"{tcIdx + 1}/{tcCnt}");
            _Grid[currentRow, (int)ColumnID.TcCnt] = new SourceGrid.Cells.Cell(sztmp);
            _Grid[currentRow, (int)ColumnID.TcCnt].View = viewCaption;
            _Grid[currentRow, (int)ColumnID.TcCnt].ColumnSpan = 1;

        }

        public void UpdateDataTcStep(int boardID, int dutIdx, int tcStepID, int tcStepIdx, int tcStepCnt)
        {
            string sztmp;
            int currentRow = GetRowIndex(boardID, dutIdx);
            SourceGrid.Cells.Views.Cell viewCaption = _CellViewData[boardID % 2];

            //ScID
            sztmp = string.Format($"{tcStepID}");
            _Grid[currentRow, (int)ColumnID.TcStepID] = new SourceGrid.Cells.Cell(sztmp);
            _Grid[currentRow, (int)ColumnID.TcStepID].View = viewCaption;
            _Grid[currentRow, (int)ColumnID.TcStepID].ColumnSpan = 1;

            //ScCnt
            sztmp = string.Format($"{tcStepIdx+1}/{tcStepCnt}");
            _Grid[currentRow, (int)ColumnID.TcStepCnt] = new SourceGrid.Cells.Cell(sztmp);
            _Grid[currentRow, (int)ColumnID.TcStepCnt].View = viewCaption;
            _Grid[currentRow, (int)ColumnID.TcStepCnt].ColumnSpan = 1;

        }
    }
}
