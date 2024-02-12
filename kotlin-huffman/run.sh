#!/bin/bash

if [ ! -f app/build/libs/app.jar ]; then
    ./build.sh
fi

java -jar app/build/libs/app.jar -i "this is a sample input string. its text is being used to test the huffman coding tree."
