# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(HarmonyLeaksDetector)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror=return-type -Wl,--hash-style=sysv")

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include
                    ${NATIVERENDER_ROOT_PATH}/inline64/
                    ${NATIVERENDER_ROOT_PATH}/unwind64/
                    ${NATIVERENDER_ROOT_PATH}/xDL/
)

# 增加hiloglib库引用
find_library(
    # Sets the name of the path variable.
    hilog-lib
    # Specifies the name of the NDK library that
    # you want CMake to locate.
    hilog_ndk.z
)

add_library(
    raphael
    SHARED

    # And64InlineHook
    ${NATIVERENDER_ROOT_PATH}/inline64/And64InlineHook.cpp

    # Unwind-64
    ${NATIVERENDER_ROOT_PATH}/unwind64/backtrace_64.cpp

    # xDL
    ${NATIVERENDER_ROOT_PATH}/xDL/xdl.c
    ${NATIVERENDER_ROOT_PATH}/xDL/xdl_iterate.c
    ${NATIVERENDER_ROOT_PATH}/xDL/xdl_linker.c
    ${NATIVERENDER_ROOT_PATH}/xDL/xdl_lzma.c
    ${NATIVERENDER_ROOT_PATH}/xDL/xdl_util.c

    # Raphael napi provider
    ${NATIVERENDER_ROOT_PATH}/Raphael.cpp
    # Raphael Utility
    ${NATIVERENDER_ROOT_PATH}/MemoryCache.cpp
    ${NATIVERENDER_ROOT_PATH}/MapData.cpp
)

target_link_libraries(raphael PUBLIC ${hilog-lib} libace_napi.z.so)