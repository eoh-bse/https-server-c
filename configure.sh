#!/usr/bin/env bash

build_type=Debug
if [[ -n "$BUILD_TYPE" ]]; then
	build_type=$BUILD_TYPE
fi

cmake -DCMAKE_C_COMPILER=clang\
	-DCMAKE_BUILD_TYPE=$build_type\
	-DCMAKE_EXPORT_COMPILE_COMMANDS=ON\
	-S . -B ./build
