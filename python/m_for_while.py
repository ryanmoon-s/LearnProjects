#!/opt/homebrew/bin/python3.11

#  Python 中没有 do..while 循环

# while else
str1 = '' # 必须先定义
i = 0
while i < 10:
    if (i == 5):
        break
    str1 += str(i) + ' ' # 才能识别
    i+=1
else: # 循环正常结束之后执行；循环break出来不执行
    print("while end") # 不执行
print(str1)

str1 = ''
i = 0
while i < 10:
    str1 += str(i) + ' '
    i+=1
else: # 循环正常结束之后执行；循环break出来不执行
    print("while end") # 执行
print(str1)

# for list
str1 = ''
list1 = [1, 2, 3, 4]
for i in list1:
    str1 += str(i) + ' '
print(str1)

# for range; 不包含end
sum1 = 0
for i in range(1, 101, 1): 
    sum1 += i
else: # 循环正常结束之后执行；循环break出来不执行
    print("for end")
print(sum1)

for i in range(0, len(list1)): # range不包含最后一个，刚好
    print(i, list1[i])


# pass
# 占位语句，什么也不做

for i in range(1, 21):
    print(i, end=',') # 不输出换行，输出,