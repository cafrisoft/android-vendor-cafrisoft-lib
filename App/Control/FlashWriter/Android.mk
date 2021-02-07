LOCAL_PATH := $(call my-dir)

##########################################################################################################
# TESysFlashWriter
##########################################################################################################
include $(CLEAR_VARS)
include $(LOCAL_PATH)/../../../AndroidBuildCommon.mk

LOCAL_SRC_FILES:= \
    main.cpp 
  
LOCAL_CFLAGS += -Wno-error=date-time
  
LOCAL_SHARED_LIBRARIES :=    \
		libbinder            \
        libutils             \
        libcutils            \
        libnetutils            \
        libui                \
		libgui \
        libTESysComm libTESysTESys libTESysTED

LOCAL_MODULE:= TESysFlashWriter
include $(BUILD_EXECUTABLE)
