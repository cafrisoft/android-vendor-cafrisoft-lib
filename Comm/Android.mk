LOCAL_PATH:= $(call my-dir)

##########################################################################################################
# Comm Shared Lib
##########################################################################################################
include $(CLEAR_VARS)

BASE_SRC = \
    Base/Object.cpp

DATAEX_SRC = \
    DataEx/Consumer.cpp \
    DataEx/Producer.cpp \
    DataEx/Exchanger.cpp 

OAL_SRC = \
    OAL/Cond.cpp  OAL/CondLinux.cpp \
    OAL/CriticalSection.cpp  OAL/CriticalSectionLinux.cpp \
    OAL/DateTimeComm.cpp \
    OAL/FileSysComm.cpp OAL/FileSysLinux.cpp \
    OAL/Lock.cpp \
    OAL/Log.cpp OAL/LogAndroid.cpp \
    OAL/Mutex.cpp OAL/MutexLinux.cpp \
    OAL/ProcessMutex.cpp OAL/ProcessMutexLinux.cpp \
    OAL/Semaphore.cpp  OAL/SemaphoreLinux.cpp \
    OAL/SyncObject.cpp \
    OAL/SystemComm.cpp OAL/SystemLinux.cpp \
    OAL/Thread.cpp OAL/ThreadLinux.cpp \
    OAL/ThreadService.cpp \
    OAL/Timer.cpp OAL/TimerComm.cpp \
    

SOCKET_TCP_SRC = \
    Socket/TCP/TCPClient.cpp  \
    Socket/TCP/TCPClientLinux.cpp  \
    Socket/TCP/TCPServer.cpp  \
    Socket/TCP/TCPServerLinux.cpp  


SOCKET_UDP_SRC = \
    Socket/UDP/UDPClient.cpp  \
    Socket/UDP/UDPClientLinux.cpp  \
    Socket/UDP/UDPServer.cpp  \
    Socket/UDP/UDPServerLinux.cpp  


NET_PACKET_SRC = \
    Socket/NetPacket.cpp Socket/NetPacketFixed.cpp

UTILS_SRC= \
    Utils/Android.cpp \
    Utils/AndroidScreenCap.cpp \
    Utils/Counter.cpp \
    Utils/CRC.cpp \
    Utils/IntegerCount.cpp  \
    Utils/Property.cpp  \
    Utils/StringTool.cpp \
    Utils/TxtFile.cpp

NETUTILS_SRC= \
    NetUtils/FTPClient.cpp  NetUtils/FTPClient_libftp.cpp

OPENSRC_SRC= \
    OpenSource/ftplib-4.0-1/src/ftplib_libcomm_opensrc.c

SHELL_SRC= \
    Shell/CmdItem.cpp Shell/CmdSet.cpp Shell/MainShell.cpp

PROPERTY_SRC= \
    Property/Path_Comm_Property.cpp \
    Property/System_Comm_Property.cpp
    
LOCAL_SRC_FILES:= \
    $(BASE_SRC) $(DATAEX_SRC) $(OAL_SRC) $(SOCKET_TCP_SRC) $(SOCKET_UDP_SRC) $(NET_PACKET_SRC) $(UTILS_SRC) $(NETUTILS_SRC) $(OPENSRC_SRC) $(SHELL_SRC) $(PROPERTY_SRC)
    
#LOCAL_C_INCLUDES:= \
#      $(TESYS_INC_TOP)

COMM_INC_TOP := $(LOCAL_PATH)/..
LOCAL_C_INCLUDES:= $(COMM_INC_TOP)
LOCAL_CFLAGS += -DANDROID
LOCAL_CFLAGS += -DANDROID_PLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)

LOCAL_SHARED_LIBRARIES := \
        libbinder            \
        libutils             \
        libcutils            \
        libnetutils          \
        libui               \
        libgui \
        liblog
        
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= libCafriComm
include $(BUILD_SHARED_LIBRARY)
