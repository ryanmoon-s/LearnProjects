from django.contrib import admin
from django.urls import path, include
from mgr.cgi import customer, login, medicine

urlpatterns = [
    path('customers', customer.Dispatcher),
    path('medicines', medicine.dispatcher),
    path('signin', login.Login),
    path('signout', login.Logout),
]
