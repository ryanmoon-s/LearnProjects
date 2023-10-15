#!/bin/bash

PID="$(pgrep -f buysms.wsgi)"
if [[ -n PID ]]; then
    kill $PID
fi

echo "waiting process shutdown ..."
while [[ -n "$PID" ]]
do
    PID="$(pgrep -f ww_spam_svr:ww_spam_svr)"
done
echo "all process shotdown"