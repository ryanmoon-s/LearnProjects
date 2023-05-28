#!/opt/homebrew/bin/python3.11
import random

target = int(random.randint(0, 10))

'''
while True:
    num = int(input("输入一个10以内的数字"))
    if num == target:
        print("rignt")
        break;
    elif num > target:
        print("upper")
    elif num < target:
        print('lower')
'''

# match...case ; Python 3.10

def http_error(status):
    match status:
        case 400|401|402:
            return "Bad request"
        case 404:
            return "Not found"
        case 418:
            return "I'm a teapot"
        case _:
            return "Something's wrong with the internet"

print(http_error(400))
print(http_error(401))
print(http_error(404))
print(http_error(500))