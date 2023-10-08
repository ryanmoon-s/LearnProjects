from django.db import models

# 国家表
class Country(models.Model):
    name = models.CharField(max_length=100)

# 学生表， country 字段是国家表的外键，形成一对多的关系
class Student(models.Model):
    name = models.CharField(max_length=100)
    grade = models.PositiveSmallIntegerField()
    country = models.ForeignKey(Country, 
                                on_delete=models.PROTECT,
                                # 指定反向访问的名字
                                related_name='students')