#ifndef COMM_GLOBAL_OS_WIN_H__
#define COMM_GLOBAL_OS_WIN_H__

#include <Comm/Global/OS/Common.h>

/*
주의 :  WinSock2 include는 windows.h 앞에 있어야 한다.
https://stackoverflow.com/questions/1372480/c-redefinition-header-files-winsock2-h

This problem is caused when including <windows.h> before <winsock2.h>. Try arrange your include list that <windows.h> is included after <winsock2.h> or define _WINSOCKAPI_ first:
#define _WINSOCKAPI_    // stops windows.h including winsock.h
#include <windows.h>
// ...
#include "MyClass.h"    // Which includes <winsock2.h>
*/

#include <direct.h>
#include <winsock2.h>
#include <Windows.h>
#include <tchar.h>
#include <ws2tcpip.h>
#include <time.h>

#ifdef __cplusplus
#ifdef COMM_EXPORTS
#define COMM_API extern "C"  __declspec(dllexport)
#else
#define COMM_API extern "C"  __declspec(dllimport)
#endif

#else
#ifdef COMM_EXPORTS
#define COMM_API __declspec(dllexport)
#else
#define COMM_API __declspec(dllimport)
#endif
#endif

#define STDC_FSEEK64  _fseeki64
#define STDC_FTELL64  _ftelli64

#endif

