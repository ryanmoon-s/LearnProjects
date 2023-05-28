#!/usr/bin/python3

# 元组与列表类似，不同之处在于元组的元素不能修改
# 元组使用小括号 ( )，列表使用方括号 [ ]

tup1 = ('Google', 'Runoob', 1997, 2000)
print(tup1)

# 空元组
tup1 = ()

# 一个元素
tup1 = (2)
print(type(tup1)) # 识别成int
tup1 = (1,)
print(type(tup1)) # 正确

# 与list类似，可以截取 组合
# + * 
# in
tup1 = (1, 2, 3, 4, 5)
for i in tup1:
    print(i)

# 修改，不可以修改，可以组合多个tup
# tup1[0] = 100 # error

tup1 = (1, 2, 3)
tup2 = (4, 5, 6)
tup3 = tup1 + tup2
print(tup3)

# 删除，不可以删除元素，可以删除整个变量
del tup3
# print(tup3) # error 已经被删除


# 内置函数
tup1 = (1, 2, 3, 4, 5, 44)
print(len(tup1))

print(max(tup1))
print(min(tup1))

# list -> tuple
list1 = [1, 2, 3, 45, 98]
tup1 = tuple(list1)
print(tup1)

# tuple -> list
list2 = list(tup1)
print(list2)

# 元组不可变？
# 内容不可变，指向可变