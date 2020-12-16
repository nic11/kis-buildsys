cmake_minimum_required(VERSION 3.0)
project(SimpleLibrary)

# cross-compiling
if (NOT DEFINED SYSROOT)
    message(FATAL_ERROR "please define SYSROOT, e.g. -DSYSROOT=/path/to/sysroot-glibc-linaro-2.25-2019.12-arm-linux-gnueabihf")
endif()

if (NOT DEFINED TOOLCHAIN)
    message(FATAL_ERROR "please define SYSROOT, e.g. -DTOOLCHAIN=/path/to/gcc-linaro-7.5.0-2019.12-i686_arm-linux-gnueabihf")
endif()

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_SYSROOT ${SYSROOT})

include(CMakeForceCompiler)

set(CMAKE_C_COMPILER ${TOOLCHAIN}/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN}/bin/arm-linux-gnueabihf-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_INSTALL_PREFIX ${SYSROOT})


# build
include_directories(include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SimpleLibrary_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SimpleLibrary_SOURCE_DIR}/lib)
add_subdirectory(src)
add_executable(Main main.cpp)
add_executable(MainLib main_lib.cpp)

target_link_libraries(MainLib buffer)

# install
install(TARGETS Main MainLib)
