#!/bin/bash

DELAY=2

echo "Starting Valgrind"
valgrind --leak-check=full --show-reachable=yes --leak-resolution=high --num-callers=50 --trace-children=yes --xml=yes --xml-file=valgrind_result.xml ./hub &

echo "Giving ${DELAY} seconds for app to work"
sleep ${DELAY}

for i in {1..5}
do
    echo "Running telnet.sh script ${i}"
    ./telnet.sh
done

PID=`cat hub.pid`
echo "Killing hub PID: ${PID}"
kill $PID
