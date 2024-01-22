cmake_minimum_required(VERSION 3.5.1)
project(huffman)

set(CMAKE_BUILD_TYPE Release)
set(LIBRARY_OUTPUT_PATH "bin/")

include_directories(src)
file(GLOB_RECURSE SOURCES "src/lib/*.cpp")

add_library(huffman STATIC ${SOURCES})
