#ifndef COMM_GLOBAL_OS_ANDROID_H__
#define COMM_GLOBAL_OS_ANDROID_H__

#include <Comm/Global/OS/Common.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <signal.h>
#include <pthread.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <termios.h>
#include <stdarg.h>
#include <dirent.h>
#include <time.h>
#include <semaphore.h>

#ifdef __cplusplus
#define COMM_API extern "C" 

#else
#define COMM_API extern
#endif

#define STDC_FSEEK64  fseeko
#define STDC_FTELL64  ftello

#if (ANDROID_PLATFORM_SDK_VERSION == 28)
#define ANDROID_MAJOR_VERSION 9
#else
#define ANDROID_MAJOR_VERSION 0
#endif


#endif

