cmake_minimum_required(VERSION 3.8)
project("test-system-app")

#set(GCC_PATH /usr/local/etc/gcc/gcc-7.2.0)
#set(CMAKE_C_COMPILER ${GCC_PATH}/bin/gcc)
#set(CMAKE_CXX_COMPILER ${GCC_PATH}/bin/g++)

set(PATH_RELEASE .)
set(PATH_ROOT ../..)
set(PATH_PYTHON_INCLUDE  /opt/TESys/android-emul/system/etc/python/include/python3.8)

set(PATH_RELEASE release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release/bin)


set(LIBNAME_COMM TESysComm)
set(LIBNAME_TESYS TESysTESys)
set(LIBNAME_TED TED)
set(LIBNAME_DATABASE TESysDatabase)

set(APP_SERVER_PATTERNDRAW TESysPatternDraw)
set(APP_SERVER_DATAACQ TESysDataAcq)
set(APP_CONTROLHUB TESysHub)
set(APP_CONTROL_TESTER TESysTester)
set(APP_CONTROL_OPERATOR TESysOperator)
set(APP_CONTROL_SHELL TESysShell)
set(APP_FILESYNC TESysFileSync)
set(APP_HUBCALCRC TESysHubCalCRC)
set(APP_DATABASE_RAWDATA TESysDBRawData)
set(APP_DATABASE_MYSQL   TESysDBMySQL)
set(APP_DATABASE_VerifyRAWDATA TESysDBVerifyRawData)
set(PYTHON_MODULE_TED PythonModuleTED)

include_directories(${PATH_ROOT} ${PATH_PYTHON_INCLUDE})
ADD_DEFINITIONS(-DLINUX)
add_compile_options(-std=c++11)
#link_directories(/usr/local/etc/gcc/gcc-7.2.0/lib64)

################################################################################################################################
#
#  libComm
#
################################################################################################################################

# Setting PATH 
set(PATH_COMM ${PATH_ROOT}/Comm)
set(PATH_COMM_API ${PATH_COMM}/API)
set(PATH_COMM_BASE ${PATH_COMM}/Base)
set(PATH_COMM_DATAEX ${PATH_COMM}/DataEx)
set(PATH_COMM_NETUTILS ${PATH_COMM}/NetUtils)
set(PATH_COMM_OAL ${PATH_COMM}/OAL)
set(PATH_COMM_OPENSOURCE_FTP ${PATH_COMM}/OpenSource/ftplib-4.0-1/src)
set(PATH_COMM_PROPERTY ${PATH_COMM}/Property)
set(PATH_COMM_SHELL ${PATH_COMM}/Shell)
set(PATH_COMM_SOCKET ${PATH_COMM}/Socket)
set(PATH_COMM_SOCKET_TCP ${PATH_COMM_SOCKET}/TCP)
set(PATH_COMM_SOCKET_UDP ${PATH_COMM_SOCKET}/UDP)
set(PATH_COMM_UTILS ${PATH_COMM}/Utils)

# Comm/Base
set(SRC_COMM_BASE ${PATH_COMM_BASE}/Object.cpp)

#Comm/DataEx
set(SRC_COMM_DATAEX
${PATH_COMM_DATAEX}/Consumer.cpp
${PATH_COMM_DATAEX}/Producer.cpp
${PATH_COMM_DATAEX}/Exchanger.cpp
)

#Comm/NetUtils
set(SRC_COMM_NETUTILS
${PATH_COMM_NETUTILS}/FTPClient.cpp
${PATH_COMM_NETUTILS}/FTPClient_libftp.cpp
${PATH_COMM_OPENSOURCE_FTP}/ftplib_libcomm_opensrc.c
)

# Comm/Property
set(SRC_COMM_PROPERTY
${PATH_COMM_PROPERTY}/Path_Comm_Property.cpp
${PATH_COMM_PROPERTY}/System_Comm_Property.cpp
)

# Comm/OAL
set(SRC_COMM_OAL 
${PATH_COMM_OAL}/Cond_Comm_OAL.cpp   ${PATH_COMM_OAL}/CondLinux.cpp  
${PATH_COMM_OAL}/CriticalSection.cpp   ${PATH_COMM_OAL}/CriticalSectionLinux.cpp  
${PATH_COMM_OAL}/DateTimeComm.cpp
${PATH_COMM_OAL}/FileSysComm.cpp ${PATH_COMM_OAL}/FileSysLinux.cpp  
${PATH_COMM_OAL}/Lock.cpp 
${PATH_COMM_OAL}/Log.cpp  ${PATH_COMM_OAL}/LogLinux.cpp    
${PATH_COMM_OAL}/Mutex_Comm_OAL.cpp   ${PATH_COMM_OAL}/MutexLinux.cpp  
${PATH_COMM_OAL}/ProcessMutex_Comm_OAL.cpp   ${PATH_COMM_OAL}/ProcessMutexLinux.cpp  
${PATH_COMM_OAL}/Semaphore.cpp   ${PATH_COMM_OAL}/SemaphoreLinux.cpp  
${PATH_COMM_OAL}/SyncObject.cpp   
${PATH_COMM_OAL}/SystemComm.cpp ${PATH_COMM_OAL}/SystemLinux.cpp  
${PATH_COMM_OAL}/Thread.cpp   ${PATH_COMM_OAL}/ThreadLinux.cpp  ${PATH_COMM_OAL}/ThreadService.cpp
${PATH_COMM_OAL}/Timer.cpp ${PATH_COMM_OAL}/TimerComm.cpp
)

# Comm/Shell
set(SRC_COMM_SHELL
${PATH_COMM_SHELL}/CmdItem.cpp
${PATH_COMM_SHELL}/CmdSet.cpp
${PATH_COMM_SHELL}/MainShell.cpp
)

# Comm/Socket 
set(SRC_COMM_SOCKET_TCP 
${PATH_COMM_SOCKET_TCP}/TCPClient.cpp  ${PATH_COMM_SOCKET_TCP}/TCPClientLinux.cpp  
${PATH_COMM_SOCKET_TCP}/TCPClientWin.cpp  ${PATH_COMM_SOCKET_TCP}/TCPServer.cpp  
${PATH_COMM_SOCKET_TCP}/TCPServerLinux.cpp  ${PATH_COMM_SOCKET_TCP}/TCPServerWin.cpp )

set(SRC_COMM_SOCKET_UDP 
${PATH_COMM_SOCKET_UDP}/UDPClient.cpp  ${PATH_COMM_SOCKET_UDP}/UDPClientLinux.cpp  
${PATH_COMM_SOCKET_UDP}/UDPClientWin.cpp  ${PATH_COMM_SOCKET_UDP}/UDPServer.cpp  
${PATH_COMM_SOCKET_UDP}/UDPServerLinux.cpp  ${PATH_COMM_SOCKET_UDP}/UDPServerWin.cpp )

set(SRC_COMM_SOCKET
${PATH_COMM_SOCKET}/NetPacket.cpp  ${PATH_COMM_SOCKET}/NetPacketFixed.cpp
${SRC_COMM_SOCKET_TCP} 
${SRC_COMM_SOCKET_UDP})

 #Comm/Utils
set(SRC_COMM_UTILS
${PATH_COMM_UTILS}/Android_Comm_Utils.cpp
${PATH_COMM_UTILS}/AndroidScreenCap.cpp
${PATH_COMM_UTILS}/argparse.c
${PATH_COMM_UTILS}/Counter_Comm_Utils.cpp
${PATH_COMM_UTILS}/CRC.cpp
${PATH_COMM_UTILS}/IntegerCount.cpp
${PATH_COMM_UTILS}/Property_Comm_Utils.cpp
${PATH_COMM_UTILS}/StringTool.cpp
${PATH_COMM_UTILS}/TxtFile_Comm_Utils.cpp
)

# Setting All Source Files 
set(SRC_COMM 
${SRC_COMM_BASE}
${SRC_COMM_DATAEX}
${SRC_COMM_NETUTILS}
${SRC_COMM_OAL} 
${SRC_COMM_PROPERTY}
${SRC_COMM_SHELL}
${SRC_COMM_SOCKET}
${SRC_COMM_UTILS}
) 

add_library(${LIBNAME_COMM} SHARED ${SRC_COMM})

################################################################################################################################
#
#  libTESysDatabase
#
################################################################################################################################

# Setting PATH 
set(PATH_DATABASE_ROOT ${PATH_ROOT}/Database)
set(PATH_DATABASE_CLASS ${PATH_DATABASE_ROOT}/Class)
set(PATH_DATABASE_RDBMS ${PATH_DATABASE_ROOT}/RDBMS)

 #Database
set(SRC_DATABASE_ROOT
${PATH_DATABASE_ROOT}/VarType_Database.cpp
)

#Database/Class
set(SRC_DATABASE_CLASS
${PATH_DATABASE_CLASS}/Column_Database_Class.cpp
${PATH_DATABASE_CLASS}/Data_Database_Class.cpp
${PATH_DATABASE_CLASS}/Header_Database_Class.cpp
${PATH_DATABASE_CLASS}/Record_Database_Class.cpp
${PATH_DATABASE_CLASS}/Table_Database_Class.cpp
)

#Database/RDBMS
set(SRC_DATABASE_RDBMS
${PATH_DATABASE_RDBMS}/Base_Database_RDBMS.cpp
${PATH_DATABASE_RDBMS}/MySQL_Database_RDBMS.cpp
)

# Setting All Source Files 
set(SRC_DATABASE
${SRC_DATABASE_ROOT}
${SRC_DATABASE_CLASS}
${SRC_DATABASE_RDBMS}
) 

add_library(${LIBNAME_DATABASE} SHARED ${SRC_DATABASE})
target_link_libraries(${LIBNAME_DATABASE} PUBLIC ${LIBNAME_COMM} mysqlcppconn)

################################################################################################################################
#
#  libTESys
#
################################################################################################################################

# Setting PATH 
set(PATH_TESYS ${PATH_ROOT}/TESys)

set(PATH_TESYS_CONTROL ${PATH_TESYS}/Control)
set(PATH_TESYS_DATA ${PATH_TESYS}/Data)
set(PATH_TESYS_DB ${PATH_TESYS}/DB)
set(PATH_TESYS_NET ${PATH_TESYS}/Net)
set(PATH_TESYS_PROPERTY ${PATH_TESYS}/Property)
set(PATH_TESYS_TED ${PATH_TESYS}/TED)
set(PATH_TESYS_UTILS ${PATH_TESYS}/Utils)

# TESys/Control
set(SRC_TESYS_CONTROL
${PATH_TESYS_CONTROL}/Operator_Extern.cpp
${PATH_TESYS_CONTROL}/Operator_TESys_Control.cpp
${PATH_TESYS_CONTROL}/OperatorAgingMonitor.cpp
${PATH_TESYS_CONTROL}/OperatorCommander.cpp
${PATH_TESYS_CONTROL}/OperatorCommanderExtern.cpp
${PATH_TESYS_CONTROL}/OperatorDataAcqReceiver.cpp
${PATH_TESYS_CONTROL}/OperatorDataConsumerDataAcq.cpp
${PATH_TESYS_CONTROL}/OperatorDataConsumerHubStatus.cpp
${PATH_TESYS_CONTROL}/OperatorDataConsumerTesterStatus.cpp
${PATH_TESYS_CONTROL}/OperatorDataProducerDataAcq.cpp
${PATH_TESYS_CONTROL}/OperatorDataProducerHubStatus.cpp
${PATH_TESYS_CONTROL}/OperatorDataProducerTesterStatus.cpp
${PATH_TESYS_CONTROL}/OperatorFileSync.cpp
${PATH_TESYS_CONTROL}/OperatorNotifyReceiver.cpp
${PATH_TESYS_CONTROL}/OperatorNotifyReceiverCmdProc.cpp
${PATH_TESYS_CONTROL}/OperatorNotifyReceiverExtern.cpp
${PATH_TESYS_CONTROL}/OperatorNotifyReceiverService.cpp
${PATH_TESYS_CONTROL}/OperatorTesterDictionary.cpp
${PATH_TESYS_CONTROL}/OperatorTesterMonitor.cpp
${PATH_TESYS_CONTROL}/Tester_TESys_Control.cpp
${PATH_TESYS_CONTROL}/TesterCommandReceiver.cpp
${PATH_TESYS_CONTROL}/TesterCommandReceiverCmdProc.cpp
${PATH_TESYS_CONTROL}/TesterNotifier.cpp
${PATH_TESYS_CONTROL}/TesterNotifierCmdProc.cpp
${PATH_TESYS_CONTROL}/TesterNotifierExtern.cpp
${PATH_TESYS_CONTROL}/TesterStatusReporter.cpp
${PATH_TESYS_CONTROL}/TesterTransaction_TH_HT.cpp
${PATH_TESYS_CONTROL}/AgingMonitor_Export.cpp
${PATH_TESYS_CONTROL}/AgingMonitor_TESys_Control.cpp
)

# TESys/Data
set(SRC_TESYS_DATA
${PATH_TESYS_DATA}/Adc_TESys_Data.cpp
${PATH_TESYS_DATA}/DataAcqDB_Export.cpp
${PATH_TESYS_DATA}/DataAcqDB_ExportData.cpp
${PATH_TESYS_DATA}/DataAcqDB_TESys_Data.cpp
${PATH_TESYS_DATA}/DataAcqDBRaw_TESys_Data.cpp
${PATH_TESYS_DATA}/DataAcqDBRawExport.cpp
${PATH_TESYS_DATA}/DataAcqDBRawQuery.cpp
${PATH_TESYS_DATA}/DataAcqDBRawVerify.cpp
${PATH_TESYS_DATA}/Status_TESys_Data.cpp
${PATH_TESYS_DATA}/TesterError_TESys_Data.cpp
${PATH_TESYS_DATA}/Export/RawDB_TESys_Data_Export.cpp
${PATH_TESYS_DATA}/Export/TED_TESys_Data_Export.cpp
${PATH_TESYS_DATA}/Export/TEDCollection_TESys_Data_Export.cpp
${PATH_TESYS_DATA}/Aging/Job_TESys_Data_Aging.cpp
${PATH_TESYS_DATA}/Aging/Py_TESys_Data_Aging.cpp
${PATH_TESYS_DATA}/Aging/PyCollection_TESys_Data_Aging.cpp
${PATH_TESYS_DATA}/Aging/Sc_TESys_Data_Aging.cpp
${PATH_TESYS_DATA}/Aging/Tc_TESys_Data_Aging.cpp
${PATH_TESYS_DATA}/Aging/TcStep_TESys_Data_Aging.cpp
${PATH_TESYS_DATA}/Aging/TcStepExportCSV.cpp
)

# TESys/Data
set(SRC_TESYS_DB
${PATH_TESYS_DB}/Table/AdcBase_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/AdcErr_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/AdcExtA_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/AdcExtV_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/AdcLdoV_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/AdcProp_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/AdcRegV_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/AdcSoutV_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/Cpu_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/DutPcb_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/Hardware_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/Job_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/JobList_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/Sc_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/ScList_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/SocPcb_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/Software_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/Tc_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/TcList_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/TcStep_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/TcStepList_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/Ted_TESys_DB_Table.cpp
${PATH_TESYS_DB}/Table/TedList_TESys_DB_Table.cpp
)

# TESys/Net
set(SRC_TESYS_NET 
${PATH_TESYS_NET}/Command.cpp
${PATH_TESYS_NET}/PacketDataAcq.cpp
${PATH_TESYS_NET}/PacketControl.cpp
${PATH_TESYS_NET}/PacketPython.cpp
)

# TESys/Property
set(SRC_TESYS_PROPERTY
${PATH_TESYS_PROPERTY}/DataAcq_TESys_Property.cpp
${PATH_TESYS_PROPERTY}/FileSync_TESys_Property.cpp
${PATH_TESYS_PROPERTY}/FileSyncFtp.cpp
${PATH_TESYS_PROPERTY}/FileSyncStatus.cpp
${PATH_TESYS_PROPERTY}/Hub_TESys_Property.cpp
${PATH_TESYS_PROPERTY}/HubFtpServer.cpp
${PATH_TESYS_PROPERTY}/Net_TESys_Property.cpp
${PATH_TESYS_PROPERTY}/Path_DeviceDriver.cpp
${PATH_TESYS_PROPERTY}/Path_TESys_Property.cpp
${PATH_TESYS_PROPERTY}/PathControlShell.cpp
${PATH_TESYS_PROPERTY}/PathDataAcq.cpp
${PATH_TESYS_PROPERTY}/PatternDraw_TESys_Property.cpp
${PATH_TESYS_PROPERTY}/TED_TESys_Property.cpp
${PATH_TESYS_PROPERTY}/TesterPropertyAgingComm.cpp
${PATH_TESYS_PROPERTY}/TesterPropertyBoardComm.cpp
${PATH_TESYS_PROPERTY}/TesterPropertyComm.cpp
${PATH_TESYS_PROPERTY}/TesterPropertyErrorClass.cpp
${PATH_TESYS_PROPERTY}/TesterPropertyStatusClass.cpp
)

# TESys/TED
set(SRC_TESYS_TED
${PATH_TESYS_TED}/ANA670X_TESys_TED.cpp
${PATH_TESYS_TED}/ANA6707_TESys_TED.cpp
${PATH_TESYS_TED}/Aging_TESys_TED.cpp
${PATH_TESYS_TED}/DeviceDriver_TESys_TED.cpp
${PATH_TESYS_TED}/PowerSource_TESys_TED.cpp
${PATH_TESYS_TED}/VerifyBoard_TESys_TED.cpp
${PATH_TESYS_TED}/VerifyBoard_v2_1.cpp
${PATH_TESYS_TED}/VerifyBoard_v2_1_ADC.cpp
${PATH_TESYS_TED}/VerifyBoard_v2_1_Aging.cpp
${PATH_TESYS_TED}/VerifyBoard_v2_1_ANA670X.cpp
${PATH_TESYS_TED}/VerifyBoard_v2_1_Display.cpp
${PATH_TESYS_TED}/VerifyBoard_v2_1_DriverPathADC.cpp
${PATH_TESYS_TED}/VerifyBoard_v2_1_DriverPathDisplay.cpp
${PATH_TESYS_TED}/VerifyBoard_v2_1_LED.cpp
${PATH_TESYS_TED}/ADC/Ina3221.cpp
${PATH_TESYS_TED}/ADC/Max113xx.cpp
${PATH_TESYS_TED}/ADC/Max11301.cpp
${PATH_TESYS_TED}/ADC/Max11312.cpp
${PATH_TESYS_TED}/DD/DSIM_TESys_TED_Display.cpp
${PATH_TESYS_TED}/DD/GraphicsFrameBuffer_TESys_TED_Display.cpp
)

# TESys/Utils
set(SRC_TESYS_UTILS
${PATH_TESYS_UTILS}/TmdStringTool.cpp
${PATH_TESYS_UTILS}/Tmd2Py.cpp
)

set(SRC_TESYS 
${SRC_TESYS_CONTROL}
${SRC_TESYS_DATA}
${SRC_TESYS_DB}
${SRC_TESYS_NET} 
${SRC_TESYS_PROPERTY} 
${SRC_TESYS_TED} 
${SRC_TESYS_UTILS}
)

add_library(${LIBNAME_TESYS} SHARED ${SRC_TESYS})
target_link_libraries(${LIBNAME_TESYS} PUBLIC ${LIBNAME_COMM} ${LIBNAME_DATABASE} pthread)


################################################################################################################################
#
#  libTED
#
################################################################################################################################

# Setting PATH 
set(PATH_TED ${PATH_ROOT}/TED)
set(PATH_TED_PYTHON ${PATH_TED}/Python)

# TED/Python
set(SRC_TED_PYTHON
${PATH_TED_PYTHON}/AdcApi.cpp
${PATH_TED_PYTHON}/AgingApi.cpp
${PATH_TED_PYTHON}/ANA670X_Api.cpp
${PATH_TED_PYTHON}/DDApi.cpp
${PATH_TED_PYTHON}/PatternApi.cpp
${PATH_TED_PYTHON}/SysApi.cpp
)

set(SRC_TED
${SRC_TED_PYTHON} 
)

add_library(${LIBNAME_TED} SHARED ${SRC_TED})

################################################################################################################################
#
#  App Path Setting
#
################################################################################################################################
set(PATH_APP ${PATH_ROOT}/App)
set(PATH_APP_SERVER ${PATH_APP}/Server)


################################################################################################################################
#
#  App ServerDataAcq
#
################################################################################################################################
set(PATH_APP_SERVER_DATAACQ ${PATH_APP_SERVER}/DataAcq)
set(SOURCE_APP_SERVER_DATAACQ 
${PATH_APP_SERVER_DATAACQ}/main.cpp
${PATH_APP_SERVER_DATAACQ}/Notifier.cpp
${PATH_APP_SERVER_DATAACQ}/NotifierExtern.cpp
${PATH_APP_SERVER_DATAACQ}/NotifierRawDataSaver.cpp
${PATH_APP_SERVER_DATAACQ}/NotifierTCPServer.cpp
${PATH_APP_SERVER_DATAACQ}/NotifierTester.cpp
)

add_executable(${APP_SERVER_DATAACQ} ${SOURCE_APP_SERVER_DATAACQ})
target_link_libraries(${APP_SERVER_DATAACQ} PUBLIC ${LIBNAME_COMM} ${LIBNAME_TESYS} pthread)

################################################################################################################################
#
#  App Server  PatternDraw
#
################################################################################################################################
set(PATH_APP_SERVER_PATTERNDRAW ${PATH_APP_SERVER}/PatternDraw)
set(SOURCE_APP_SERVER_PATTERNDRAW 
${PATH_APP_SERVER_PATTERNDRAW}/main.cpp
${PATH_APP_SERVER_PATTERNDRAW}/PatternDraw.cpp
${PATH_APP_SERVER_PATTERNDRAW}/PatternDrawTCPServer.cpp
)

add_executable(${APP_SERVER_PATTERNDRAW} ${SOURCE_APP_SERVER_PATTERNDRAW})
target_link_libraries(${APP_SERVER_PATTERNDRAW} PUBLIC ${LIBNAME_COMM} ${LIBNAME_TESYS} pthread)

################################################################################################################################
#
#  AppControlHub
#
################################################################################################################################
set(PATH_APP_CONTROL ${PATH_APP}/Control)
set(PATH_APP_CONTROL_HUB ${PATH_APP_CONTROL}/Hub)
set(SOURCE_APP_CONTROL_HUB 
${PATH_APP_CONTROL_HUB}/main.cpp
${PATH_APP_CONTROL_HUB}/Notifier.cpp
${PATH_APP_CONTROL_HUB}/NotifierExtern.cpp
${PATH_APP_CONTROL_HUB}/NotifierOperator.cpp
${PATH_APP_CONTROL_HUB}/NotifierTester.cpp
${PATH_APP_CONTROL_HUB}/CommanderAgent.cpp
${PATH_APP_CONTROL_HUB}/CommanderAgentOperator.cpp
${PATH_APP_CONTROL_HUB}/CommanderAgentOperatorCmdProc.cpp
${PATH_APP_CONTROL_HUB}/CommanderAgentOperatorSockCallback.cpp
${PATH_APP_CONTROL_HUB}/CommanderAgentTester.cpp
${PATH_APP_CONTROL_HUB}/CommanderAgentTesterCmdProc.cpp
${PATH_APP_CONTROL_HUB}/CommanderAgentTesterExtern.cpp
${PATH_APP_CONTROL_HUB}/CommanderAgentTesterSockCallback.cpp
)

add_executable(${APP_CONTROLHUB} ${SOURCE_APP_CONTROL_HUB})
target_link_libraries(${APP_CONTROLHUB} PUBLIC ${LIBNAME_COMM} ${LIBNAME_TESYS} pthread)

################################################################################################################################
#
#  AppControlTester
#
################################################################################################################################
set(PATH_APP_CONTROL_TESTER ${PATH_APP_CONTROL}/Tester)
set(SOURCE_APP_CONTROL_TESTER
${PATH_APP_CONTROL_TESTER}/App.cpp
${PATH_APP_CONTROL_TESTER}/main.cpp)

add_executable(${APP_CONTROL_TESTER} ${SOURCE_APP_CONTROL_TESTER})
target_link_libraries(${APP_CONTROL_TESTER} PUBLIC ${LIBNAME_COMM} ${LIBNAME_TESYS} pthread)

################################################################################################################################
#
#  AppControlOperator
#
################################################################################################################################
set(PATH_APP_CONTROL_OPERATOR ${PATH_APP_CONTROL}/Operator)
set(SOURCE_APP_CONTROL_OPERATOR
${PATH_APP_CONTROL_OPERATOR}/App.cpp
${PATH_APP_CONTROL_OPERATOR}/CmdFileSync.cpp
${PATH_APP_CONTROL_OPERATOR}/CmdHubStatus.cpp
${PATH_APP_CONTROL_OPERATOR}/CmdTED.cpp
${PATH_APP_CONTROL_OPERATOR}/CmdTesterStatus.cpp
${PATH_APP_CONTROL_OPERATOR}/CmdVerify.cpp
${PATH_APP_CONTROL_OPERATOR}/HubStatus.cpp
${PATH_APP_CONTROL_OPERATOR}/main.cpp
${PATH_APP_CONTROL_OPERATOR}/TesterStatus.cpp)

add_executable(${APP_CONTROL_OPERATOR} ${SOURCE_APP_CONTROL_OPERATOR})
target_link_libraries(${APP_CONTROL_OPERATOR} PUBLIC ${LIBNAME_COMM} ${LIBNAME_TESYS} pthread)

################################################################################################################################
#
#  AppControlShell
#
################################################################################################################################
set(PATH_APP_CONTROL_SHELL ${PATH_APP_CONTROL}/Shell)
set(SOURCE_APP_CONTROL_SHELL
${PATH_APP_CONTROL_SHELL}/CmdAndroid.cpp
${PATH_APP_CONTROL_SHELL}/CmdDatabase.cpp
${PATH_APP_CONTROL_SHELL}/CmdEmulator.cpp
${PATH_APP_CONTROL_SHELL}/CmdExport.cpp
${PATH_APP_CONTROL_SHELL}/CmdFileSync.cpp
${PATH_APP_CONTROL_SHELL}/CmdHub.cpp
${PATH_APP_CONTROL_SHELL}/CmdOALTest.cpp
${PATH_APP_CONTROL_SHELL}/CmdSocket.cpp
${PATH_APP_CONTROL_SHELL}/CmdStringTest.cpp
${PATH_APP_CONTROL_SHELL}/CmdSysTest.cpp
${PATH_APP_CONTROL_SHELL}/CmdTED.cpp
${PATH_APP_CONTROL_SHELL}/CmdTester.cpp
${PATH_APP_CONTROL_SHELL}/CmdVerify.cpp
${PATH_APP_CONTROL_SHELL}/main.cpp)

add_executable(${APP_CONTROL_SHELL} ${SOURCE_APP_CONTROL_SHELL})
target_link_libraries(${APP_CONTROL_SHELL} PUBLIC ${LIBNAME_COMM} ${LIBNAME_TESYS} ${LIBNAME_TED} pthread)


################################################################################################################################
#
#  AppFileSync
#
################################################################################################################################
set(PATH_APP_FILESYNC ${PATH_APP}/Client/FileSync)
set(SOURCE_APP_FILESYNC
${PATH_APP_FILESYNC}/main.cpp)

add_executable(${APP_FILESYNC} ${SOURCE_APP_FILESYNC})
target_link_libraries(${APP_FILESYNC} PUBLIC ${LIBNAME_COMM} ${LIBNAME_TESYS} pthread)

################################################################################################################################
#
#  App HubCalCRC
#
################################################################################################################################
set(PATH_APP_HUBCALCRC ${PATH_APP}/Client/HubCalCRC)
set(SOURCE_APP_HUBCALCRC
${PATH_APP_HUBCALCRC}/main.cpp)

add_executable(${APP_HUBCALCRC} ${SOURCE_APP_HUBCALCRC})
target_link_libraries(${APP_HUBCALCRC} PUBLIC ${LIBNAME_COMM} ${LIBNAME_TESYS} pthread)

################################################################################################################################
#
#  App Database RawData
#
################################################################################################################################
set(PATH_APP_DATABASE_RAWDATA ${PATH_APP}/Database/RawData)
set(SOURCE_APP_SERVER_RAWDATA 
${PATH_APP_DATABASE_RAWDATA}/main.cpp
${PATH_APP_DATABASE_RAWDATA}/AppCmdProc.cpp
${PATH_APP_DATABASE_RAWDATA}/Receiver.cpp
${PATH_APP_DATABASE_RAWDATA}/ReceiverDataAcq.cpp
${PATH_APP_DATABASE_RAWDATA}/ReceiverExportCSV.cpp
${PATH_APP_DATABASE_RAWDATA}/ReceiverExtern.cpp
${PATH_APP_DATABASE_RAWDATA}/ReceiverRawDataSaver.cpp
)

add_executable(${APP_DATABASE_RAWDATA} ${SOURCE_APP_SERVER_RAWDATA})
target_link_libraries(${APP_DATABASE_RAWDATA} PUBLIC ${LIBNAME_COMM}  ${LIBNAME_TESYS} pthread)

################################################################################################################################
#
#  App Database MySQL
#
################################################################################################################################
set(PATH_APP_DATABASE_MYSQL ${PATH_APP}/Database/MySQL)
set(SOURCE_APP_SERVER_MYSQL
${PATH_APP_DATABASE_MYSQL}/CmdExport.cpp
${PATH_APP_DATABASE_MYSQL}/CmdInsert.cpp
${PATH_APP_DATABASE_MYSQL}/CmdVerify.cpp
${PATH_APP_DATABASE_MYSQL}/insert.cpp
${PATH_APP_DATABASE_MYSQL}/main.cpp
${PATH_APP_DATABASE_MYSQL}/mysql.cpp
)

add_executable(${APP_DATABASE_MYSQL} ${SOURCE_APP_SERVER_MYSQL})
target_link_libraries(${APP_DATABASE_MYSQL} PUBLIC ${LIBNAME_COMM} ${LIBNAME_TESYS} pthread)

################################################################################################################################
#
#  App Database VerifyRawData
#
################################################################################################################################
set(PATH_APP_DATABASE_VerifyRAWDATA ${PATH_APP}/Database/VerifyRawData)
set(SOURCE_APP_SERVER_VerifyRAWDATA 
${PATH_APP_DATABASE_VerifyRAWDATA}/main.cpp
)

add_executable(${APP_DATABASE_VerifyRAWDATA} ${SOURCE_APP_SERVER_VerifyRAWDATA})
target_link_libraries(${APP_DATABASE_VerifyRAWDATA} PUBLIC ${LIBNAME_COMM} ${LIBNAME_TESYS} pthread)

################################################################################################################################
#
#  Python Module TED
#
################################################################################################################################

# Setting PATH 
set(PATH_PYTHON ${PATH_ROOT}/Python)
set(PATH_PYTHON_MODULES ${PATH_PYTHON}/Modules)

# Setting All Source Files 
set(SRC_PYTHON_MODULES_TED
${PATH_PYTHON_MODULES}/_ted.c
) 

add_library(${PYTHON_MODULE_TED} SHARED ${SRC_PYTHON_MODULES_TED})
target_link_libraries(${PYTHON_MODULE_TED} PUBLIC TED TESysComm TESysTESys pthread)


################################################################################################################################
#
#  Install
#
################################################################################################################################

set(INSTALL_LIB_PATH /opt/TESys/lib)
set(INSTALL_BIN_PATH /opt/TESys/bin)

install(TARGETS 
${APP_CONTROLHUB}  
${APP_SERVER_DATAACQ} 
${APP_SERVER_PATTERNDRAW} 
${APP_FILESYNC} 
${APP_HUBCALCRC} 
${APP_CONTROL_TESTER} 
${APP_CONTROL_OPERATOR} 
${APP_CONTROL_SHELL} 
${APP_DATABASE_RAWDATA}
${APP_DATABASE_MYSQL}
${APP_DATABASE_VerifyRAWDATA}
DESTINATION ${INSTALL_BIN_PATH}
)

install(TARGETS 
${LIBNAME_COMM} 
${LIBNAME_DATABASE} 
${LIBNAME_TESYS} 
${LIBNAME_TED}  
${PYTHON_MODULE_TED} 
DESTINATION ${INSTALL_LIB_PATH}
)



