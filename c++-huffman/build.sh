#!/bin/sh

rm -r CMakeFiles
rm CMakeCache.txt
rm cmake_install.cmake
rm Makefile

cmake .
make clean
make config=release

cp bin/libhuffman.a test/libhuffman.a
cp src/Huffman.hpp test/Huffman.hpp
