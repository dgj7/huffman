#!/bin/bash

# build c++-huffman
printf "building c++-huffman..."
(cd c++-huffman ; ./build.sh > /dev/null 2>&1)
if [ $? -eq 0 ]; then
    printf " done.\n"
else
    printf " failed!\n"
    exit 1
fi

# build rust-huffman
printf "building rust-huffman..."
(cd rust-huffman ; ./build.sh > /dev/null 2>&1)
if [ $? -eq 0 ]; then
    printf " done.\n"
else
    printf " failed!\n"
    exit 1
fi

# build go-huffman
printf "building go-huffman..."
(cd go-huffman ; ./build.sh > /dev/null 2>&1)
if [ $? -eq 0 ]; then
    printf " done.\n"
else
    printf " failed!\n"
    exit 1
fi

# build java-huffman
printf "building java-huffman..."
(cd java-huffman ; ./build.sh > /dev/null 2>&1)
if [ $? -eq 0 ]; then
    printf " done.\n"
else
    printf " failed!\n"
    exit 1
fi

# if we get this far, all builds succeeded and we're ready to run the apps
printf " ------------------------------|||c++ |||------------------------------\n"
(cd c++-huffman ; ./run.sh)
printf " ------------------------------|||rust|||------------------------------\n"
(cd rust-huffman ; ./run.sh)
printf " ------------------------------||||go||||------------------------------\n"
(cd go-huffman ; ./run.sh)
printf " ------------------------------|||java|||------------------------------\n"
(cd java-huffman ; ./run.sh)
printf " ----------------------------------------------------------------------\n"
