from common.models import Customer
from django.http import JsonResponse
from mgr.cgi import handler
import json

def BEGIN(func_name, request):
    print(f"{func_name} begin, param: {request.params}")

PubErrResponse = {
    'param_err': {'ret':-2003, 'msg': 'param_err'}
}

def ListCustomer(request):
    BEGIN("ListCustomer", request)
    qs = Customer.objects.values()
    cus_lst = list(qs)
    return JsonResponse({'ret':0, 'retlist':cus_lst})

def AddCustomer(request):
    BEGIN("AddCustomer", request)
    info = request.params.get('data') # 没有则返回None
    if not info:
        print("param err")
        return JsonResponse(PubErrResponse['param_err'])
    
    record = Customer.objects.create(
        name=info['name'],
        phonenumber=info['phonenumber'],
        address=info['address']
    )
    
    return JsonResponse({'ret':0, 'id':record.id})

def ModCustomer(request):
    BEGIN("ModCustomer", request)
    customerid = request.params.get('id')
    newdata = request.params.get('newdata')
    if not customerid or not newdata:
        print("param err", customerid, newdata)
        return JsonResponse(PubErrResponse['param_err'])
    
    try:
        customer = Customer.objects.get(id=customerid)
    except Exception as e:
        print('exception', request.params, e)
        return JsonResponse({'ret':1, 'msg':f'id:{customerid}, 不存在'})
    
    if 'name' in newdata:
        customer.name = newdata['name']
    if 'phonenumber' in newdata:
        customer.phonenumber = newdata['phonenumber']
    if 'address' in newdata:
        customer.address = newdata['address']

    # 保存进数据库
    customer.save()
    
    return JsonResponse({'ret':0})

def DelCustomer(request):
    BEGIN("DelCustomer", request)
    customerid = request.params.get('id')
    if not customerid:
        print("param err", customerid,)
        return JsonResponse(PubErrResponse['param_err'])
    
    try:
        customer = Customer.objects.get(id=customerid)
    except Exception as e:
        print('exception', request.params, e)
        return JsonResponse({'ret':1, 'msg':f'id:{customerid}, 不存在'})
    
    customer.delete()
    
    return JsonResponse({'DelCustomer':True})

Action2Handler = {
    'list_customer': ListCustomer,
    'add_customer': AddCustomer,
    'modify_customer': ModCustomer,
    'del_customer': DelCustomer,
}

def Dispatcher(request):
    return handler.DispatcherBase(request, Action2Handler)
