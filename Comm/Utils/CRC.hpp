#ifndef COMM_UTILS_CRC_HPP__
#define COMM_UTILS_CRC_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/OAL/FileSys.hpp>

typedef void (*Comm_Utils_CRC16_File_Callback)(void* arg, 
                                          std::shared_ptr<Comm::OAL::FileSys::File> file,
                                          int crc,   // 현재 CRC값 
                                          long long checkDoneByteSize, //현재 CRC값을 계산하는데 사용한 byte
                                          long long checkDoneFileByteSize //현재 파일에서 체크 완료한 File ByteSize
                                       );

namespace Comm {
    namespace Utils {

        int CRC16(char* addr, int num, int crc);
        int CRC16(std::shared_ptr<Comm::OAL::FileSys::File> file, 
                  int crc,
                  unsigned char* crcUserBuf=NULL, int crcBufMaxByteSize = -1, 
                  void* cbArg=NULL, Comm_Utils_CRC16_File_Callback cbFunc=NULL);

        unsigned short CheckSum16Bit(char* addr, int num, unsigned short initValue);
    };
};

#endif
