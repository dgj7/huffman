#!/bin/bash

if [ ! -f target/debug/test-program ]; then
    ./build.sh
fi

./target/debug/test-program -i "this is a sample input string. its text is being used to test the huffman coding tree."
