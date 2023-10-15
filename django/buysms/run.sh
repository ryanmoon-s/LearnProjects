#!/bin/bash

python3 manage.py runserver 0.0.0.0:8080

# DIR="$( cd "$( dirname "$0" )" && pwd )"
# echo $DIR

# cd $DIR

# # ulimit -n 50000
# nohup gunicorn --config=buysms/gunicorn_conf.py buysms.wsgi &> /dev/null &
