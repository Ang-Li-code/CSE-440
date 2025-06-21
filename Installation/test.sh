#!/bin/bash

set -e  # Exit if anything fails

echo "=== [1/5] Creating test project folder..."
mkdir -p ~/llvm-test && cd ~/llvm-test

echo "=== [2/5] Writing CMakeLists.txt..."
cat > CMakeLists.txt <<EOF
cmake_minimum_required(VERSION 3.13)
project(LLVMHello)

find_package(LLVM REQUIRED CONFIG)

include_directories(\${LLVM_INCLUDE_DIRS})
add_definitions(\${LLVM_DEFINITIONS})

add_executable(main main.cpp)

target_link_libraries(main
  PRIVATE
  LLVMCore
  LLVMIRReader
)
EOF

echo "=== [3/5] Writing main.cpp..."
cat > main.cpp <<EOF
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include <iostream>

int main() {
    llvm::LLVMContext context;
    llvm::Module module("my cool jit", context);
    llvm::IRBuilder<> builder(context);

    std::cout << "Successfully created LLVM module!" << std::endl;
    return 0;
}
EOF

echo "=== [4/5] Building project with CMake + Ninja..."
mkdir -p build && cd build
cmake .. -G Ninja
ninja

echo "=== [5/5] Running the test binary..."
./main
