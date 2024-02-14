#!/bin/bash

if [ ! -f gohuff ]; then
    ./build.sh
fi

./gohuff -i "this is a sample input string. its text is being used to test the huffman coding tree."
