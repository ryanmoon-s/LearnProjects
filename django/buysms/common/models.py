from django.db import models
import datetime

class Customer(models.Model):
    name = models.CharField(max_length=50)
    phonenumber = models.CharField(max_length=50)
    address = models.CharField(max_length=300)
    
class Medicine(models.Model):
    # 药品名
    name = models.CharField(max_length=200)
    # 药品编号
    sn = models.CharField(max_length=200)
    # 描述
    desc = models.CharField(max_length=200)
    
class Order(models.Model):
    # 订单名
    name = models.CharField(max_length=200, null=True, blank=True)
    # 创建日期
    create_date = models.DateTimeField(default=datetime.datetime.now)
    # 客户 默认是NOT NULL
    customer_id = models.IntegerField()

# 关联Order和Medicine
class OrderMedicine(models.Model):
    order_id = models.IntegerField()
    medicine_id = models.IntegerField()
    
    # 订单中药品的数量
    amount = models.PositiveIntegerField()