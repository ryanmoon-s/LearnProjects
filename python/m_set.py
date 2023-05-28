#!/usr/bin/python3

# 空集合
set1 = set()
print(set1)

set1 = set('ddddfsf1ass') # 每个字符一个元素
print(set1)

set1 = set({'123', '422', 'hello'})
set1 = set(('123', '422', 'hello'))
set1 = {'123', '422', 'hello'}
print(set1)

print('-------------------')
# 集合操作

a = set('abcdefghijklmn234')
b = set('jklmnopqrstuvw456')

# 并
print(a | b)
# 交
print(a & b)
# 差
print(a - b)
# 不同时包含，只在其中一个集合中
print(a ^ b)

print('------------------- 函数')

# add
set1 = set('12345') 
print(set1)

set1.add(98)
print(set1)

# update 参数可以是列表，元组，字典等，可以是多个参数
set1 = set()
set1.update([11, 22, 33, 44], [55, 66], ('aa', 'bb', 'cc'))
print(set1)

set1 = set()
set1.update({11:"a", 22:"b", 33:"c", 44:'d'}) # 字典，只插入key
print(set1)

print('-- del', set1)
# remove 不存在时，会报错
# 返回None
set1.remove(11)

# discard 不存在时，不会报错
# 返回删除的元素（不存在为None）
print(set1.discard(3) == None)

# pop 随机删除一个元素
# 返回删除的元素
print(set1.pop())
print(set1)


# 函数
# print(len(set1))
# set1.clear()
# set1.copy()

set1 = {1, 2, 3, 4, 5}
print(1 in set1)

# set1 - set2 - set3 - set4 只返回结果
set2 = {3}
set3 = {4}
set4 = {5}
print(set1.difference(set2, set3, set4))

# set1 - set2 - set3 - set4 更新到set1
set1.difference_update(set2, set3, set4)
print(set1)

# 交集
# set1.intersection(set2, set3, set4)
# set1.intersection_update(set2, set3, set4)

# 是否是 没有交集的，没有交集->True，有交集->True
set1 = {1, 2, 3}
set2 = {3, 4, 5}
print(set1.isdisjoint(set2))

# 是否是入参的子集
set1 = {1, 2, 3, 4}
set2 = {3, 4}
set3 = {3, 5}
print(set2.issubset(set1)) # set2是set1的子集
print(set3.issubset(set1)) # set3不是set1的子集

# 是否是入参的超集
print(set1.issuperset(set2)) # set1是set2的超集

# union
set1 = {1, 2, 3, 4, 5}
print('-- union', set1)
print(set1.union({6, 7, 8}))