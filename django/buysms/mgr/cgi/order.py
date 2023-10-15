from django.http import JsonResponse
from django.db import IntegrityError, transaction
from django.core.paginator import Paginator

from common.models import  Customer, Order, Medicine, OrderMedicine
from mgr.cgi import handler

import json

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
    {
        "id": 2, 
        "name": "华山医院订单002", 
        "create_date": "2018-12-27T14:10:37.208Z", 
        "customer_name": "华山医院",
        "medicinelist":[
            {"id":16,"amount":5,"name":"环丙沙星"},
            {"id":15,"amount":5,"name":"克林霉素"}
        ]
    }
    '''

    # objects.values()返回的是: [{}]
    # objects.all(), get(), filter() 返回的是class对象
    
    pagenum = request.params['pagenum']
    pagesize = request.params['pagesize']
    
    order_list = Order.objects.all()
    pgtr = Paginator(order_list, pagesize)
    page = pgtr.get_page(pagenum)
    
    res_lst = []
    for order in page:
        customer = Customer.objects.get(id=order.customer_id)
        medicinelist = []
        for order_medicine in OrderMedicine.objects.filter(order_id=order.id):
            medicine = Medicine.objects.get(id=order_medicine.medicine_id)
            medicinelist.append({"id":medicine.id, 'amount':order_medicine.amount, 'name':medicine.name})
        res_lst.append({'id':order.id, 'name':order.name, 'create_date':order.create_date, 'customer_name':customer.name, 'medicinelist':medicinelist})

    return JsonResponse({'ret': 0, 'retlist': res_lst})

def DeleteOrder(request):
    oid = request.params['id']

    try:
        one = Order.objects.get(id=oid)
        with transaction.atomic():
            # 一定要先删除 OrderMedicine 里面的记录
            OrderMedicine.objects.filter(order_id=oid).delete()
            # 再删除订单记录
            one.delete()
        return JsonResponse({'ret': 0, 'id': oid})

    except Order.DoesNotExist:
        return JsonResponse({
            'ret': 1,
            'msg': f'id 为`{oid}`的订单不存在'
        })

    except:
        err = traceback.format_exc()
        return JsonResponse({'ret': 1, 'msg': err})

Action2Handler = {
    'list_order': ListOrder,
    'add_order': AddOrder,
    'delete_order': DeleteOrder
}

def Dispatcher(request):
    return handler.DispatcherBase(request, Action2Handler)
