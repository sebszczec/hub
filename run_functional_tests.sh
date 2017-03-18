#!/bin/bash

TEST=""
SEED=0

function printHelp {
    echo "Functional Tests Framework"
    echo "-h|--help - prints help"
    echo "-l|--testlist - prints list of available tests"
    echo "-r|--random SEED - runs tests in random order with SEED"
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
    TEST="-t $2"
    shift # past argument
    ;;
    -r|--random)
    SEED="$2"
    shift # past argument
    ;;
    -h|--help)
    printHelp
    exit 0
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
valgrind --leak-check=full --show-reachable=yes --leak-resolution=high --num-callers=50 --trace-children=yes --xml=yes --xml-file=valgrind_result.xml ./hub &

echo "Giving ${DELAY} seconds for app to work"
sleep ${DELAY}

# dry run
./telnet.sh
echo ""

# functional tests
python functional_tests.py $TEST
RESULT=$?


PID=`cat hub.pid`
echo "Killing hub PID: ${PID}"
kill $PID

exit $RESULT
