#!/bin/bash

# python3 manage.py runserver 0.0.0.0:8080

# 已经存在进程则kill掉
PID="$(pgrep -f buysms.wsgi)"
if [[ -n PID ]]; then
    kill $PID
fi

echo "waiting process shutdown ..."
while [[ -n "$PID" ]]
do
    PID="$(pgrep -f buysms.wsgi)"
done
echo "all process shotdown, begin to run ..."

# ulimit -n 50000
# buysms.wsgi为django应用的路径，gunicorn会创建django应用来处理请求
# 同时也作为进程名
nohup gunicorn --config=./gunicorn_conf.py buysms.wsgi &> /dev/null &

echo "running success!"