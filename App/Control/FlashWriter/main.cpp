#define CLOG_TAG "TESysFlashWriter"
#include <TESys/Global/BuildOptions.h>
#include <Comm/Utils/StringTool.hpp>
#include <TED/Api.h>
#include <Comm/OAL/Log.hpp>
#include <Comm/OAL/Thread.hpp>
#include <TESys/Property/Tester.hpp>


#define FLASH_BINARY_FILENAME "/data/TESysData/firmware/avl8895-ted-flash.vec.bin"
#define FLASH_ERASE_COMMAND "flash_erase /dev/mtd/mtd0 0x00 1936"
#define FLASH_WRITE_COMMAND "dd if=/data/TESysData/firmware/avl8895-ted-flash.vec.bin of=/dev/mtd/mtd0 bs=512 count=1936"

#if (CommOS==CommOS_WIN) 

#define FLASH_ERASE_COMMAND_FILE "C:\\Temp\\TESys\\FlashWriteEmul\\Flash_Erase_Command_File.txt"
#define FLASH_WRITE_COMMAND_FILE "C:\\Temp\\TESys\\FlashWriteEmul\\Flash_Write_Command_File.txt"

static FILE* popen(const char* cmd, const char* mode) {

    FILE* fp;
    const char* emulTxtFileName="";

    if (strcmp(cmd, FLASH_ERASE_COMMAND) == 0) {
        FILE* fpw = fopen(FLASH_ERASE_COMMAND_FILE, "w");
        assert(fpw);
        fprintf(fpw, "Erase Total 1936 Units\n");
        fprintf(fpw, "Performing Flash Erase of length 4096 at offset 0x78f000 done\n");
        fclose(fpw);
        emulTxtFileName = FLASH_ERASE_COMMAND_FILE;
    }
    else if (strcmp(cmd, FLASH_WRITE_COMMAND) == 0) {
        
        FILE* fpw = fopen(FLASH_WRITE_COMMAND_FILE, "w");
        assert(fpw);
        fprintf(fpw, "1936+0 records in\n");
        fprintf(fpw, "1936 + 0 records out\n");
        fprintf(fpw, "991232 bytes transferred in 3.955 secs(250627 bytes/sec)\n");
        fclose(fpw);
        emulTxtFileName = FLASH_WRITE_COMMAND_FILE;
    }
    else {
        assert(0);
    }

    fp = fopen(emulTxtFileName, "r");
    assert(fp);

    return fp;
}

static void pclose(FILE* fp) {
    fclose(fp);
}

#endif

static void TED_FB_Blank_Off(int dutIdx) {

    CLOGI("TED_FB_Blank_Off, Delay 1sec");
    TedDD_FB_blank(dutIdx, 0 /* blank off*/);
    TedSysDelayMS(1000);
}

/*
    avl8895: / # flash_erase /dev/mtd/mtd0 0x00 1936
    Erase Total 1936 Units
    Performing Flash Erase of length 4096 at offset 0x78f000 done
*/
static void Flash_Erase() {
    
    FILE* fp;

    CLOGI("Flash Erase");

    fp = popen(FLASH_ERASE_COMMAND, "r");
    if (fp) {
        char buf[512];
        
        while (true) {
            char* p = fgets(buf, 512, fp);
            if (p == NULL) {
                break;
            }
            Comm::Utils::StringTool::RemoveCharInStringFromBack(p);
            CLOGI("%s", p);
        }
        pclose(fp);
    }

}

/*
    avl8895:/data/TESysData/firmware # dd if=ip06_flash00_0923_orig.vec.bin of=/dev/mtd/mtd0 bs=512 count=1936
    1936+0 records in
    1936+0 records out
    991232 bytes transferred in 3.955 secs (250627 bytes/sec)
*/
static void Flash_Binary_Write() {

    FILE* fp;
    CLOGI("Flash Binary Write");

    fp = popen(FLASH_WRITE_COMMAND, "r");
    if (fp) {
        char buf[512];

        while (true) {
            char* p = fgets(buf, 512, fp);
            if (p == NULL) {
                break;
            }
            Comm::Utils::StringTool::RemoveCharInStringFromBack(p);
            CLOGI("%s", p);
        }
        pclose(fp);
    }

}

/*
    # echo "0x39 0xc0 0x00 0x00 0x00 0x00 0x51" > / sys / devices / platform / 12870000.dsim / mipi2_rw
    # echo "0x39 0xc0 0x0f 0x00 0x00 0xff 0x01" > / sys / devices / platform / 12870000.dsim / mipi2_rw
    # echo "0x06 0xc1 0xff" > / sys / devices / platform / 12870000.dsim / mipi2_rw
    # cat / sys / devices / platform / 12870000.dsim / mipi2_rw
     0x34 0x07 0xFF 0x07 0xFF 0x07 0xFF 0x67 0x08 0x01 0x00 0x30 0x20 0x49 0x00 0x29 
     0x06 0x40 0xC8 0x12 0xC1 0x90 0x1F 0x42 0x58 0x2B 0xC3 0x20 0x38 0x43 0xE8 0x44 
     0xC4 0xB0 0x51 0x45 0x78 0x5D 0xC6 0x40 0x6A 0x47 0x08 0x76 0xC7 0xD0 0x83 0x48 
     0x98 0x8F 0xC9 0x60 0x9C 0x4A 0x28 0xA8 0xCA 0xF0 0xB5 0x4B 0xB8 0xC1 0xCC 0x80 
     0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 
     0x00

*/
static bool Flash_Verify(int dutIdx) {
    
    //Write Status Flag
    unsigned char cmdData1[5] = { 0x00, 0x00, 0x00, 0x00, 0x51 };
    TedDD_DSIM_MipiWriteReg15(dutIdx, 0xB0, 0x00);
    TedDD_DSIM_MipiWriteReg15(dutIdx, 0xC1 /*SPI Data*/, 0xFC);         //0xFC가 읽을 수 있게 하는 Flag인 것 같다. 
    TedDD_DSIM_MipiWriteReg39(dutIdx, 0xC0 /*regAddr*/, 5, cmdData1);   //Status Flag를 쓴다. 
    Comm::OAL::Thread::Sleep(100);

    //Send Read Command 
    const int DATA2_COUNT = 5;
    unsigned char cmdData2[DATA2_COUNT] = { 0x0f, 0x00, 0x00, 0xff, 0x01 };
    TedDD_DSIM_MipiWriteReg15(dutIdx, 0xB0, 0x00);
    TedDD_DSIM_MipiWriteReg39(dutIdx, 0xC0 /*regAddr*/, 5, cmdData2);
    Comm::OAL::Thread::Sleep(100);

    const int VERIFY_DATA_COUNT = 0xFF;
    unsigned char spibuf[VERIFY_DATA_COUNT];
    memset(spibuf, 0x0A, VERIFY_DATA_COUNT);
    TedDD_DSIM_MipiReadReg(dutIdx, 0xC1 /*regAddr*/, 0 /*byteOffset*/, VERIFY_DATA_COUNT /*readCnt*/, spibuf, VERIFY_DATA_COUNT /*maxByteSize*/);

    unsigned char filebuf[VERIFY_DATA_COUNT];
    memset(filebuf, 0x01, VERIFY_DATA_COUNT);
    FILE* fp = fopen(FLASH_BINARY_FILENAME, "rb");
    if (fp) {
        fseek(fp, 0x0F0000, SEEK_SET);
        fread(filebuf, 1, VERIFY_DATA_COUNT, fp);
        fclose(fp);
    }

    bool isVerifyOK;

    for (int i = 0; i < 32; i++) {

        PRINTF("%d. 0x%02X 0x%02X \n", i, (int)filebuf[i] & 0xFF, (int)spibuf[i] & 0xFF);

        if (filebuf[i] == spibuf[i]) {
            isVerifyOK = true;
        }
        else {
            isVerifyOK = false;
            break;
        }
    }

    return isVerifyOK;
}

int main(int argc, char* argv[]) {

    bool isVerifyOnly = false;
    int dutIdx = 0;
    int boardID = TESys::Property::Tester::Board::GetInvalidID();

    int dutCnt = TedSysGetDutCount();
    if (dutCnt > 1) {
        dutIdx = TedSysGetDutIndexAllDeviceValue();
    }
    else {
        dutIdx = 0;
    }

    boardID = TESys::Property::Tester::Board::GetID();
    if (argc == 2) {
        if (strcmp(argv[1], "verify") == 0) {
            isVerifyOnly = true;
        }
    }
    

    if (boardID < 0) {
        PRINTF("ERROR: boardID is not defined!! \n");
        return -1;
    }

    PRINTF("BoardID=%d  isVerifyOnly=%d\n", boardID, isVerifyOnly);

    Comm::OAL::Log::SysLogOpen(CLOG_TAG);
    Comm::OAL::Log::EnableOutDevice(Comm::OAL::Log::OutDevice::Console);
    Comm::OAL::Log::EnableDebug();

    if (Comm::OAL::FileSys::IsThisFileExist(FLASH_BINARY_FILENAME) != true) {
        TESys::Property::Tester::ErrorClass::SetFlashWriterError(boardID, TESys::Property::Tester::ErrorClass::FlashWriter::BinaryFileNotExist);
        CLOGI("Cannot find TED-Flash-Binary-FIle (%s)", FLASH_BINARY_FILENAME);
        return -1;
    }

    TESys::Property::Tester::ErrorClass::SetFlashWriterError(boardID, TESys::Property::Tester::ErrorClass::FlashWriter::FlashWriterStart);

    //TED Blank Off
    TED_FB_Blank_Off(dutIdx);

    if (isVerifyOnly == false) {
        //Flash Erase
        Flash_Erase();

        //Flash BInary Write
        Flash_Binary_Write();
    }

    //Flash Verify
    if (Flash_Verify(dutIdx) == true) {
        TESys::Property::Tester::ErrorClass::SetFlashWriterError(boardID, TESys::Property::Tester::ErrorClass::FlashWriter::Success);
        CLOGI("Spi Flash Write Verify OK");
    }
    else {
        TESys::Property::Tester::ErrorClass::SetFlashWriterError(boardID, TESys::Property::Tester::ErrorClass::FlashWriter::VerifyFail);
        CLOGI("Spi Flash Write Verify FAIL");
    }

    Comm::OAL::Log::SysLogClose();
    CLOGI("Bye Bye~~");

    return 0;
}

