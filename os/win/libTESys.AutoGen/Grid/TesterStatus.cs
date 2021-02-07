using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace libTESys.AutoGen.Grid
{
    public class TesterStatus
    {
        private SourceGrid.Grid _Grid;

        private enum ColumnID
        {
            BID = 0,
            IPAddr,
            ErrFlag,
            DateTime,
            Aging,
            FileSync,
            HubSync,
            CRC,
            FWVer
        };

        private int[] _ColumnWidthArray = { 40/*BoardID*/,
                                            100, /*IP*/
                                            140, /*ErrFlag*/
                                            140 /*DateTime*/,
                                            550 /*Aging*/,
                                            200 /*FileSync*/,
                                            150 /*HubSync*/,
                                            100 /*CRC*/,
                                            250 /*FWVer*/ 
                                           };


        private int _TesterMaxCount;

        private SourceGrid.Cells.Views.Cell _CellViewTitle { get; }
        private SourceGrid.Cells.Views.Cell[] _CellViewData; // captionView0 = new SourceGrid.Cells.Views.Cell();
        private SourceGrid.Cells.Views.Cell _CellViewError;
        private Color[] _ColorCellViewData { get; } = { Color.White, Color.FromArgb(255, 235, 204) };

        private SourceGrid.Cells.Views.Cell[] _CellViewDataParm { get; } // captionView0 = new SourceGrid.Cells.Views.Cell();

        private Font _FontParmLink { get; }// = new Font(Grid.Font.Name, Grid.Font.Size, System.Drawing.FontStyle.Underline);//, Grid.Font.SizeInPoints, ((byte)(0)));

        public TesterStatus(SourceGrid.Grid grid, int testerMaxCount)
        {
            //System.Drawing.Color color = System.Drawing.Color.White;

            _Grid = grid;
            _TesterMaxCount = testerMaxCount;

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

        private int GetRowIndexFormBoardID(int boardID)
        {
            return boardID;
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
            _Grid.Redim(_TesterMaxCount + 1, Enum.GetValues(typeof(ColumnID)).Length);


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

            for (int ir = 0; ir < _TesterMaxCount; ir++, currentRow++)
            {
                string sztmp;
                int boardID = ir + 1;

                SourceGrid.Cells.Views.Cell viewCaption = _CellViewData[boardID % 2];
                SourceGrid.Cells.Views.Cell viewCaptionParm = _CellViewDataParm[boardID % 2];

                //JOB
                for (int ic = (int)ColumnID.BID; ic < _Grid.ColumnsCount; ic++)
                {
                    sztmp = string.Format("");
                    _Grid[currentRow, ic] = new SourceGrid.Cells.Cell(sztmp);
                    _Grid[currentRow, ic].View = viewCaption;
                    _Grid[currentRow, ic].ColumnSpan = 1;
                }

                sztmp = string.Format($"{boardID}");
                _Grid[currentRow, (int)ColumnID.BID].Value = sztmp;
                
                //Date Time
                sztmp = string.Format("xxx-xx-xx");
                _Grid[currentRow, (int)ColumnID.DateTime].Value = sztmp;
                
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

        public void UpdateData(Data.Status.Tester ts, Data.Status.Hub hubStatus)
        {
            int currentRow = GetRowIndexFormBoardID(ts.Board.BoardID);
            SourceGrid.Cells.Views.Cell viewCaption = _CellViewData[currentRow % 2];
                        
            //IP
            _Grid[currentRow, (int)ColumnID.IPAddr].Value = ts.Board.IPAddrString;

            //ErrFlag
            _Grid[currentRow, (int)ColumnID.ErrFlag].Value = ts.Board.ErrFlagString;

            //Date Time
            _Grid[currentRow, (int)ColumnID.DateTime].Value = API.Utils.GetDateTimeString(ts.TesterHeader.NotifyUtcTime);
                        
            //FileSync
            _Grid[currentRow, (int)ColumnID.FileSync].Value = ts.FileSync.AppStatus;
            
            //HubSync
            _Grid[currentRow, (int)ColumnID.HubSync].Value = hubStatus.CalCRCApp.AppStatus;
            
            //FileSync CRC-SUM
            _Grid[currentRow, (int)ColumnID.CRC].Value = string.Format($"{ts.FileSync.CrcSum}/{hubStatus.CalCRCApp.CrcSum} ");
            if (ts.FileSync.CrcSum == hubStatus.CalCRCApp.CrcSum)
            {
                _Grid[currentRow, (int)ColumnID.CRC].View = viewCaption;
            }
            else 
            {
                _Grid[currentRow, (int)ColumnID.CRC].View = _CellViewError;
            }
            
            //FWVer
            _Grid[currentRow, (int)ColumnID.FWVer].Value = ts.Board.FWVer;

            //Aging
            _Grid[currentRow, (int)ColumnID.Aging].Value = ts.Aging.AppStatus;
        }
    }
}
