#!/bin/bash

if [ ! -f huffman-coding-lib/target/debug/libhuffman_coding_lib.rlib ]; then
    #printf "building lib...\n"
    (cd huffman-coding-lib; ./build_lib.sh) > /dev/null 2>&1
fi
if [ ! -f huffman-coding-lib/target/debug/libhuffman_coding_lib.rlib ]; then
    printf "ERROR: lib build failed\n"
    exit 1
fi

if [ ! -f test-program/target/debug/test-program ]; then
    #printf "building test program...\n"
    (cd test-program; ./build_test_program.sh) > /dev/null 2>&1
fi

if [ ! -f test-program/target/debug/test-program ]; then
    printf "ERROR: test program build failed\n"
    exit 2
fi

./test-program/target/debug/test-program -i "this is a sample input string. its text is being used to test the huffman coding tree."
