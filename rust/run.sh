#!/bin/bash

if [ ! -f target/debug/examples/test_program.exe ]; then
    #printf "building...\n"
    (./build.sh) > /dev/null 2>&1
fi
if [ ! -f target/debug/examples/test_program.exe ]; then
    printf "ERROR: lib build failed\n"
    exit 1
fi

./target/debug/examples/test_program -i "this is a sample input string. its text is being used to test the huffman coding tree."
