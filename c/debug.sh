#!/bin/bash

###############################################################################
# debug the program.
#
# step: `s` or `step`: run the next line
# step over: `n` or `next`: run the entire next function
# continue: `c` or `continue`: finish the program
#
# `print x` and `set x` allow you to view/update variables.
#
# more info: https://web.eecs.umich.edu/~sugih/pointers/gdbQS.html
###############################################################################

if [ ! -f target/ex1.exe ]; then
    ./build.sh
fi

gdb -ex 'break encode' --args target/ex1.exe -i "this is a sample input string. its text is being used to test the huffman coding tree."