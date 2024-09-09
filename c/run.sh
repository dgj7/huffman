#!/bin/bash

if [ ! -f bin/huffman ]; then
    ./build.sh
fi

./bin/huffman -i "this is a sample input string. its text is being used to test the huffman coding tree."
