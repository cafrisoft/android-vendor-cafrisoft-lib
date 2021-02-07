#define CLOG_TAG "TestString"
#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/HeaderFiles.hpp>
#include <Comm/Utils/HeaderFiles.hpp>

using namespace Comm;


void TestString() {

    int valueArr[10] = { 1, 2,3,4,5,6,7,8,9,10 };
    char szBuf[1024];

    Utils::StringTool::ConvertIntArrayToHexString(valueArr, 10, ',', 4, szBuf);
    CLOGD("%s", szBuf);

    Utils::StringTool::ConvertIntArrayToDecimalString(valueArr, 10, ',', szBuf);
    CLOGD("%s", szBuf);
}