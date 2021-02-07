using System;
using Comm = libComm.AutoGen;

namespace AppTEDAgingExport
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");

#if false
            string csvFileName1 = "d:\\work\\Export\\201022_181750-TC_0001.py-B0044-Dut0.csv";
            string csvFileName2 = "d:\\work\\Export\\201022_181750-TC_0001.py-B0046-Dut0.csv";
            string excelFileName = "d:\\work\\Export\\export.xlsx";

            TESys.Export.CSV.ToExcel(csvFileName1, csvFileName2,  excelFileName);
#endif

            string exportFilePath= @"D:\Work\ABCDE\Export";
            string exportFileKey ="";
            string rawFilesDirectory= @"D:\Work\ABCDE";
            bool deleteRawFiles = false;

            Comm.Utils.ExcelTool.CombineWorkBooks(exportFilePath, exportFileKey, rawFilesDirectory, deleteRawFiles);

            //liComm.UTESys.Export.ExcelTool.CombineWorkBooks(exportFilePath, exportFileKey, rawFilesDirectory, deleteRawFiles);

        }
    }
}
