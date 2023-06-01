cmake_minimum_required(VERSION 3.10)

# app工程名
project(versionProj VERSION 1.2) 

# 设置变量 var value
set(VAR1 1)
set(VAR2 2)
# 文件、目录
set(SRC_FILE version.cpp)
set(SRC_LIB_DIR library)
# c++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 将input文件中的@var@或者${var}替换成cmake中的变量。
# input output
configure_file(versionProjConfig.h.in versionProjConfig.h)

# 构建工程的源文件
add_executable(version.out ${SRC_FILE})
# 将子目录添加到构建
add_subdirectory(${SRC_LIB_DIR})

#----------------------------------

#[[
为target - 设定头文件查找目录
INTERFACE：target对应的头文件使用
PRIVATE：target对应的源文件使用
PUBLIC：target对应的头文件、源文件都使用
PROJECT_BINARY_DIR：主目录
]]
# target_include_directories(version.out PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/library")

# 为整个项目 - 设定头文件查找目录
include_directories(
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/library"
)

# 为target链接库
target_link_libraries(version.out PUBLIC strlib)
