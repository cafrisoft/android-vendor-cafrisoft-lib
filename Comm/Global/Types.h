#ifndef COMM_GLOBAL_TYPES_H__
#define COMM_GLOBAL_TYPES_H__

typedef void* COMM_HANDLE;
typedef int Bool;
typedef void (*ThreadServiceFuncType)(void*);

#define True  1
#define False 0

#ifdef __cplusplus
#define PRINTF Comm::OAL::Log::Printf
#define CLOGI(...) Comm::OAL::Log::Info(CLOG_TAG, ##__VA_ARGS__)
#define CLOGD(...) Comm::OAL::Log::Debug(CLOG_TAG, __func__, __LINE__, ##__VA_ARGS__)
#define CLOGE(...) Comm::OAL::Log::Error(CLOG_TAG, __func__, __LINE__, ##__VA_ARGS__)


#else
#define PRINTF printf
#endif

//#define PRINTFDBG(fmt, ...) do { fprintf(stderr, "[DBG, %s] ln=%d " fmt, __func__, __LINE__, ##__VA_ARGS__);  fprintf(stderr, "\n"); } while(0)  
//#define CLOGE(fmt, ...) do { fprintf(stderr, "[ERR, %s] ln=%d " fmt, __func__, __LINE__, ##__VA_ARGS__);  fprintf(stderr, "\n"); } while(0)  


#ifdef __cplusplus
enum class VarType {
    Void = 0,
    Char,
    UnsignedChar,
    Short,
    UnsignedShort,
    Int,
    UnsignedInt,
    LongLong,
    UnsignedLongLong,
    Float,
    Double,
    String,
    MaxCnt
};
#endif

struct CommDateTime {
    int _Year;
    int _Month;
    int _Day;
    int _Hour;
    int _Minute;
    int _Second;
    int _MileSec;
};


#endif

