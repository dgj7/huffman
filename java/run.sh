#!/bin/bash

if [ ! -f target/jhtree-0.0.1-SNAPSHOT-jar-with-dependencies.jar ]; then
    ./build.sh
fi

java -jar target/jhtree-0.0.1-SNAPSHOT-jar-with-dependencies.jar -i "this is a sample input string. its text is being used to test the huffman coding tree."
