#!/opt/homebrew/bin/python3.11

# list 推导

# 作用：遍历一个list，过滤一些不符合条件的值，再给一个表达式去计算最后结果；得到一个新list
# new_list = [out_expr for i in old_list if condition]
# out_expr          : 过滤出的i，经过out_expr得出最后结果
# for i in old_list : 遍历一个list
# if condition      : 过滤一些不符合条件的值；可以省略

print('-------------------------- list')

list2 = [i + 100 for i in range(1, 11) if i > 4]
print(list2)

list2 = ['_' + str(i) + '_' for i in range(0,101) if i % 2 == 0]
print(list2)

# 也可以和i无关，只要i满足if条件，就会进入out_expr
list2 = ['x' for i in range(0,101) if i % 2 == 0]
print(list2)

print('-------------------------- set')

# 集合推导式
# new_set = [out_expr for i in old_set if condition]
set1 = {i**2 for i in range(1, 11) if i > 5}
print(set1)

print('-------------------------- tuple')

# 元组推导式
tup1 = (i**2 for i in range(1, 11) if i > 5)
print(tup1) # 返回一个生成器对象
print(tuple(tup1)) # 用tuple将其构造成元组

print('-------------------------- dic')

# new_dic = {key_expr : value_expr for key in dict if condition}
dic1 = {1:'a', 2:'b', 3:'c', 4:'d'}
dic2 = {key:key**2 for key in dic1}
print(dic2)

# 保持原样
dic1 = {1:'a', 2:'b', 3:'c', 4:'d'}
dic2 = {key:dic1[key] for key in dic1}
print(dic2)

dic1 = {1:'a', 2:'b', 3:'c', 4:'d'}
dic2 = {key + 10 : str(key) + '_' + str(key*key) for key in dic1}
print(dic2)
