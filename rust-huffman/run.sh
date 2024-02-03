#!/bin/bash

if [ ! -f target/debug/rust-huffman ]; then
    ./build.sh
fi

./target/debug/rust-huffman -i "this is a sample input string. its text is being used to test the huffman coding tree."
