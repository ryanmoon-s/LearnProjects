from django.db import models

class Customer(models.Model):
    name = models.CharField(max_length=50)
    phonenumber = models.CharField(max_length=50)
    address = models.CharField(max_length=300)
    qq = models.CharField(max_length=50, null=True, blank=True)