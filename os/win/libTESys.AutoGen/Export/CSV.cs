using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace libTESys.AutoGen.Export
{

#if false
    public static class CSV
    {
        public static void ToExcel(string csvFileName, string excelFileName)
        {
            var app = new Excel.Application();
            var workBooks = app.Workbooks;

            workBooks.OpenText(csvFileName,
                               DataType: Excel.XlTextParsingType.xlDelimited,
                               TextQualifier: Excel.XlTextQualifier.xlTextQualifierNone,
                               ConsecutiveDelimiter: true,
                               Semicolon: true);

            workBooks[1].SaveAs(excelFileName, Excel.XlFileFormat.xlExcel7);
            workBooks.Close();
            app.Quit();
        }

        private static void ToExcel(Excel.Application app, string csvFileName, string excelFileName)
        {
            var workBooks = app.Workbooks;

            workBooks.OpenText(csvFileName,
                               DataType: Excel.XlTextParsingType.xlDelimited,
                               TextQualifier: Excel.XlTextQualifier.xlTextQualifierNone,
                               ConsecutiveDelimiter: true,
                               Semicolon: true);

            workBooks[1].SaveAs(excelFileName, Excel.XlFileFormat.xlExcel7);
            workBooks.Close();
        }

        //string exportFilePath, string exportFileKey, string rawFilesDirectory, bool deleteRawFiles
        public static void ToExcel(string csvFileName1, string csvFileName2, string excelFileName)
        {
            Excel.Application xlApp = null;
            Excel.Workbooks newBooks = null;
            Excel.Workbook newBook = null;
            Excel.Sheets newBookWorksheets = null;
            Excel.Worksheet defaultWorksheet = null;

            Debug.WriteLine("Method: CombineWorkBooks - Starting excel &");

            xlApp = new Excel.Application();

            Debug.WriteLine("Method: CombineWorkBooks - Disabling the display alerts to prevent any prompts during workbooks close");
            xlApp.DisplayAlerts = false;

            Debug.WriteLine("Method: CombineWorkBooks - Set Visible to false as a background process, else it will be displayed in the task bar ");
            xlApp.Visible = false;

            Debug.WriteLine("Method: CombineWorkBooks - Create a new workbook, comes with an empty default worksheet");
            newBooks = xlApp.Workbooks;
            newBook = newBooks.Add(Excel.XlWBATemplate.xlWBATWorksheet);
            newBookWorksheets = newBook.Worksheets;

            // get the reference for the empty default worksheet
            if (newBookWorksheets.Count > 0)
            {
                defaultWorksheet = newBookWorksheets[1] as Excel.Worksheet;
            }

            Debug.WriteLine("Method: CombineWorkBooks - Get the files sorted by creation date");
            //var dirInfo = new DirectoryInfo(rawFilesDirectory);
            //filesToMerge = from f in dirInfo.GetFiles(exportFileKey + &quot; *&quot;, SearchOption.TopDirectoryOnly)
            //             orderby f.CreationTimeUtc
            //           select f.FullName;

            xlApp.Workbooks.OpenText(csvFileName1,
                               DataType: Excel.XlTextParsingType.xlDelimited,
                               TextQualifier: Excel.XlTextQualifier.xlTextQualifierNone,
                               ConsecutiveDelimiter: true,
                               Semicolon: true);

            xlApp.Workbooks.OpenText(csvFileName2,
                               DataType: Excel.XlTextParsingType.xlDelimited,
                               TextQualifier: Excel.XlTextQualifier.xlTextQualifierNone,
                               ConsecutiveDelimiter: true,
                               Semicolon: true);

            var workBookCSV1 = xlApp.Workbooks[1];
            var workBookCSV2 = xlApp.Workbooks[2];

            Excel.Workbook newbook = new Excel.Workbook();
            newbook.Worksheets.Delete();

            //workBooks[1].SaveAs(csvFileName1 + ".xls", Excel.XlFileFormat.xlExcel7);
            //workBooks[2].SaveAs(csvFileName2 + ".xls", Excel.XlFileFormat.xlExcel7);
            workBookCSV1.Close();
            workBookCSV2.Close();

            xlApp.Workbooks.Close();
            xlApp.Quit();
        }

        public static string Truncate(string source, int length)
        {
            if (source.Length > length)
            {
                source = source.Substring(0, length);
            }
            return source;
        }

        private static string GetReportDescription(string fileName, string defaultName)
        {
            var splits = fileName.Split('_');
            return splits.Length > 1 ? string.Join("-", splits, 1, splits.Length - 1) : defaultName;
        }

        private static void DisposeCOMObject(object o)
        {
            Console.WriteLine("Method: DisposeCOMObject - Disposing");
            if (o == null)
            {
                return;
            }
            try
            {
                System.Runtime.InteropServices.Marshal.ReleaseComObject(o);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Method: DisposeCOMObject - Exception: {0}", ex.ToString());
            }
        }

        private static void DeleteTemporaryFiles(IEnumerable<string> tempFilenames)
        {
            foreach (var tempFile in tempFilenames)
            {
                try
                {
                    File.Delete(tempFile);
                }
                catch
                    (Exception)
                {
                    Console.WriteLine("Could not delete temporary file '{0}'", tempFilenames);
                }
            }
        }

        public static bool CombineWorkBooks(string exportFilePath, string exportFileKey, string rawFilesDirectory, bool deleteRawFiles)
        {
            Excel.Application xlApp = null;
            Excel.Workbooks newBooks = null;
            Excel.Workbook newBook = null;
            Excel.Sheets newBookWorksheets = null;
            Excel.Worksheet defaultWorksheet = null;
            IEnumerable<string> filesToMerge = null;
            bool areRowsTruncated = false;

            try
            {
                Console.WriteLine("Method: CombineWorkBooks - Starting excel ");
                xlApp = new Excel.Application();

                if (xlApp == null)
                {
                    Console.WriteLine(" EXCEL could not be started.Check that your office installation and project references are correct.");
                    return false;
                }

                Console.WriteLine("Method: CombineWorkBooks - Disabling the display alerts to prevent any prompts during workbooks close");
                // not an elegant solution? however has to do this else will prompt for save on exit, even set the Saved property didn't help
                xlApp.DisplayAlerts = false;

                Console.WriteLine("Method: CombineWorkBooks - Set Visible to false as a background process, else it will be displayed in the task bar");
                xlApp.Visible = false;

                Console.WriteLine("Method: CombineWorkBooks - Create a new workbook, comes with an empty default worksheet ");
                newBooks = xlApp.Workbooks;
                newBook = newBooks.Add(Excel.XlWBATemplate.xlWBATWorksheet);
                newBookWorksheets = newBook.Worksheets;

                // get the reference for the empty default worksheet
                if (newBookWorksheets.Count > 0)
                {
                    defaultWorksheet = newBookWorksheets[1] as Excel.Worksheet;
                }

                Console.WriteLine("Method: CombineWorkBooks - Get the files sorted by creation date");
                var dirInfo = new DirectoryInfo(rawFilesDirectory);
                filesToMerge = from f in dirInfo.GetFiles(exportFileKey + "*", SearchOption.TopDirectoryOnly)
                               orderby f.CreationTimeUtc
                               select f.FullName;


                foreach (var filePath in filesToMerge)
                {
                    Excel.Workbook childBook = null;
                    Excel.Sheets childSheets = null;
                    try
                    {
                        Console.WriteLine("Method: CombineWorkBooks - Processing {0}", filePath);
                        childBook = newBooks.Open(filePath, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing
                                                         , Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing);

                        childSheets = childBook.Worksheets;
                        if (childSheets != null)
                        {
                            for (int iChildSheet = 1; iChildSheet <= childSheets.Count; iChildSheet++)
                            {
                                Excel.Worksheet sheetToCopy = null;
                                try
                                {
                                    sheetToCopy = childSheets[iChildSheet] as Excel.Worksheet;
                                    if (sheetToCopy != null)
                                    {
                                        Console.WriteLine("Method: CombineWorkBooks - Assigning the worksheet name");
                                        sheetToCopy.Name = Truncate(GetReportDescription(Path.GetFileNameWithoutExtension(filePath), sheetToCopy.Name), 31); // only 31 char max

                                        Console.WriteLine("Method: CombineWorkBooks - Copy the worksheet before the default sheet");
                                        sheetToCopy.Copy(defaultWorksheet, Type.Missing);
                                    }
                                }
                                finally
                                {
                                    DisposeCOMObject(sheetToCopy);
                                }
                            }


                            Console.WriteLine("Method: CombineWorkBooks - Close the childbook");
                            // for some reason, calling close below may cause an exception -&gt; System.Runtime.InteropServices.COMException (0x80010108): The object invoked has disconnected from its clients.
                            childBook.Close(false, Type.Missing, Type.Missing);
                        }
                    }
                    finally
                    {
                        DisposeCOMObject(childSheets);
                        DisposeCOMObject(childBook);
                    }

                }


                Console.WriteLine("Method: CombineWorkBooks - Delete the empty default worksheet");

                if (defaultWorksheet != null)
                {
                    defaultWorksheet.Delete();
                }

                Console.WriteLine("Method: CombineWorkBooks - Save the new book into the export file path: {0}", exportFilePath);
                newBook.SaveAs(exportFilePath, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing
                        , Excel.XlSaveAsAccessMode.xlExclusive, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing);

                newBooks.Close();
                xlApp.DisplayAlerts = true;

                return true;
            }

            catch (Exception ex)
            {
                Console.WriteLine("Method: CombineWorkBooks - Exception: {0}", ex.ToString());
                return false;
            }
            finally
            {
                DisposeCOMObject(defaultWorksheet);
                DisposeCOMObject(newBookWorksheets);
                DisposeCOMObject(newBooks);
                DisposeCOMObject(newBook);

                Console.WriteLine("Method: CombineWorkBooks - Closing the excel app");
                if (xlApp != null)
                {
                    xlApp.Quit();
                    DisposeCOMObject(xlApp);
                }

                if (deleteRawFiles)
                {
                    Console.WriteLine("Method: CombineWorkBooks - Deleting the temporary files");
                    DeleteTemporaryFiles(filesToMerge);
                }
            }
        }
    }

#if false
        public static void ToExcel(string csvFileName1, string csvFileName2, string excelFileName)
        {
            string tmpXlsxFileName1, tmpXlsxFileName2;
            var app = new Excel.Application();

            tmpXlsxFileName1 = Path.ChangeExtension(csvFileName1, ".xls");
            //ToExcel(app, csvFileName1, tmpXlsxFileName1);

            //tmpXlsxFileName2 = Path.ChangeExtension(csvFileName2, ".xls");
            //ToExcel(app, csvFileName2, tmpXlsxFileName2);

#if true
            var workBook1 = app.Workbooks.Open(tmpXlsxFileName1);

            Debug.WriteLine($"workBook1.Worksheets.Count={workBook1.Worksheets.Count}");

            //var workBook2 = app.Workbooks.Open(tmpXlsxFileName2);
            var mergeWorkBook = app.Workbooks.Add();
            var mergeWorkSheet = mergeWorkBook.Worksheets.get_Item(1) as Excel.Worksheet;
            
            Debug.WriteLine($"mergeWorkBook.Worksheets.Count={mergeWorkBook.Worksheets.Count}");

            //mergeWorkSheet.Copy(workBook1.Worksheets[1]);
            workBook1.Worksheets[1].Copy(mergeWorkSheet);

            //mergeWorkBook.Worksheets.Add(workBook1.Worksheets[1]);
            ////mergeWorkBook.Worksheets["Sheet2"].Copy(workBook2.Worksheets["Sheet1"]);
            mergeWorkBook.SaveAs(excelFileName);

            mergeWorkBook.Close();
            workBook1.Close();
            //workBook2.Close();
#endif

            app.Quit();

            //System.IO.File.Delete(tmpXlsxFileName1);
            //System.IO.File.Delete(tmpXlsxFileName2);
        }

#endif

#endif
}
    
