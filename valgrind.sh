#!/bin/bash

DELAY=2

echo "Starting Valgrind"
valgrind --leak-check=full --xml=yes --xml-file=valgrind_result.xml ./hub &

echo "Giving ${DELAY} seconds for app to work"
sleep ${DELAY}

PID=`cat hub.pid`
echo "Killing hub PID: ${PID}"
kill $PID
