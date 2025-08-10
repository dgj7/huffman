#!/bin/bash

cargo test > /dev/null 2>&1
if [ $? -ne 0 ]; then
  printf "ERROR: lib tests failed\n"
  exit $?
fi

cargo test --examples > /dev/null 2>&1
if [ $? -ne 0 ]; then
  printf "ERROR: test_program tests failed\n"
  exit $?
fi

if [ ! -f target/debug/examples/test_program ]; then
    #printf "building...\n"
    (./build.sh) > /dev/null 2>&1
fi
if [ ! -f target/debug/examples/test_program ]; then
    printf "ERROR: lib build failed\n"
    exit 1
fi

./target/debug/examples/test_program -i "this is a sample input string. its text is being used to test the huffman coding tree."
