#!/bin/sh

rm -r CMakeFiles
rm CMakeCache.txt
rm cmake_install.cmake
rm Makefile

cmake .
make clean
make config=release

rm -r CMakeFiles
rm CMakeCache.txt
rm cmake_install.cmake
rm Makefile
