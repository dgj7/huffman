#!/bin/bash

function do_build() {
    printf "building for $1..."
    (cd $1; ./build.sh > /dev/null 2>&1)
    if [ $? -eq 0 ]; then
    printf " done.\n"
    else
        printf " failed!\n"
        exit 1
    fi
}

do_build "c"
do_build "cpp"
do_build "rust"
do_build "go"
do_build "java"
