from django.http import JsonResponse
from django.db.models import F
from django.db import IntegrityError, transaction

# 导入 Order 对象定义
from  common.models import  Order, Medicine, OrderMedicine
from  common.models import  Customer

import json

def dispatcher(request):
    # 根据session判断用户是否是登录的管理员用户
    if 'usertype' not in request.session:
        return JsonResponse({
            'ret': 302,
            'msg': '未登录',
            'redirect': '/mgr/sign.html'},
            status=302)

    if request.session['usertype'] != 'mgr':
        return JsonResponse({
            'ret': 302,
            'msg': '用户非mgr类型',
            'redirect': '/mgr/sign.html'},
            status=302)


    # 将请求参数统一放入request 的 params 属性中，方便后续处理

    # GET请求 参数 在 request 对象的 GET属性中
    if request.method == 'GET':
        request.params = request.GET

    # POST/PUT/DELETE 请求 参数 从 request 对象的 body 属性中获取
    elif request.method in ['POST','PUT','DELETE']:
        # 根据接口，POST/PUT/DELETE 请求的消息体都是 json格式
        request.params = json.loads(request.body)

    # 根据不同的action分派给不同的函数进行处理
    action = request.params['action']
    if action == 'list_order':
        return ListOrder(request)
    elif action == 'add_order':
        return AddOrder(request)

    # 订单 暂 不支持修改 和删除

    else:
        return JsonResponse({'ret': 1, 'msg': '不支持该类型http请求'})

def AddOrder(request):

    info  = request.params['data']

    # 从请求消息中 获取要添加订单的信息
    # 并且插入到数据库中
    
    # 事务 with是一种RAII应用，失败时自动回滚
    with transaction.atomic():
        new_order = Order.objects.create(name=info['name'] ,
                                         customer_id=info['customerid'])

        # 同一个order_id关联多个药品
        batch_lst = [OrderMedicine(order_id=new_order.id, medicine_id=mid, amount=1)  
                    for mid in info['medicineids']]

        #  在多对多关系表中 添加了 多条关联记录
        OrderMedicine.objects.bulk_create(batch_lst)

    return JsonResponse({'ret': 0,'id':new_order.id})

def ListOrder(request):
    '''
    [
        {
            id: 1, 
            name: "华山医院订单001", 
            create_date: "2018-12-26T14:10:15.419Z",
            customer_name: "华山医院",
            names: "青霉素"
        },
        {
            id: 2, 
            name: "华山医院订单002", 
            create_date: "2018-12-27T14:10:37.208Z",
            customer_name: "华山医院",
            names: "青霉素 | 红霉素 "
        }
    ] 
    '''
    
    # objects.values()返回的是: [{}]
    # objects.all(), get(), filter() 返回的是class对象
    res_lst = []
    for order in Order.objects.all():
        customer = Customer.objects.get(id=order.customer_id)
        names = ''
        for order_medicine in OrderMedicine.objects.filter(order_id=order.id):
            medicine = Medicine.objects.get(id=order_medicine.medicine_id)
            if len(names) != 0:
                names += ' | '
            names += medicine.name
        res_lst.append({'id':order.id, 'name':order.name, 'create_date':order.create_date, 'customer_name':customer.name, 'names':names})

    return JsonResponse({'ret': 0, 'retlist': res_lst})