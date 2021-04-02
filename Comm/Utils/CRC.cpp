#include <Comm/Global/BuildOptions.h>
#include <Comm/Utils/CRC.hpp>

namespace Comm {
    namespace Utils {

        
        /* On entry, addr=>start of data
                     num = length of data
                     crc = incoming CRC     */
        int CRC16(char* addr, int num, int crc)
        {
            int i;
            const int poly = 0x1021;

            for (; num > 0; num--)               /* Step through bytes in memory */
            {
                crc = crc ^ (*addr++ << 8);      /* Fetch byte from memory, XOR into CRC top byte*/
                for (i = 0; i < 8; i++)              /* Prepare to rotate 8 bits */
                {
                    crc = crc << 1;                /* rotate */
                    if (crc & 0x10000)             /* bit 15 was set (now bit 16)... */
                        crc = (crc ^ poly) & 0xFFFF; /* XOR with XMODEM polynomic */
                                                     /* and ensure CRC remains 16-bit value */
                }                              /* Loop for 8 bits */
            }                                /* Loop until num=0 */
            return(crc) & 0xFFFF;                     /* Return updated CRC */
        }

        int CRC16(std::shared_ptr<Comm::OAL::FileSys::File> file,
                  int crc,
                  unsigned char* crcUserBuf, int crcBufMaxByteSize,
                  void* cbArg, Comm_Utils_CRC16_File_Callback cbFunc) {
        
            char* crcWorkBuf;
            
            if (crcUserBuf == NULL) {
                const int bufByteSize = 1024 * 256;// 1024 * 10;
                crcWorkBuf = new char[bufByteSize];
                crcBufMaxByteSize = bufByteSize;
            }
            else {
                crcWorkBuf = (char*)crcUserBuf;
            }
            assert(crcWorkBuf);

            int offset = 0;
            long long fileByteSize = file->GetByteSize();
            memcpy(&crcWorkBuf[offset], file->GetName().c_str(), file->GetName().size()); offset += (int)file->GetName().size();
            memcpy(&crcWorkBuf[offset], &fileByteSize, sizeof(fileByteSize)); offset += sizeof(fileByteSize);
            crc = Comm::Utils::CRC16(crcWorkBuf, offset, crc);

            long long checkDoneFileByteSize = 0;
            FILE* fp = fopen(file->GetPathFileName().c_str(), "rb");
            if (fp) {

                while (true) {
                    size_t rdsz = fread(crcWorkBuf, 1, crcBufMaxByteSize, fp);
                    assert(sizeof(size_t) == sizeof(long long));
                    if (rdsz == 0) {
                        break;
                    }
                    crc = Comm::Utils::CRC16(crcWorkBuf, (int)rdsz, crc);
                    checkDoneFileByteSize += rdsz;

                    if (cbFunc) {
                        (*cbFunc)(cbArg, file, crc, rdsz, checkDoneFileByteSize);
                    }
                }

            }

            if (crcUserBuf == NULL) {
                delete[] crcWorkBuf;
            }

            return crc;
        }


        /* On entry, addr=>start of data
                     num = length of data
                     crc = incoming CRC     */
        unsigned short CheckSum16Bit(char* addr, int num, unsigned short initValue)
        {
            unsigned short chksum = initValue;
            unsigned short* sdata = (unsigned short*)addr;
            int dcnt = num / 2;


            assert((num % 2) == 0); // num은 2byte 배수여야 한다. 

            for (int i = 0; i < dcnt; i++)               /* Step through bytes in memory */
            {
                chksum += *sdata;
                sdata++;
            }                                /* Loop until num=0 */
            return chksum;
        }

    };
};
