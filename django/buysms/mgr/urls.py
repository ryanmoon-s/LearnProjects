from django.contrib import admin
from django.urls import path, include
from mgr.cgi import customer, login

urlpatterns = [
    path('customers', customer.Dispatcher),
    path('signin', login.Login),
    path('signout', login.Logout),
]
