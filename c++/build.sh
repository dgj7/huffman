#!/bin/sh

# clean
rm -r CMakeFiles
rm CMakeCache.txt
rm cmake_install.cmake
rm Makefile
rm bin/huffman
rm bin/libhuffman.a

# generate makefile
cmake .

# build the huffman library, `libhuffman.a`
make clean
make config=release

# build a test program `huffman`, linking to `libhuffman.a`
(cd src ; g++ -o ../bin/huffman main.cpp -L../bin -lhuffman)
