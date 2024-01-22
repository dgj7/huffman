#!/bin/sh

# do some cmake-related cleaning things
rm -r CMakeFiles
rm CMakeCache.txt
rm cmake_install.cmake
rm Makefile
rm bin/huffman
rm bin/libhuffman.a

# build the huffman library
cmake .
make clean
make config=release

# build the test as well
(cd src ; g++ -o ../bin/huffman main.cpp -L../bin -lhuffman)
