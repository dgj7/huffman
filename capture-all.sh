#!/bin/bash

function do_capture() {
    printf "capturing for $1..."
    (cd $1; ./run.sh > ../.testall/$1.txt)
    if [ $? -eq 0 ]; then
        printf " done.\n"
    else
        printf " failed!\n"
        exit 1
    fi
}

do_capture "c"
do_capture "cpp"
do_capture "rust"
do_capture "go"
do_capture "java"
