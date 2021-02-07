#ifndef COMM_NETUTILS_FTPDEFINE_H__
#define COMM_NETUTILS_FTPDEFINE_H__

// FTP로 파일 수신시, 진행상황 체크하기 위한 Callback
typedef int (*Comm_NetUtils_FtpGetCallback)(void* arg, long long readByteSize);  //add by hthwang 2020-0813

#endif

