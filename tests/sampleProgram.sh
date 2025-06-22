#!/bin/bash

set -e  # Exit if anything fails

echo "=== [1/4] Creating test project folder..."
mkdir -p ~/llvm-test && cd ~/llvm-test


echo "=== [2/4] Writing main.cpp..."
cat > main.cpp <<EOF
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <iostream>

int main() {
    llvm::LLVMContext context;
    llvm::Module module("my cool jit", context);
    llvm::IRBuilder<> builder(context);

    std::cout << "Successfully created LLVM module!" << std::endl;
    return 0;
}
EOF

echo "=== [3/4] Compile and link with llvm"
# Compile
~/llvm-install/bin/clang++ -I~/llvm-src/llvm-project/llvm/include -g -O3 main.cpp `~/llvm-build/bin/llvm-config --cxxflags --ldflags --system-libs --libs core` -o main.exe

echo "=== [4/4] Running the test binary..."
./main.exe
