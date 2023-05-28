#!/usr/bin/python3
sep = '-------------- '

'''
Number（数字）
String（字符串）
bool（布尔类型）
bytes（字节数组类型，二进制）
-------
Tuple（元组）

List（列表）
Set（集合）
Dictionary（字典）
--------
不可变数据（3 个）：Number（数字）、String（字符串）、Tuple（元组）；
可变数据（3 个）：List（列表）、Set（集合）、Dictionary（字典）。
'''

print(sep, 'bytes')
pbytes1 = b'hello'
print(pbytes1)
# bytes 类型中的元素是整数值，因此在进行比较操作时需要使用相应的整数值。
if pbytes1[0] == ord("h"):
    print("yes")

print(sep, 'list')
plist1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
plist2 = plist1[:]
plist3 = plist1[2:-1:2]
print(plist1)
print(plist2)
print(plist3)

plist3.append('hello')
plist3.append('world')
print(plist3)

print(sep, 'dir')
pdir1 = {1:"hello", 2:"world"}
pdir1["hello"] = 1
pdir1["world"] = 2
print(pdir1)

print(sep, 'set')
pset1 = {1, 2, 3, 4, 'hello', False, True}
print(pset1)
pset2 = set('helloworld') # 每个字母是一个元素
print(pset2)

