cmake_minimum_required(VERSION 3.10)

project(STRLIB)

file(GLOB SRC_CPP_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_HEADER_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

# 头文件路径
include_directories(${SRC_HEADER_LIST})

# 静态库
add_library(strlib STATIC ${SRC_CPP_LIST})

# 动态库
# 具有传递性，A链接B B链接C ; A就会链接C
# add_library(strlib SHARED ${SRC_CPP_LIST})
# 设置动态库生成路径 动态库是可执行的 所以适用
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 设置动态库/静态库生成路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)