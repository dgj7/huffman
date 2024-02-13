#!/bin/bash

if [ ! -f go-huffman ]; then
    ./build.sh
fi

./go-huffman -i "this is a sample input string. its text is being used to test the huffman coding tree."