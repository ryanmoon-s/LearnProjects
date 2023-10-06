from django.contrib import admin
from django.urls import path, include
from mgr.cgi import customer

urlpatterns = [
    path('customers', customer.Dispatcher),
]
