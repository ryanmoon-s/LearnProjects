from common.models import Customer
from django.http import JsonResponse
import json

def DispatcherBase(request, action2HandlerTable):
    # 校验登录状态，这个时候框架已经用前端带上来的sessionid取到了session data
    if 'usertype' not in request.session:
        print("no usertype in session")
        return JsonResponse({
            'ret': 302,
            'msg': '未登录',
            'redirect': '/mgr/sign.html'}, 
            status=302)

    if request.session['usertype'] != 'mgr':
        print("usertype err", request.session['usertype'])
        return JsonResponse({
            'ret': 302,
            'msg': '用户非mgr类型',
            'redirect': '/mgr/sign.html'} ,
            status=302)
    
    # 将请求参数统一放入request 的 params 属性中，方便后续处理
    # GET请求 参数在url中，同过request 对象的 GET属性获取
    if request.method == 'GET':
        request.params = request.GET
    # POST/PUT/DELETE 请求 参数 从 request 对象的 body 属性中获取
    elif request.method in ['POST','PUT','DELETE']:
        # 根据接口，POST/PUT/DELETE 请求的消息体都是 json格式
        request.params = json.loads(request.body)
    
    # 根据不同的action分派给不同的函数进行处理
    action = request.params.get('action', None)
    responce = ''

    if action in action2HandlerTable:
        handlerFunc = action2HandlerTable[action]
        responce = handlerFunc(request)
    
    return responce
