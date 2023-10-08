from django.shortcuts import render
from django.http import HttpResponse
from studentdemo.models import Country, Student

def GetStudent(request):
    name = request.GET.get('name', None)
    if not name:
        return HttpResponse("param err")
    
    # 访问
    stu = Student.objects.get(name=name)
    # 访问外键字段
    stu_contry_name = stu.country.name
    res = str(stu) + "_" + stu_contry_name
    return HttpResponse(res)
    
def AddStudent(request):
    name = request.GET.get('name', None)
    grade = request.GET.get('grade', None)
    contry = request.GET.get('contry', None)
    if not name or not grade or not contry:
        return HttpResponse("param err")
    
    # 已经预先创建好：
    # python manage.py shell
    # from common.models import *
    # c1 = Country.objects.create(name='中国')
    # c2 = Country.objects.create(name='美国')
    # c3 = Country.objects.create(name='法国')
    
    # country__name=contry，自动关联到Contry表name字段为contry的记录上
    # 无需先查Contry表
    Student.objects.create(name=name, grade=grade, country__name=contry)
    