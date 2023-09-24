#!/usr/bin/python3

dic1 = {1:"hello", 2:"world"}
print(dic1)

# 空字典
dic1 = {}
print(dic1)

dic1 = dict()
print(dic1)

# 访问
dic1 = {"hello":1, "world":2}
print(dic1['hello'])

# 访问不存在元素
# print(dic1['hh']) # error报错

# defaultvalue给一个默认值
from collections import defaultdict
dict2 = defaultdict(int) # 默认值为int类型0
print(dict2['key'])

# update insert
dic1['hh'] = 20
dic1['hh'] = 30 # this
print(dic1['hh'])

# del
print(dic1)
dic1.clear()  # 清空
print(dic1)   # 不报错

del dic1
# print(dic1)  # 报错，已被删除

# 不允许同一个键出现两次。创建时如果同一个键被赋值两次，后一个值会被记住
# 键必须不可变，所以可以用数字，字符串或元组充当，而用列表就不行

# 函数
dic1 = {"hello":1, "world":2}
print(len(dic1))
print(str(dic1))
print(dic1)

# dic的方法
# clear
# copy

# 以一个初始列表为key，value为默认值None
list1 = ['hello', 'world', 'xx']
print(dict.fromkeys(list1))

# get 不存在为默认值None
print(dic1.get('hello') == None)
print(dic1.get('biu') == None)

# in
print("hello" in dic1)

# set 一个value为None的key
dic1.setdefault('hh')
print(dic1)

# dic2 中的值更新到 dic1 
dic2 = {"hello":222}
dic1.update(dic2)
print(dic1)

# value视图
print(dic1.values())

# 返回并删除最后一个键值对
print(dic1.popitem())
print(dic1)

# 删除键
dic1.pop('hello')
print(dic1)