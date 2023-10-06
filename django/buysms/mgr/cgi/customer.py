from common.models import Customer
from django.http import JsonResponse
import json

def Dispatcher(request):
    # 校验登录状态，这个时候框架已经用前端带上来的sessionid取到了session data
    if 'usertype' not in request.session:
        print("no usertype in session")
        return JsonResponse({
            'ret': 302,
            'msg': '未登录',
            'redirect': '/mgr/sign.html'}, 
            status=302)

    if request.session['usertype'] != 'mgr':
        print("usertype err", request.session['usertype'])
        return JsonResponse({
            'ret': 302,
            'msg': '用户非mgr类型',
            'redirect': '/mgr/sign.html'} ,
            status=302)
    
    # 将请求参数统一放入request 的 params 属性中，方便后续处理
    # GET请求 参数在url中，同过request 对象的 GET属性获取
    if request.method == 'GET':
        request.params = request.GET
    # POST/PUT/DELETE 请求 参数 从 request 对象的 body 属性中获取
    elif request.method in ['POST','PUT','DELETE']:
        # 根据接口，POST/PUT/DELETE 请求的消息体都是 json格式
        request.params = json.loads(request.body)
    
    # 根据不同的action分派给不同的函数进行处理
    action = request.params.get('action', None)
    responce = ''
    if action == 'list_customer':
        responce = ListCustomer(request)
    elif action == 'add_customer':
        responce = AddCustomer(request)
    elif action == 'modify_customer':
        responce = ModCustomer(request)
    elif action == 'del_customer':
        responce = DelCustomer(request)
    else:
        responce = JsonResponse({'ret': 1, 'msg': '不支持该类型的参数'})
    
    return responce

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