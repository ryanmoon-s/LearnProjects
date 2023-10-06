from django.test import TestCase
import requests, pprint

ip = '123.60.86.245'
port = 8080
host = f'http://{ip}:{port}'

# list_customer
def Test_list_customer():
    response = requests.get(f'{host}/api/mgr/customers?action=list_customer')
    pprint.pprint(response.json())
    ret = int(response.json().get('ret', 0))
    if ret:
        print('list_customer err', ret)
        return ret

# add_customer
def Test_add_customer():
    payload = {
        "action":"add_customer",
        "data":{
            "name":"武汉市桥西医院",
            "phonenumber":"13345679934",
            "address":"武汉市桥西医院北路"
        }
    }
    response = requests.post(f'{host}/api/mgr/customers/', json=payload)
    ret = int(response.json().get('ret', 0))
    if ret:
        print('add_customer err', ret)
        return ret

    # 再查一下
    Test_list_customer()
    
    customerid = int(response.json().get('id', 0))
    return customerid

# modify_customer
def Test_modify_customer(customerid, name, phonenumber, address):
    payload = {
        "action":"modify_customer",
        "id":customerid,
        "newdata":{
            "name":name,
            "phonenumber":phonenumber,
            "address":address
        }
    }
    response = requests.post(f'{host}/api/mgr/customers/', json=payload)
    ret = int(response.json().get('ret', 0))
    if ret:
        print('modify_customer err', ret)
        return ret
    
    # 再查一下
    Test_list_customer()
    
# del_customer
def Test_del_customer(customerid):
    payload = {
        "action":"del_customer",
        "id":customerid
    }
    response = requests.post(f'{host}/api/mgr/customers/', json=payload)
    ret = int(response.json().get('ret', 0))
    if ret:
        print('add_customer err', ret)
        return ret
    
    # 再查一下
    Test_list_customer()


# exec
def Test():
    Test_list_customer()
    customerid = Test_add_customer()
    if not customerid > 0:
        print("customerid err", customerid)
        return
    Test_modify_customer(customerid, '小瓜瓜', '12345678', '地球村')
    Test_del_customer(customerid)
    
Test()