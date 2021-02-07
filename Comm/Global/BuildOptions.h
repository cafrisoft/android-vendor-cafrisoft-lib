#ifndef COMM_GLOBAL_BUILDOPTIONS_H__
#define COMM_GLOBAL_BUILDOPTIONS_H__

/*
   OS Define
*/
#define CommOS_WIN     1
#define CommOS_LINUX   2
#define CommOS_ANDROID 3

#if defined ANDROID
#define CommOS CommOS_ANDROID
#elif defined _WIN64
#define CommOS CommOS_WIN
#elif defined WIN32
#define CommOS CommOS_WIN
#elif defined ANDROID
#define CommOS CommOS_ANDROID
#elif defined LINUX
#define CommOS CommOS_LINUX
#else
#error "OS Type is not defined"
#endif

#if (CommOS==CommOS_WIN)
#include <Comm/Global/OS/Win.h>
#elif (CommOS==CommOS_ANDROID)
#include <Comm/Global/OS/Android.h>
#elif (CommOS==CommOS_LINUX)
#include <Comm/Global/OS/Linux.h>
#else
#error "CommOS is not defined"
#endif

/*
   Type Define
*/
#include <Comm/Global/Types.h>

#ifdef __cplusplus
#include <Comm/Global/TemplateList.hpp>
#endif

/*
ASSERT Definitin
*/
#define ASSERT_CHECK_TIME_T_64BIT assert(sizeof(time_t) == sizeof(long long))


/*
Class SingleTon Pattern Define
*/
#ifdef __cplusplus

#define CLASS_SINGLETON_PATTERN_DECLARE(cls) \
    private:  \
        static std::shared_ptr<cls> _Instance; \
    public:  \
        static void Init(); \
        static void Deinit(); \
        static std::shared_ptr<cls> Inst(); 


#define CLASS_SINGLETON_PATTERN_IMPLEMENT(cls) \
    std::shared_ptr<cls> cls::_Instance; \
    \
    void cls::Init() { \
        cls::_Instance = std::make_shared<cls>(); \
        assert(cls::_Instance); \
    } \
    \
    void cls::Deinit() { \
        assert(cls::_Instance); \
        cls::_Instance.reset(); \
    } \
    \
    std::shared_ptr<cls> cls::Inst() { \
        assert(cls::_Instance); \
        return cls::_Instance; \
    } 

#define CLASS_SINGLETON_PATTERN_DECLARE_C1(cls) \
    private:  \
        static std::shared_ptr<cls> _Instance; \
    public:  \
        static std::shared_ptr<cls> Inst(); 


#define CLASS_SINGLETON_PATTERN_IMPLEMENT_C1(cls) \
    std::shared_ptr<cls> cls::_Instance; \
    \
    std::shared_ptr<cls> cls::Inst() { \
        if(cls::_Instance==NULL) cls::_Instance = std::make_shared<cls>(); \
        assert(cls::_Instance); \
        return cls::_Instance; \
    } 

#endif


/*
    Fourcc, BytAlign, Swap
*/
#define COMM_MAKE_FOURCC(ch0, ch1, ch2, ch3)                           \
                ((unsigned int)(unsigned char)(ch0) | ((unsigned int)(unsigned char)(ch1) << 8) |   \
                ((unsigned int)(unsigned char)(ch2) << 16) | ((unsigned int)(unsigned char)(ch3) << 24 ))

#define COMM_GET_FOURCC(fourcc,ch) (unsigned char)(fourcc>>(8*ch))
#define COMM_GET_FOURCCARG(fourcc)  COMM_GET_FOURCC(fourcc,0),COMM_GET_FOURCC(fourcc,1),COMM_GET_FOURCC(fourcc,2),COMM_GET_FOURCC(fourcc,3)
#define COMM_BYTE_ALIGN(x, align)   (((x) + (align) - 1) & ~((align) - 1))
#define COMM_BYTE_ALIGN_16B(x)   ((((x) + (1 <<  4) - 1) >>  4) <<  4)
#define COMM_BYTE_ALIGN_32B(x)   ((((x) + (1 <<  5) - 1) >>  5) <<  5)
#define COMM_BYTE_ALIGN_128B(x)  ((((x) + (1 <<  7) - 1) >>  7) <<  7)
#define COMM_BYTE_ALIGN_8KB(x)   ((((x) + (1 << 13) - 1) >> 13) << 13)

#define COMM_MAX(a,b) ((a) > (b) ? (a) : (b))
#define COMM_MIN(a,b) ((a) > (b) ? (b) : (a))
#define COMM_MAX3(a,b,c) COMM_MAX(COMM_MAX(a,b),c)
#define COMM_MIN3(a,b,c) COMM_MIN(COMM_MIN(a,b),c)

#define COMM_SWAP_I16(v) (short)((((v)>>8)  & 0xff) | (((v)&0xff) << 8))
#define COMM_SWAP_I32(v) (int)((((v)>>24) & 0xff) | (((v)>>8) & 0xff00) | (((v)&0xff00) << 8) | (((v)&0xff) << 24))
#define COMM_SWAP_U16(v) (unsigned short)((((v)>>8)  & 0xff) | (((v)&0xff) << 8))
#define COMM_SWAP_U32(v) (unsigned int)((((v)>>24) & 0xff) | (((v)>>8) & 0xff00) | (((v)&0xff00) << 8) | (((v)&0xff) << 24))

#define COMM_PUT_BYTE(_p, _b) \
    *_p++ = (unsigned char)_b; 

#define COMM_PUT_BUFFER(_p, _buf, _len) \
    memcpy(_p, _buf, _len); \
    _p += _len;

#define COMM_PUT_LE32(_p, _var) \
    *_p++ = (unsigned char)((_var)>>0);  \
    *_p++ = (unsigned char)((_var)>>8);  \
    *_p++ = (unsigned char)((_var)>>16); \
    *_p++ = (unsigned char)((_var)>>24); 

#define COMM_PUT_BE32(_p, _var) \
    *_p++ = (unsigned char)((_var)>>24);  \
    *_p++ = (unsigned char)((_var)>>16);  \
    *_p++ = (unsigned char)((_var)>>8); \
    *_p++ = (unsigned char)((_var)>>0); 


#define COMM_PUT_LE16(_p, _var) \
    *_p++ = (unsigned char)((_var)>>0);  \
    *_p++ = (unsigned char)((_var)>>8);  


#define COMM_PUT_BE16(_p, _var) \
    *_p++ = (unsigned char)((_var)>>8);  \
    *_p++ = (unsigned char)((_var)>>0);  


#define COMM_RB32(x)                                 \
    (((unsigned int)((const unsigned char*)(x))[0] << 24) |     \
               (((const unsigned char*)(x))[1] << 16) |    \
               (((const unsigned char*)(x))[2] <<  8) |    \
                ((const unsigned char*)(x))[3])


#define COMM_MKTAG(a,b,c,d) ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))
#define COMM_MKBETAG(a,b,c,d) ((d) | ((c) << 8) | ((b) << 16) | ((unsigned)(a) << 24))



#endif

