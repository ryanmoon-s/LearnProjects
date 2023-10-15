from django.http import JsonResponse
from django.db.models import Q
from django.core.paginator import Paginator
import json

from  common.models import  Medicine
from mgr.cgi import handler

def listmedicine(request):
    # .order_by('-id') 表示按照 id字段的值 倒序排列
    # 这样可以保证最新的记录显示在最前面
    qs = Medicine.objects.values().order_by('-id')
    
    # 查看是否有 关键字 搜索 参数
    keywords = request.params.get('keywords', None)
    if keywords:
        conditions = [Q(name__contains=one) for one in keywords.split(' ') if one]
        query = Q()
        for condition in conditions:
            query &= condition
        qs = qs.filter(query)

    pagenum = request.params['pagenum']
    pagesize = request.params['pagesize']
 
    paginator = Paginator(qs, pagesize)
    page = paginator.page(pagenum)
    
    retlist = list(page)

    return JsonResponse({'ret': 0, 'retlist': retlist, 'total':paginator.count})


def addmedicine(request):

    info    = request.params['data']

    # 从请求消息中 获取要添加客户的信息
    # 并且插入到数据库中
    medicine = Medicine.objects.create(name=info['name'] ,
                            sn=info['sn'] ,
                            desc=info['desc'])


    return JsonResponse({'ret': 0, 'id':medicine.id})


def modifymedicine(request):

    # 从请求消息中 获取修改客户的信息
    # 找到该客户，并且进行修改操作

    medicineid = request.params['id']
    newdata    = request.params['newdata']

    try:
        # 根据 id 从数据库中找到相应的客户记录
        medicine = Medicine.objects.get(id=medicineid)
    except Medicine.DoesNotExist:
        return  {
                'ret': 1,
                'msg': f'id 为`{medicineid}`的药品不存在'
        }


    if 'name' in  newdata:
        medicine.name = newdata['name']
    if 'sn' in  newdata:
        medicine.sn = newdata['sn']
    if 'desc' in  newdata:
        medicine.desc = newdata['desc']

    # 注意，一定要执行save才能将修改信息保存到数据库
    medicine.save()

    return JsonResponse({'ret': 0})


def deletemedicine(request):

    medicineid = request.params['id']

    try:
        # 根据 id 从数据库中找到相应的药品记录
        medicine = Medicine.objects.get(id=medicineid)
    except Medicine.DoesNotExist:
        return  {
                'ret': 1,
                'msg': f'id 为`{medicineid}`的药品不存在'
        }

    # delete 方法就将该记录从数据库中删除了
    medicine.delete()

    return JsonResponse({'ret': 0})


Action2Handler = {
    'list_medicine': listmedicine,
    'add_medicine': addmedicine,
    'modify_medicine': modifymedicine,
    'del_medicine': deletemedicine,
}

def Dispatcher(request):
    return handler.DispatcherBase(request, Action2Handler)
