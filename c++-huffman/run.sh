#!/bin/bash

if [ ! -f bin/huffman ]; then
    ./build.sh
fi

./bin/huffman

