#!/bin/sh

# do some cmake-related cleaning things
rm -r CMakeFiles
rm CMakeCache.txt
rm cmake_install.cmake
rm Makefile

# build the huffman library
cmake .
make clean
make config=release

# copy things needed to build the test
cp bin/libhuffman.a test/libhuffman.a
cp src/Huffman.hpp test/Huffman.hpp

# build the test as well
(cd test ; ./build.sh)
