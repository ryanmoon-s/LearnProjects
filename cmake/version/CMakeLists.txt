cmake_minimum_required(VERSION 3.10)

# app工程名
project(versionProj VERSION 1.2) 

# 设置变量
set (VAR1 1)
set (VAR2 2)

# 将input文件中的@var@或者${var}替换成cmake中的变量。
# input output
configure_file(versionProjConfig.h.in versionProjConfig.h)

# c++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 构建工程的源文件
add_executable(version.out version.cpp)

# 为指定的target设定头文件查找目录
# INTERFACE：target对应的头文件使用
# PRIVATE：target对应的源文件使用
# PUBLIC：target对应的头文件、源文件都使用
target_include_directories(version.out PUBLIC "${PROJECT_BINARY_DIR}")