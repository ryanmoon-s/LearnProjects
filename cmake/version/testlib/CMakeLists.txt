cmake_minimum_required(VERSION 3.10)

# 设置内部文件变量
file(GLOB SRC_CPP_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_HEADER_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# 设置lib变量
set(LIB_NAME strlib)
set(LIB_PATH ${PROJECT_SOURCE_DIR}/library)
# 设置二进制名字
set(BIN_NAME testlib)

# 头文件查找路径
include_directories(${SRC_HEADER_LIST})
# 设置可执行二进制生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 库查找位置
link_directories(${LIB_PATH})
# 添加静态库
link_libraries(${LIB_NAME})

add_executable(${BIN_NAME} ${SRC_CPP_LIST})