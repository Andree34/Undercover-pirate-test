#!/bin/bash

g++ -o test/checker test/E-Checker.cpp
g++ -o test/solution Undercover\ pirate.cpp

cd test
touch pipe1 pipe2 E-sample.out E.out

tail -f pipe2 | ./solution > pipe1 &
tail -f pipe1 | ./checker E-sample.in E-sample.out > pipe2

if diff -q E-sample.out E-sample-correct.out >/dev/null; then
    echo "Sample tests passed!"
else
    echo "Sample tests failed :("
    diff E-sample.out E-sample-correct.out
fi

> pipe1
> pipe2

tail -f pipe2 | ./solution > pipe1 &
tail -f pipe1 | ./checker E.in E.out > pipe2

if diff -q E.out E-correct.out >/dev/null; then
    echo "Tests passed!"
else
    echo "Tests failed :("
    diff E.out E-correct.out
fi

# feel free to keep some files to debug
rm pipe1 pipe2 E-sample.out E.out checker solution