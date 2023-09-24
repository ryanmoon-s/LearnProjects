# 空列表
list1 = []
print(list1)

print('xxxxxxxxxx')
list1 = [0, 1, 2, 3, 4, 5, 6, 7, 8]
print(list1)

# append
list1.append("hello")
print(list1)

# del
del list1[0]
print(list1)

# update
list1[0] += 20
print(list1)

# find
print(list1[0])

# + *
print(list1 + ['w', 'o'])
print(list1 * 2)

# 嵌套
list1 = [1, 2, 3, [4, 5, 6, [7, 8, 9]]]
print(list1)

# 比较 需要导入operator
import operator

a = [1, 2]
b = [2, 3]
c = [2, 3]
print("operator.eq(a,b): ", operator.eq(a,b))
print("operator.eq(c,b): ", operator.eq(c,b))

# 函数
list1 = [1, 2, 3, 5, 6, 3, 2, 2, -2]
print(len(list1))
print(max(list1))
print(min(list1))

# 方法
list1.append(34)
print(list1)

list2 = ["hello", "world"]
list1.extend(list2)
print(list1)

print(list1.count(2))
print(list1.index(2))

list1.pop(0) # index 默认-1
print(list1)

list1.remove(6) # value 第一个匹配值
print(list1)

list1.reverse() # 反转
print(list1)

list1.clear()
print(list1)

list1 = list2.copy() # 复制一份，不影响以前的
print(list1, list2)
list1.clear()
print(list1, list2)

list1 = list2
list1.clear() # 指向同一个对象
print(list1, list2)
