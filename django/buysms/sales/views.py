from django.shortcuts import render
from django.http import HttpResponse
from common.models import  Customer

def GetCustomers(request):
    # 返回一个 QuerySet 对象 ，包含所有的表记录
    # 每条表记录都是是一个dict对象，
    # key 是字段名，value 是 字段值
    qs = Customer.objects.values()
    
    result = ''
    for customer in qs:
        for key, value in customer.items():
            result += f"key:{key}, value:{value} | "
        result += "<br>"
    
    return HttpResponse(result)