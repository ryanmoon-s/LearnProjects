from django.contrib import admin
from django.urls import path, include
from mgr.cgi import customer, login, medicine, order

urlpatterns = [
    path('customers', customer.Dispatcher),
    path('medicines', medicine.dispatcher),
    path('orders', order.dispatcher),
    
    path('signin', login.Login),
    path('signout', login.Logout),
]
