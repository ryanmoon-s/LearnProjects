from django.urls import path
from sales.views import *

urlpatterns = [
    path('orders/', listorders),
    path('orders1/', listorders1),
    path('orders2/', listorders2),
]