cmake_minimum_required(VERSION 3.8)
project("TESys-Python-Module")

set(PATH_RELEASE .)
set(PATH_ROOT ../..)
set(PATH_PYTHON_INCLUDE  /opt/TESys/android-emul/system/etc/python/include/python3.8)


set(PATH_RELEASE release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release/bin)

set(PYTHON_MODULE_TED PythonModuleTED)

include_directories(${PATH_PYTHON_INCLUDE} ${PATH_ROOT})
ADD_DEFINITIONS(-DLINUX)
add_compile_options(-std=c++11)

################################################################################################################################
#
#  Module TED
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

install(TARGETS ${PYTHON_MODULE_TED} 
DESTINATION ${INSTALL_LIB_PATH}
)

