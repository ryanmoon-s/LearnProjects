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
    PID="$(pgrep -f ww_spam_svr:ww_spam_svr)"
done
echo "all process shotdown, begin to run ..."

# ulimit -n 50000
# buysms.wsgi为进程名
nohup gunicorn --config=./gunicorn_conf.py buysms.wsgi &> /dev/null &

echo "running success!"