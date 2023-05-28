#!/usr/bin/python3

# 算术运算符
# + - * / %
# ** (乘方)
# // (往小的方向取整数)
print(9//2)

# 比较运算符
# == != > < >= <=

# 赋值运算符
# = += -= *= /= %= **= //= 
# := (海象运算符，可在表达式内部为变量赋值 Python3.8 版本新增运算符)
str = 'hello world'
if (n := len(str)) > 5:
    print("len > 5")

# 位运算符
# & | ^ ~ << >>

# 逻辑运算符
# and or not

# 成员运算符
# in
# not in

# 身份运算符
# is 
# is not
a = 20
b = 20
print(a is b)
print(a == b)
a = [1, 2, 3]
b = a
print(a is b)
print(a == b)
b = a[:]
print(a is b) # False 另一个对象 
print(a == b)

