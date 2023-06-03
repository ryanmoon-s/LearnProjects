cmake_minimum_required(VERSION 3.10)

# app工程名
project(varProj VERSION 1.2) 

file(GLOB SRC_CPP ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_HEAD ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

# set 拼接到var上，本质上是一个list
# /Users/shishun/LearnProjects/cmake/var/a.cpp/Users/shishun/LearnProjects/cmake/var/a.h
set(SRC_SET_ALL ${SRC_CPP} ${SRC_HEAD})
message(WARNING ${SRC_SET_ALL})

# list

# 拼接 op var stra [strb...]
list(APPEND SRC_APPEND_ALL ${SRC_CPP} ${SRC_HEAD} "_hello" "_world")
message(WARNING ${SRC_APPEND_ALL})

# 移除
# REMOVE_ITEM list var1 [var2...]
list(REMOVE_ITEM SRC_APPEND_ALL ${CMAKE_CURRENT_SOURCE_DIR}/a.h "_world")
message(WARNING ${SRC_APPEND_ALL})

# 长度 2
# LENGTH list var
list(LENGTH SRC_APPEND_ALL list_len)
message(WARNING ${list_len})

# 读取 0开始
# GET list index var
list(GET SRC_APPEND_ALL 1 list_get_1)
message(WARNING ${list_get_1})

# 将列表用连接符连接成一个字符串
# JOIN list gule连接符 var
list(JOIN SRC_APPEND_ALL "-" join_result)
message(WARNING ${join_result})

# 获取值 1
# FIND list value var
list(FIND SRC_APPEND_ALL "_hello" find_result)
message(WARNING ${find_result})

# INSERT 指定的位置插入若干元素
# PREPEND 左边插入

# POP_BACK 将列表中最后元素移除
# POP_FRONT 将列表中第一个元素移除
# REMOVE_ITEM 将指定的元素从列表中移除
# REMOVE_AT 将指定索引的元素从列表中移除
# REMOVE_DUPLICATES 移除列表中的重复元素
# REVERSE 列表翻转

# SORT 列表排序
# SORT list [COMPARE ..] [CASE ..] [ORDER ..]
#[[
COMPARE：指定排序方法。有如下几种值可选：
    STRING: 按照字母顺序进行排序，为默认的排序方法
    FILE_BASENAME：如果是一系列路径名，会使用 basename 进行排序
    NATURAL：使用自然数顺序排序
CASE：指明是否大小写敏感。有如下几种值可选：
    SENSITIVE: 按照大小写敏感的方式进行排序，为默认值
    INSENSITIVE：按照大小写不敏感方式进行排序
ORDER：指明排序的顺序。有如下几种值可选：
    ASCENDING: 按照升序排列，为默认值
    DESCENDING：按照降序排列
]]