from django.urls import path
from studentdemo.views import GetStudent, AddStudent

urlpatterns = [
    path('get_stu', GetStudent),
    path('add_stu', AddStudent),
]