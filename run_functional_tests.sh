#!/bin/bash

ARGS=""

function printHelp {
    echo "Functional Tests Framework"
    echo "-h|--help - prints help"
    echo "-l|--testlist - prints list of available tests"
    echo "-r|--random SEED - runs tests in random order with SEED (SEED==0 will generate SEED)"
    echo "-t|--test test_name - runs test_name"
}

while [[ $# -eq 1 ]]
do
key="$1"

case $key in
    -l|--testlist)
    python functional_tests.py -l 
    ;;
    -h|--help)
    printHelp
    ;;
    *)
    echo "Unknown argument $key or missing value"
    exit 1
    ;;
esac
exit 0
done

while [[ $# -gt 1 ]]
do
key="$1"

case $key in
    -t|--test)
    ARGS="-t $2"
    break
    ;;
    -r|--random)
    ARGS="-r $2"
    break
    ;;
    *)
    echo "Unknown argument $key"
    exit 1
    ;;
esac
shift # past argument or value
done

DELAY=2

echo "Starting Valgrind"
valgrind --leak-check=full --show-reachable=yes --leak-resolution=high --num-callers=50 --trace-children=yes --xml=yes --xml-file=valgrind_ft_result.xml ./hub &

echo "Giving ${DELAY} seconds for app to work"
sleep ${DELAY}

# functional tests
echo $ARGS
python functional_tests.py $ARGS
RESULT=$?


PID=`cat hub.pid`
echo "Killing hub PID: ${PID}"
kill $PID

exit $RESULT
