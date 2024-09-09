#!/bin/bash

# build c++
printf "building for c++..."
(cd c++ ; ./build.sh > /dev/null 2>&1)
if [ $? -eq 0 ]; then
    printf " done.\n"
else
    printf " failed!\n"
    exit 1
fi

# build rust
printf "building for rust..."
(cd rust ; ./build.sh > /dev/null 2>&1)
if [ $? -eq 0 ]; then
    printf " done.\n"
else
    printf " failed!\n"
    exit 1
fi

# build go
printf "building for go..."
(cd go ; ./build.sh > /dev/null 2>&1)
if [ $? -eq 0 ]; then
    printf " done.\n"
else
    printf " failed!\n"
    exit 1
fi

# build java
printf "building for java..."
(cd java ; ./build.sh > /dev/null 2>&1)
if [ $? -eq 0 ]; then
    printf " done.\n"
else
    printf " failed!\n"
    exit 1
fi

# build c
printf "building for c..."
(cd c ; ./build.sh > /dev/null 2>&1)
if [ $? -eq 0 ]; then
    printf " done.\n"
else
    printf " failed!\n"
    exit 1
fi

# if we get this far, all builds succeeded and we're ready to run the apps
printf " ------------------------------|||c++ |||------------------------------\n"
(cd c++ ; ./run.sh)
printf " ------------------------------|||rust|||------------------------------\n"
(cd rust ; ./run.sh)
printf " ------------------------------||||go||||------------------------------\n"
(cd go ; ./run.sh)
printf " ------------------------------|||java|||------------------------------\n"
(cd java ; ./run.sh)
printf " ------------------------------||||c|||||------------------------------\n"
(cd c ; ./run.sh)
printf " ----------------------------------------------------------------------\n"
