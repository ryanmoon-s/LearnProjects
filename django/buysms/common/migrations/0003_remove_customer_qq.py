# Generated by Django 3.2.22 on 2023-10-07 14:26

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('common', '0002_customer_qq'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='customer',
            name='qq',
        ),
    ]
