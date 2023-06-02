cmake_minimum_required(VERSION 3.10)

project(STRLIB)

# set(SRC_FILE lib.cpp)
file(GLOB SRC_CPP_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_HEADER_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

# 头文件路径
include_directories(${SRC_HEADER_LIST})

# 静态库
add_library(strlib STATIC ${SRC_CPP_LIST})

# 动态库
# add_library(strlib SHARED ${SRC_FILE})
