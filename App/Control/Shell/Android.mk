LOCAL_PATH := $(call my-dir)

##########################################################################################################
# RemotePython
##########################################################################################################
include $(CLEAR_VARS)
include $(LOCAL_PATH)/../../../AndroidBuildCommon.mk

LOCAL_SRC_FILES:= \
    CmdAndroid.cpp \
    CmdDatabase.cpp \
    CmdEmulator.cpp \
    CmdExport.cpp \
    CmdFileSync.cpp \
    CmdHub.cpp \
    CmdOALTest.cpp \
    CmdSocket.cpp \
    CmdStringTest.cpp \
    CmdSysTest.cpp   \
    CmdTED.cpp \
    CmdTester.cpp  \
    CmdVerify.cpp  \
    main.cpp 
           
  
#LOCAL_CFLAGS += -Wno-error=unused-parameter  -Wno-error=sign-compare
#LOCAL_CFLAGS += -DWITHOUT_IFADDRS -Wno-sign-compare

#LOCAL_C_INCLUDES += $(USIMOTA_TOP)/inc
LOCAL_CFLAGS += -Wno-error=date-time
  
LOCAL_SHARED_LIBRARIES :=    \
		libbinder            \
        libutils             \
        libcutils            \
        libnetutils            \
        libui                \
		libgui \
        libTESysComm libTESysTESys libTESysTED

LOCAL_MODULE:= TESysShell
include $(BUILD_EXECUTABLE)
