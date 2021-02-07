#include "Cmd.hpp"
#include <TESys/Data/Export/RawDB.hpp>
#include <TESys/Property/Path.hpp>
#include <Comm/Utils/TxtFile.hpp>
#include <TESys/Property/Tester.hpp>
#include <Comm/Utils/argparse.h>
#include <TESys/Data/Aging/PyCollection.hpp>
#include <TESys/TED/PowerSource.hpp>
#include <TESys/Data/DataAcqDBRaw.hpp>

namespace AppControlShell {
    namespace Cmd {


         bool Export::JobToCSV(int argc, const char** argv) {

             //std::vector<std::string> rawDBFileVector = {
               //  "D:\\Project_AgingSys\\DBRawData\\JOB_0002-tesys.dataacq.rawdata-2020-10-26",
                 //"D:\\Project_AgingSys\\DBRawData\\JOB_0002-tesys.dataacq.rawdata-2020-10-27"
             //};


             std::string configPathFileName = TESys::Property::Path::ControlShell::GetConfigRoot();
             configPathFileName += Comm::Property::Path::GetFilePathDelimChar();
             configPathFileName += "Export_JobToCSV_RawDBFileVector.txt";

             std::vector<std::string> rawDBFileVector = Comm::Utils::TxtFile::ReadLineString(configPathFileName);
             for (std::vector<std::string>::const_iterator it = rawDBFileVector.cbegin();
                 it != rawDBFileVector.cend();
                 it++) {

                 PRINTF("RawDBFile: %s \n", (*it).c_str());
             }

#if 1
             TESys::Data::Export::RawDB::JobToCSV(rawDBFileVector, 5 /*jobID*/);

#else
             int boardID = 30;
             int dutIdx = 0;
             TESys::Data::Export::RawDB::JobToCSV(rawDBFileVector, boardID, dutIdx, 2 /*jobID*/);

#endif
             
             return true;
         }

         bool Export::TcToCSV(int argc, const char** argv) {

             int boardID;
             int dutIdx;
             int tcID;
                          
             printf("<<Convert TC to CSV>>\n");
             
             if (argc == 1) {
                 boardID = TESys::Property::Tester::Board::GetGeneralID();
                 dutIdx = TESys::Property::Tester::Board::GetGeneralDutIdx();
                 tcID = atoi(argv[0]);
             }
             else if (argc == 2) {
                 boardID = atoi(argv[0]);
                 dutIdx = TESys::Property::Tester::Board::GetGeneralDutIdx();
                 tcID = atoi(argv[1]);
             }
             else if (argc == 3) {
                 boardID = atoi(argv[0]);
                 dutIdx = atoi(argv[1]);
                 tcID = atoi(argv[2]);
             }
             else {
                 printf("ERROR : argument error \n");
                 printf("\t USAGE1) #export tc2csv [BoardID] [DutIdx] [TcID] \n");
                 printf("\t USAGE1) #export tc2csv [BoardID] [TcID]  //DutIdx=ALL \n");
                 printf("\t USAGE2) #export tc2csv [TcID]  //Boarkd=ALL, DutIdx=All \n");
                 return false;
             }

             if (boardID == TESys::Property::Tester::Board::GetGeneralID()) {
                 printf("BoardID=%d (General ID) \n", boardID);
             }
             else {
                 printf("BoardID=%d \n", boardID);
             }

             if (dutIdx == TESys::Property::Tester::Board::GetGeneralDutIdx()) {
                 printf("DutIdx=%d (General ID) \n", dutIdx);
             }
             else {
                 printf("DutIdx=%d \n", dutIdx);
             }

             printf("TcID=%d \n", tcID);


             std::string configPathFileName = TESys::Property::Path::ControlShell::GetConfigRoot();
             configPathFileName += Comm::Property::Path::GetFilePathDelimChar();
             configPathFileName += "Export_TcToCSV_RawDBFileVector.txt";

             std::vector<std::string> rawDBFileVector = Comm::Utils::TxtFile::ReadLineString(configPathFileName);
             for (std::vector<std::string>::const_iterator it = rawDBFileVector.cbegin();
                 it != rawDBFileVector.cend();
                 it++) {

                 PRINTF("RawDBFile: %s \n", (*it).c_str());
             }

             if (rawDBFileVector.size() > 0) {
                 //TESys::Data::Export::RawDB::JobToCSV(rawDBFileVector, 2 /*tcID*/);
             }
             else {
                 PRINTF("ERROR : Cannot find RawDBFile, check %s \n", configPathFileName.c_str());
             }

             return true;
         }

         bool Export::CSVMerge(int argc, const char** argv) {

             //#define DATA_ROOT_PATH "C:\\MyTESys\\opt\\TESys\\DataAcq\\ExportCSV\\JobToCsv\\JOB_0003-201031_210524"
             //#define MERGED_FILE_PATH_FILE_NAME "C:\\MyTESys\\opt\\TESys\\DataAcq\\ExportCSV\\JobToCsv\\JOB_0003-201031_210524\\merged.csv"
             
             #define DATA_ROOT_PATH "/home/hthwang/TESysRawData/ExportCSV/JobToCsv/JOB_0005"
             #define MERGED_FILE_PATH_FILE_NAME "/home/hthwang/TESysRawData/ExportCSV/JobToCsv/JOB_0005/merged.csv"

             int boardID;
             int fcnt;
             int lineCountPerFile = 0;
             int lineCountTotoal = 0;
             char* lineData = new char[8196];
             assert(lineData);
             char* columnHdr = new char[8196];
             assert(columnHdr);

             //Read Column Hdr
             fcnt = 0;
             for (boardID = TESys::Property::Tester::Board::GetMinID();
                 boardID <= TESys::Property::Tester::Board::GetMaxID();
                 boardID++) {

                 bool isSearchOk = false;
                 std::string strFileName;
                 std::string strFileNameSearchName;
                 
                 if (isSearchOk == false) {
                     strFileNameSearchName = Comm::Utils::StringFormat("%s/201104_202334-JOB_0005-B%04d-Dut0.csv", DATA_ROOT_PATH, boardID);
                     if (Comm::OAL::FileSys::IsThisFileExist(strFileNameSearchName)) {
                         isSearchOk = true;
                         strFileName = strFileNameSearchName;
                     }
                 }

                 if (isSearchOk == false) {
                     strFileNameSearchName = Comm::Utils::StringFormat("%s/201104_202335-JOB_0005-B%04d-Dut0.csv", DATA_ROOT_PATH, boardID);
                     if (Comm::OAL::FileSys::IsThisFileExist(strFileNameSearchName)) {
                         isSearchOk = true;
                         strFileName = strFileNameSearchName;
                     }
                 }

                 if (isSearchOk == false) {
                     strFileNameSearchName = Comm::Utils::StringFormat("%s/201104_202334-JOB_0005-B%04d-Dut0.csv", DATA_ROOT_PATH, boardID);
                     if (Comm::OAL::FileSys::IsThisFileExist(strFileNameSearchName)) {
                         isSearchOk = true;
                         strFileName = strFileNameSearchName;
                     }
                 }

                 
                 if (isSearchOk) {
                     PRINTF("%d. %s \n", fcnt + 1, strFileName.c_str());

                     FILE* fp = fopen(strFileName.c_str(), "r");

                     char* p = fgets(lineData, 8196, fp);
                     Comm::Utils::StringTool::RemoveCharInStringFromBack(p);
                     PRINTF("%s \n", p);

                     strcpy(columnHdr, p);

                     fclose(fp);

                     fcnt++;
                     break;
                 }
             }

             //Merged File Open
             FILE* fp_merged = fopen(MERGED_FILE_PATH_FILE_NAME, "w");
             assert(fp_merged);

             fprintf(fp_merged, "%s\n", columnHdr);


             //Read Data And Merge
             fcnt = 0;
             lineCountTotoal = 0;
             for (boardID = TESys::Property::Tester::Board::GetMinID();
                 boardID <= TESys::Property::Tester::Board::GetMaxID();
                 boardID++) {


                 bool isSearchOk = false;
                 std::string strFileName;
                 std::string strFileNameSearchName;

                 if (isSearchOk == false) {
                     strFileNameSearchName = Comm::Utils::StringFormat("%s/201104_202334-JOB_0005-B%04d-Dut0.csv", DATA_ROOT_PATH, boardID);
                     if (Comm::OAL::FileSys::IsThisFileExist(strFileNameSearchName)) {
                         isSearchOk = true;
                         strFileName = strFileNameSearchName;
                     }
                 }

                 if (isSearchOk == false) {
                     strFileNameSearchName = Comm::Utils::StringFormat("%s/201104_202335-JOB_0005-B%04d-Dut0.csv", DATA_ROOT_PATH, boardID);
                     if (Comm::OAL::FileSys::IsThisFileExist(strFileNameSearchName)) {
                         isSearchOk = true;
                         strFileName = strFileNameSearchName;
                     }
                 }

                 if (isSearchOk==false) {
                     strFileNameSearchName = Comm::Utils::StringFormat("%s/201104_202334-JOB_0005-B%04d-Dut0.csv", DATA_ROOT_PATH, boardID);
                     if (Comm::OAL::FileSys::IsThisFileExist(strFileNameSearchName)) {
                         isSearchOk = true;
                         strFileName = strFileNameSearchName;
                     }
                 }


                 //std::string strFileName = Comm::Utils::StringFormat("%s\\201031_210524-JOB_0003-B%04d-Dut0.csv", DATA_ROOT_PATH, boardID);
                 //std::string strFileName = Comm::Utils::StringFormat("%s/201103_213631-JOB_0004-B%04d-Dut0.csv", DATA_ROOT_PATH, boardID);
                 if (isSearchOk) {
                     PRINTF("%d. %s \n", fcnt + 1, strFileName.c_str());

                     FILE* fp = fopen(strFileName.c_str(), "r");

                     //Read Column
                     char* p = fgets(lineData, 8196, fp);
                     Comm::Utils::StringTool::RemoveCharInStringFromBack(p);

                     //Read Data
                     lineCountPerFile = 0;
                     while (true) {
                         char* p = fgets(lineData, 8196, fp);
                         if (p == NULL) {
                             break;
                         }
                         Comm::Utils::StringTool::RemoveCharInStringFromBack(p);
                         fprintf(fp_merged, "%s\n", lineData);
                         lineCountPerFile++;
                         lineCountTotoal++;
                     }

                     fclose(fp);

                     fcnt++;
                 }
             }


             fclose(fp_merged);
             delete[] lineData;
             delete[] columnHdr;

             PRINTF("FileCnt=%d   lineCountPerFile=(%d %d) lineCountTotoal=%d  \n", fcnt, lineCountPerFile, lineCountTotoal/fcnt, lineCountTotoal);

             return true;
         }

         bool Export::StatisticsData(int argc, const char** argv) {
      
             int jobID;
             //int scID;

             if (argc == 1) {
                 jobID = atoi(argv[0]);
             }
             else {
                 printf("ERROR : argument error \n");
                 printf("\t ex1) #export st [JobID]  \n");
                 return false;
             }
             printf("JobID=%d \n", jobID);
             

             std::string configPathFileName = TESys::Property::Path::ControlShell::GetConfigRoot();
             configPathFileName += Comm::Property::Path::GetFilePathDelimChar();
             configPathFileName += "Export_RawDBFileVector.txt";


             std::vector<std::string> rawDBFileVector = Comm::Utils::TxtFile::ReadLineString(configPathFileName);
             for (std::vector<std::string>::const_iterator it = rawDBFileVector.cbegin();
                 it != rawDBFileVector.cend();
                 it++) {
                 PRINTF("RawDBFile: %s \n", (*it).c_str());
             }

#if 1
             const int boardID = 10;
             const int dutIdx = 0;
             std::shared_ptr<TESys::Data::Aging::PyCollection> pyColl = std::make_shared<TESys::Data::Aging::PyCollection>();

             PRINTF("RawData Loading Begin \n");
#if 0 //(CommOS==CommOS_WIN)
             pyColl->LoadRawData(rawDBFileVector, boardID, dutIdx, jobID);
#else
             pyColl->LoadRawData(rawDBFileVector, jobID);
#endif
             PRINTF("RawData Loading End\n");

             pyColl->PrintStatus();

#if 0
             int scID = 1;
             int tcID = 1;
             int tcStepID = 5;
             int psID = (int)TESys::TED::PowerSource::External::Vlin1;
             bool isVolt = true;
             pyColl->PrintValue(jobID, scID, tcID, tcStepID, psID, isVolt);
#endif

             PRINTF("Export CSV Begin\n");
             pyColl->ExportCSV();
             PRINTF("Export CSV End\n");
             
             PRINTF("tatisticsData Begin \n");
             pyColl->MakeStatisticsData();
             PRINTF("tatisticsData End \n");
             //pyAvg->SetID(300, 0);
             //pyAvg->PrintStatus();
             //pyAvg->ExportCSV("/home/hthwang/TESysRawData/ExportCSV/Statistics");

#endif

             return true;
         }


         bool Export::ScToCSV(int argc, const char** argv) {
         
             int jobID;
             int scID;

             if (argc == 2) {
                 jobID = atoi(argv[0]);
                 scID = atoi(argv[1]);
             }
             else {
                 printf("ERROR : argument error \n");
                 printf("\t ex1) #export sc2csv [JobID] [ScID]   \n");
                 return false;
             }

             printf("JobID=%d \n", jobID);
             printf("ScID=%d \n", scID);

             std::string configPathFileName = TESys::Property::Path::ControlShell::GetConfigRoot();
             configPathFileName += Comm::Property::Path::GetFilePathDelimChar();
             configPathFileName += "Export_JobToCSV_RawDBFileVector.txt";

             std::vector<std::string> rawDBFileVector = Comm::Utils::TxtFile::ReadLineString(configPathFileName);
             for (std::vector<std::string>::const_iterator it = rawDBFileVector.cbegin();
                 it != rawDBFileVector.cend();
                 it++) {
                 PRINTF("RawDBFile: %s \n", (*it).c_str());
             }

             std::shared_ptr<TESys::Data::Aging::PyCollection> pyColl = std::make_shared<TESys::Data::Aging::PyCollection>();
             pyColl->LoadRawData(rawDBFileVector, jobID);
             pyColl->ExportScToCSV(scID);

             return true;
         }

         bool Export::RawDataToOneCSVFile(int argc, const char** argv) {

             int jobID;
             
             if (argc == 1) {
                 jobID = atoi(argv[0]);
             }
             else {
                 printf("ERROR : argument error \n");
                 printf("\t ex1) #export raw2csv [JobID]  \n");
                 return false;
             }

             printf("JobID=%d \n", jobID);
             
             std::string configPathFileName = TESys::Property::Path::ControlShell::GetConfigRoot();
             configPathFileName += Comm::Property::Path::GetFilePathDelimChar();
             configPathFileName += "Export_RawDBFileVector.txt";

             std::vector<std::string> rawDBFileVector = Comm::Utils::TxtFile::ReadLineString(configPathFileName);
             for (std::vector<std::string>::const_iterator it = rawDBFileVector.cbegin();
                 it != rawDBFileVector.cend();
                 it++) {
                 PRINTF("RawDBFile: %s \n", (*it).c_str());
             }

             std::shared_ptr<TESys::Data::Aging::PyCollection> pyColl = std::make_shared<TESys::Data::Aging::PyCollection>();
             
             PRINTF("--------------------------------------------------------------------\n");
             PRINTF("[pyColl->LoadRawDataRawDBFile] Begin \n");
             pyColl->LoadRawData(rawDBFileVector, jobID);
             PRINTF("[pyColl->LoadRawDataRawDBFile] End \n");
             PRINTF("--------------------------------------------------------------------\n\n");

             PRINTF("--------------------------------------------------------------------\n");
             PRINTF("[pyColl->ExportRawDataToOneCSVFile] Begin \n");
             pyColl->ExportRawDataToOneCSVFile(jobID);
             PRINTF("[pyColl->ExportRawDataToOneCSVFile] End \n");
             PRINTF("--------------------------------------------------------------------\n\n");

             return true;
         }

         bool Export::Analysis_Job_Sc_Tc(int argc, const char** argv) {
         
             const int jobID = 9;
             const int scID = 1;
             const int tcID = 2;
             //int scID;

             printf("JobID=%d \n", jobID);
             printf("ScID=%d \n", scID);
             printf("TcID=%d \n", tcID);


             std::string configPathFileName = TESys::Property::Path::ControlShell::GetConfigRoot();
             configPathFileName += Comm::Property::Path::GetFilePathDelimChar();
             configPathFileName += "Export_RawDBFileVector.txt";

             std::vector<std::string> rawDBFileVector = Comm::Utils::TxtFile::ReadLineString(configPathFileName);
             for (std::vector<std::string>::const_iterator it = rawDBFileVector.cbegin();
                 it != rawDBFileVector.cend();
                 it++) {
                 PRINTF("RawDBFile: %s \n", (*it).c_str());
             }

             std::shared_ptr<TESys::Data::Aging::PyCollection> pyColl = std::make_shared<TESys::Data::Aging::PyCollection>();
             pyColl->LoadRawData_Job_Sc_Tc(rawDBFileVector, jobID, scID, tcID);

             pyColl->PrintStatus();
             pyColl->ExportCSV();

             PRINTF("tatisticsData Begin \n");
             pyColl->MakeStatisticsData();
             PRINTF("tatisticsData End \n");

             return true;
         }

         bool Export::Analysis_Job_Sc(int argc, const char** argv) {

             /* Set Config */
             const int jobID = 24;
             const int scID = 3;

#if (CommOS==CommOS_WIN)
             std::vector<std::string> rawDBFileVector = {
                  "d:\\work\\JOB_0024-tesys.dataacq.rawdata-2021-01-03",

             };

#else
             std::vector<std::string> rawDBFileVector = {
                 "/opt/TESys/DataAcq/BackupRawData/JOB_0013-tesys.dataacq.rawdata-2020-11-19",
                 "/opt/TESys/DataAcq/BackupRawData/JOB_0013-tesys.dataacq.rawdata-2020-11-20",
                 "/opt/TESys/DataAcq/BackupRawData/JOB_0013-tesys.dataacq.rawdata-2020-11-21",
                 "/opt/TESys/DataAcq/BackupRawData/JOB_0013-tesys.dataacq.rawdata-2020-11-22",
             };
#endif


             /* Print Config */
             printf("JobID=%d \n", jobID);
             printf("ScID=%d \n", scID);
             for (std::vector<std::string>::const_iterator it = rawDBFileVector.cbegin();
                 it != rawDBFileVector.cend();
                 it++) {
                 PRINTF("RawDBFile: %s \n", (*it).c_str());
             }

             std::shared_ptr<TESys::Data::Aging::PyCollection> pyColl = std::make_shared<TESys::Data::Aging::PyCollection>();
             pyColl->LoadRawData_Job_Sc(rawDBFileVector, jobID, scID);
             pyColl->PrintStatus();
             pyColl->ExportCSV();
             PRINTF("tatisticsData Begin \n");
             pyColl->MakeStatisticsData();
             PRINTF("tatisticsData End \n");

             return true;
         }


         bool Export::EmulAgingWithRawData(int argc, const char** argv) {
             
             long long totalFileByteSize = 0;
             long long readFileByteSize = 0;
             long long beforeReadFileByteSize = 0;

             std::vector<std::string> rawDBFileVector = {
                 "/home/hthwang/TESysRawData/RawData/JOB_0024-tesys.dataacq.rawdata-2020-12-28",
                 //"/home/hthwang/TESysRawData/RawData/JOB_0024-tesys.dataacq.rawdata-2020-12-29",
                 //"/home/hthwang/TESysRawData/RawData/JOB_0024-tesys.dataacq.rawdata-2020-12-30",
                 //"/home/hthwang/TESysRawData/RawData/JOB_0024-tesys.dataacq.rawdata-2021-01-01",
                 //"/home/hthwang/TESysRawData/RawData/JOB_0024-tesys.dataacq.rawdata-2021-01-02",
                 "/home/hthwang/TESysRawData/RawData/JOB_0024-tesys.dataacq.rawdata-2021-01-03",
             };

             /* Print Config */
             for (std::vector<std::string>::const_iterator it = rawDBFileVector.cbegin();
                 it != rawDBFileVector.cend();
                 it++) {

                 long long fileByteSize;
                 std::string strRawDBFileName = (*it);
                 
                 FILE* fp = fopen(strRawDBFileName.c_str(), "rb");
                 assert(fp);

                 STDC_FSEEK64(fp, 0, SEEK_END);
                 fileByteSize = STDC_FTELL64(fp);
                 
                 totalFileByteSize += fileByteSize;

                 fclose(fp);

                 PRINTF("RawDBFile: %s  FileSize: %lld  TotalByte: %lld \n", (*it).c_str(), fileByteSize , totalFileByteSize);
             }

             std::shared_ptr<TESys::Data::Aging::PyCollection> pyColl = std::make_shared<TESys::Data::Aging::PyCollection>();
             
             PRINTF("\n\n");

             unsigned char* recordBuf = new unsigned char[TESys::Data::DataAcqDBRaw::GetRecrodBufFixedByteSize()];
             assert(recordBuf);
             
             for (std::vector<std::string>::const_iterator it = rawDBFileVector.cbegin();
                 it != rawDBFileVector.cend();
                 it++) {

                 long long fileByteSize;
                 long long beforeFilePos;
                 std::string strRawDBFileName = (*it);
                 FILE* fp = fopen(strRawDBFileName.c_str(), "rb");
                 assert(fp);

                 STDC_FSEEK64(fp, 0, SEEK_END);
                 fileByteSize = STDC_FTELL64(fp);
                 beforeFilePos = STDC_FSEEK64(fp, 0, SEEK_SET);

                 while (true) {

                     long long filePos0, filePos1;

                     filePos0 = STDC_FTELL64(fp);

                     if (TESys::Data::DataAcqDBRaw::ReadRecord(fp, recordBuf) == true) {
                         
                         std::shared_ptr<TESys::Net::PacketDataAcq> rcvPack = TESys::Data::DataAcqDBRaw::ConvertRawRecordDataToPacketDataAcq(recordBuf);

                         if (rcvPack->GetScID() == 2) {
                            /*nothing to do */
                         }
                         else {
                             pyColl->LoadPacket(rcvPack, true /*isDbgExport*/);
                         }
                         
                     }
                     else {
                         break;
                     }

                     filePos1 = STDC_FTELL64(fp);
                     readFileByteSize += (filePos1 - filePos0);

                     if ((readFileByteSize - beforeReadFileByteSize) > 1024 * 1024) {

                         beforeReadFileByteSize = readFileByteSize;
                         PRINTF("\rProcessing %lld/%lld  %lld%c", readFileByteSize, totalFileByteSize, (readFileByteSize * 100LL) / totalFileByteSize, '%');
                     }
                 }

                 fclose(fp);
             }

             delete[] recordBuf;

             PRINTF("\n\n");

             return true;
         }

    };
};


