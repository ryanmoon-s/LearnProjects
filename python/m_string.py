#!/usr/bin/python3

# 字符串运算符
# + (连接)
# * (重复)
str = 'hello '
print(4 * str)
# [] (索引获取)
# [start:end;step] (截取一部分)   -- [:] copy一份0-len
# in ; not in
# r/R (原始字符串，不转义)
# % （格式化） 具体可以参考c
str = "my name is %s, i am %d years old" % ("xiao hong", 10)
print(str)
str2 = "%-10.3f" % (333.32323)
print(str2)

# 三引号，跨行，（所见即所得）
# \连接，否则是换行
str = '''
hello \
worl\td
xxxx\n\n
-----
'''
print(str)

# f-string ，python3.6 之后版本添加的，称之为[字面量格式化字符串]
name = 'Aliace'
print(f'my name is {name}')
# Python 3.8
x = 3
print(f'{x+1=}')

# 内建函数 str自己不会变，返回结果
# str.func()

str = 'hello world lo lo'
# str.capitalize() # 将字符串的第一个字符转换为大写
# str.center(20, '+') # 返回一个指定的宽度arg1居中的字符串，arg2为填充的字符，默认为空格。
# str.count('lo', 0, len(str))  # 出现次数
# endswith(suffix, beg=0, end=len(string)) # 是否以suffix结尾
# find(str, beg=0, end=len(string))  # 索引 or -1
# rfind(str, beg=0, end=len(string))  # 索引 or -1

# 至少一个字段，且只包含xx，则返回True，否则返回False
# str.isalnum()
# str.salpha()
# str.isdigit()
# str.isnumeric()
# str.islower()
# str.isupper()
# str.isspace()
# str.lower()
# str.upper()
# str.swapcase() # 大写->小写，小写->大写
# str.replace('lo', 'ii', max) # 替换不超过 max 次。

# 删除字符串末尾/开头的空格或指定字符
# str.strip('h')
# str.rstrip()
# str.lstrip()

plist = str.split('l')
print(plist)

str2 = str.ljust(30, '0') # 左对齐，填充
str2 = str.rjust(30, '0') # 右对齐，填充