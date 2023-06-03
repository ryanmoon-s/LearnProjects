cmake_minimum_required(VERSION 3.10)

# app工程名
project(versionProj VERSION 1.2) 

# 设置变量
# var value
set(VAR1 1)
set(VAR2 2)
# 文件、目录
set(SRC_FILE version.cpp)
set(SRC_LIB_DIR library)
# c++ 11
set(CMAKE_CXX_STANDARD 11)

# 宏定义
add_definitions(-DMY_DEF_1)
add_definitions(-DMY_DEF_2=2)

#----------------------------------

# 指定目录下的所有源文件，输出到变量
# dir var
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ALL_SRC_FILE)

# 匹配指定类型文件，输出到变量
# option var dir
# option: GLOB-不递归, GLOB_RECURSE-递归寻找
file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB MAIN_HEAD ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

#----------------------------------

# 将input文件中的@var@或者${var}替换成cmake中的变量。
# 目标文件位置：PROJECT_BINARY_DIR
# input output
configure_file(versionProjConfig.h.in versionProjConfig.h)

#----------------------------------

# 构建工程的源文件
add_executable(version.out ${MAIN_SRC})
# 将子目录CMakeLists添加到构建
add_subdirectory(${SRC_LIB_DIR})

#----------------------------------

#[[ -- 为target - 设定头文件查找目录，默认PUBLIC
INTERFACE：在 interface 后面引入的库不会被链接到前面的 target 中，只会导出符号
PRIVATE：在 private 后面的库仅被 link 到前面的 target 中，并且终结掉，第三方不能感知你调了啥库
PUBLIC：在 public 后面的库会被 Link 到前面的 target 中，并且里面的符号也会被导出，提供给第三方使用。
]]
# target_include_directories(version.out PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/library")

# 为整个项目 - 设定头文件查找目录
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}"       # 当前CMakeLists所在目录
    "${PROJECT_BINARY_DIR}"             # 执行 cmake 命令的目录 - ./build/
    "${PROJECT_SOURCE_DIR}/library"     # 使用 cmake 命令后紧跟的目录，一般是工程的根目录
)
#[[
EXECUTABLE_OUTPUT_PATH  - 重新定义 目标二进制可执行文件的存放位置
LIBRARY_OUTPUT_PATH     - 重新定义 目标链接库文件的存放位置
PROJECT_NAME            - 返回通过 PROJECT 指令定义的项目名称
CMAKE_BINARY_DIR        - 项目实际构建路径，假设在 build 目录进行的构建，那么得到的就是这个目录的路径
]]

#----------------------------------

# 设定链接时的查找目录
link_directories(${PROJECT_SOURCE_DIR}/lib)

# 为target链接库 可以是动态库、静态库
# 要在add_executable之后链接
target_link_libraries(version.out PUBLIC strlib)

#----------------------------------

# 日志

# this
message(
"this is
default 
msg")
# -- xxx
message(STATUS "[!this is STATUS msg]")
# 黄色 突出
message(WARNING "[!this is WARNING msg]")
message(AUTHOR_WARNING "[!this is AUTHOR_WARNING msg]")
# CMake 错误，继续执行，但是会跳过生成的步骤
# message(SEND_ERROR "[!this is SEND_ERROR msg]")
# CMake 错误，终止所有处理过程
# message(FATAL_ERROR "[!this is FATAL_ERROR msg]")
