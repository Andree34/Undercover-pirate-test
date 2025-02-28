#!/bin/bash

# feel free to keep some files to debug
cleanup() {
    rm -f pipe1 pipe2 E-sample.out E.out checker solution
}
trap cleanup EXIT

cd test
touch pipe1 pipe2 E-sample.out E.out
g++ -o checker E-Checker.cpp
g++ -o solution ../Undercover\ pirate.cpp

if [ $? -ne 0 ]; then
    echo "Solution doesn't compile"
    exit 1
fi

timeout 2s bash -c '
    tail -f pipe2 | ./solution > pipe1 &
    tail -f pipe1 | ./checker E-sample.in E-sample.out > pipe2
'

if [ $? -eq 124 ]; then
    echo "Timeout on samples"
    exit 1
fi

if diff -q E-sample.out E-sample-correct.out >/dev/null; then
    echo "Sample tests passed!"
else
    echo "Sample tests failed :("
    diff E-sample.out E-sample-correct.out
    exit 0
fi

> pipe1
> pipe2

timeout 2s bash -c '
    tail -f pipe2 | ./solution > pipe1 &
    tail -f pipe1 | ./checker E.in E.out > pipe2
'

if [ $? -eq 124 ]; then
    echo "Timeout on tests"
    exit 1
fi

if diff -q E.out E-correct.out >/dev/null; then
    echo "Tests passed!"
else
    echo "Tests failed :("
    diff E.out E-correct.out
fi