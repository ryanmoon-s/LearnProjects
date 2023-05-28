#!/opt/homebrew/bin/python3.11

# 不可变类型
# 变量赋值 a=5 后再赋值 a=10，这里实际是新生成一个 int 值对象 10，再让 a 指向它
# strings, numbers, tuples

# 可变类型
# 变量赋值 la=[1,2,3,4] 后再赋值 la[2]=5 则是将 list la 的第三个元素值更改
# set, list, dict

# Python参数传递
# 不可变类型：值传递
# 可变类型：引用传递

# 不可变
def ChangeSet(iSet):
    iSet.add(200)

iSet = set(range(0, 11))
ChangeSet(iSet)
print(iSet)

# 可变
def ChangeString(iStr):
    iStr += "world"

iStr = "hello"
ChangeString(iStr)
print(iStr)