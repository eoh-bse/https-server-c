#!/usr/bin/env bash

build_type=Debug
if [ -n "$1" ]; then
	build_type=$1
fi

cmake -DCMAKE_C_COMPILER=clang\
	-DCMAKE_BUILD_TYPE=$build_type\
	-DCMAKE_EXPORT_COMPILE_COMMANDS=ON\
	-S . -B ./build
