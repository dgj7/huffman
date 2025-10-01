#!/bin/bash

if [ ! -f target/ex1.exe ]; then
    ./build.sh
fi

./target/ex1.exe -i "this is a sample input string. its text is being used to test the huffman coding tree."

