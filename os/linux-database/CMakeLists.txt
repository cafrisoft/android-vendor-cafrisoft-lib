cmake_minimum_required(VERSION 3.8)
project("TESysDataBase")

set(PATH_RELEASE .)
set(PATH_ROOT ../..)


set(PATH_RELEASE release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release/bin)


set(LIBNAME_COMM TESysComm)
set(LIBNAME_TESYS TESysTESys)
set(LIBNAME_TED TED)

set(APP_DATABASE_MYSQL TESysDBMySql)

include_directories(${PATH_ROOT})
ADD_DEFINITIONS(-DLINUX)
add_compile_options(-std=c++11)


################################################################################################################################
#
#  App Path Setting
#
################################################################################################################################
set(PATH_APP ${PATH_ROOT}/App)
set(PATH_APP_SERVER ${PATH_APP}/Server)


################################################################################################################################
#
#  App Database RawData
#
################################################################################################################################
set(PATH_APP_DATABASE_MYSQL ${PATH_APP}/Database/MySQL)
set(SOURCE_APP_SERVER_DATABASE 
${PATH_APP_DATABASE_MYSQL}/main.cpp
${PATH_APP_DATABASE_MYSQL}/AppCmdProc.cpp
)

add_executable(${APP_DATABASE_MYSQL} ${SOURCE_APP_SERVER_DATABASE})
target_link_libraries(${APP_DATABASE_MYSQL} PUBLIC ${LIBNAME_COMM} ${LIBNAME_TESYS} pthread)

################################################################################################################################
#
#  Install
#
################################################################################################################################
set(INSTALL_BIN_PATH /opt/TESys/bin)

install(TARGETS ${APP_DATABASE_MYSQL}
DESTINATION ${INSTALL_BIN_PATH}
)


