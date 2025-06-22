#!/bin/bash
set -e  # Exit on error
echo "=== [1/6] Installing dependencies..."
sudo apt update
sudo apt install -y build-essential cmake ninja-build git curl python3

echo "=== [2/6] Downloading LLVM 17.0.6 source..."
mkdir -p ~/llvm-src && cd ~/llvm-src

# Check if llvm-project directory already exists
if [ -d "llvm-project" ]; then
  echo "[INFO] LLVM source directory already exists, skipping download..."
else
  curl -LO https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.6/llvm-project-17.0.6.src.tar.xz
  tar -xf llvm-project-17.0.6.src.tar.xz
  mv llvm-project-17.0.6.src llvm-project
  echo "[INFO] LLVM source downloaded and extracted"
fi

echo "=== [3/6] Building LLVM with CMake + Ninja..."
mkdir -p ~/llvm-build && cd ~/llvm-build
cmake -G Ninja ../llvm-src/llvm-project/llvm \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX=$HOME/llvm-install \
  -DLLVM_TARGETS_TO_BUILD="X86" \
  -DLLVM_ENABLE_PROJECTS="clang" \
  -DLLVM_ENABLE_TERMINFO=OFF
echo "=== [4/6] Compiling LLVM (this may take a while)..."
if [ -n "$1" ]; then
  ninja -j$1
  ninja -j$1 install
else
  ninja
  ninja install
fi
echo "=== [5/6] Configuring environment variables..."
if ! grep -q "llvm-install" ~/.bashrc; then
  echo 'export PATH=$HOME/llvm-install/bin:$PATH' >> ~/.bashrc
  echo 'export LLVM_DIR=$HOME/llvm-install/lib/cmake/llvm' >> ~/.bashrc
  echo '[INFO] Added LLVM paths to ~/.bashrc'
else
  echo '[INFO] LLVM paths already in ~/.bashrc'
fi
echo "=== [6/6] Verifying LLVM installation..."
source ~/.bashrc
clang --version || echo "⚠️ clang not found"
llvm-config --version || echo "⚠️ llvm-config not found"
echo "✅ LLVM is now installed in ~/llvm-install"
