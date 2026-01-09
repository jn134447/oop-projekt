#!/usr/bin/env bash
cmake -B build -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw64.cmake
cmake --build build
wine build/hello.exe
