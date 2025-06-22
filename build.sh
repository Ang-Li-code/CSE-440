#!/bin/bash

mkdir -p bin/
cd bin
echo "building"
~/llvm-install/bin/clang++ -std=c++2c -I~/llvm-src/llvm-project/llvm/include -g -O3 ../language/language.cpp `~/llvm-build/bin/llvm-config --cxxflags --ldflags --system-libs --libs core` -o language