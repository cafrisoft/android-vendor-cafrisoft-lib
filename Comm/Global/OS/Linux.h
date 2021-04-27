#ifndef My_GLOBAL_OS_LINUX_H__
#define My_GLOBAL_OS_LINUX_H__

#include <Comm/Global/OS/Common.h>

#include <inttypes.h>
#include <time.h>
#include <signal.h>
#include <strings.h>
#include <unistd.h>
#include <pthread.h>
#include <syslog.h>
#include <semaphore.h>
#include <fcntl.h>
#include <termios.h>
#include <stdarg.h>
#include <dirent.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <limits.h>

#ifdef __cplusplus
#define COMM_API extern "C" 

#else
#define COMM_API extern
#endif

#define C_FSEEK64  fseeko
#define C_FTELL64  ftello
#define C_ABS64  llabs
#define C_STRDUP strdup
#define C_GETPID getpid

#endif

