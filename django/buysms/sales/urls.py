from django.urls import path
from sales.views import *

urlpatterns = [
    path('customers', GetCustomers),
]