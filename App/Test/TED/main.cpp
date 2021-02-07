#include <TED/Api.h>

int main(int argc, char* argv[]) {
    
    int dutIdx = TedSysGetDutIndexAllDeviceValue();
    TedAgingMeasureADC(dutIdx, NULL);

    return 0;
}