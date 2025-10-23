#!/bin/bash

# exit on errors
printf "setting exit on errors...\n"
set -e

# install go package(s)
printf "retrieving packages...\n"
go get github.com/stretchr/testify/assert

# clean compiled binaries
printf "cleaning...\n"
go clean

# run tests
printf "testing...\n"
go test gohuff/htree

# build
printf "building...\n"
go build

# declare victory
printf "success!\n"
