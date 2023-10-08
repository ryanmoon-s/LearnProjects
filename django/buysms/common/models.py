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
    # 客户
    ''' 
    1、一对多
    2、on_delete，当删除Customer表中一条记录时：
        CASCADE 删除主键记录和相应的外键表记录
        PROTECT 禁止删除记录
        SET_NULL 删除主键记录，并且将外键记录中外键字段的值置为null。前提是外键字段要设置为值允许是null
    3、字段名customer实际被拼接为：customer_id
    4、一对一是这个：models.OneToOneField(Customer)
    '''
    customer = models.ForeignKey(Customer, on_delete=models.PROTECT)
    
    # 订单购买的药品，和Medicine表是多对多的关系
    # through: 通过OrderMedicine表来实现多对多
    # medicines = models.ManyToManyField(Medicine, through='OrderMedicine')

class OrderMedicine(models.Model):
    order = models.ForeignKey(Order, on_delete=models.PROTECT)
    medicine = models.ForeignKey(Medicine, on_delete=models.PROTECT)

    # 订单中药品的数量
    amount = models.PositiveIntegerField()