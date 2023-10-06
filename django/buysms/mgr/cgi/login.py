from django.http import JsonResponse
from django.contrib.auth import authenticate, login, logout

PubErrResponse = {
    'param_err': {'ret':-2003, 'msg': 'param_err'}
}

def Login(request):    
    # 从 HTTP POST 请求中获取用户名、密码参数
    userName = request.POST.get('username')
    passWord = request.POST.get('password')
    print("Login", userName, passWord)
    
    if not userName or not passWord:
        print("param err", userName, passWord)
        return JsonResponse(PubErrResponse['param_err'])

    # 使用 Django auth 库里面的 方法校验用户名、密码
    user = authenticate(username=userName, password=passWord)
    
    if not user:
        return JsonResponse({'ret': -1, 'msg': '用户名或者密码错误'})
    
    if not user.is_active:
        return JsonResponse({'ret': -2, 'msg': '用户已经被禁用'})
    
    if not user.is_superuser:
        return JsonResponse({'ret': -3, 'msg': '请使用管理员账户登录'})
    
    # 1. 登录，更新登录时间、登录状态
    # 2. 生成sessionid-sessiondata存储到django_session表
    # 3. 回包的header里面加上Set-Cookie: sessionid=xxx
    login(request, user)
    # 1. 在django_session表中添加数据:sessionid:{usertype:mgr}
    request.session['usertype'] = 'mgr'
    print("Login succ", userName, passWord)
    
    return JsonResponse({'ret': 0})

def Logout(request):
    # 登出时，自动清除session
    logout(request)
    print("Logout succ", request.POST)
    return JsonResponse({'ret': 0})
