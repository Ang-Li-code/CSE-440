#!/bin/bash

# Function to compare version numbers
version_ge() {
  [ "$(printf '%s\n' "$2" "$1" | sort -V | head -n1)" = "$2" ]
}

# Check if Git is installed
if ! command -v git &> /dev/null; then
  echo "Error: Git is not installed."
  echo "Please install Git version 2.25.0 or newer."
  echo "On Ubuntu:"
  echo "  sudo add-apt-repository ppa:git-core/ppa"
  echo "  sudo apt update"
  echo "  sudo apt install git"
  echo "After installation, rerun this script."
  exit 1
fi

# Check Git version
GIT_VERSION=$(git --version | awk '{print $3}')
REQUIRED_VERSION="2.25.0"
if ! version_ge "$GIT_VERSION" "$REQUIRED_VERSION"; then
  echo "Error: Git version $GIT_VERSION is too old."
  echo "Please upgrade to Git version 2.25.0 or newer."
  echo "On Ubuntu:"
  echo "  sudo add-apt-repository ppa:git-core/ppa"
  echo "  sudo apt update"
  echo "  sudo apt install git"
  echo "After upgrading, rerun this script."
  exit 1
fi

# Create 3rdparty directory
mkdir -p 3rdparty
cd 3rdparty || exit 1

# Clone llvm-project if it doesn't already exist
if [ ! -d "llvm-project" ]; then
  echo "Cloning llvm-project..."
  git clone --filter=blob:none --single-branch --sparse https://github.com/llvm/llvm-project.git
else
  echo "llvm-project directory already exists, skipping clone."
fi

# Enter the llvm-project directory
cd llvm-project || exit 1

# Check if sparse checkouts are set

SPARSE_LIST=$(git sparse-checkout list 2>/dev/null | grep '^llvm$')

# llvm
if [ -z "$SPARSE_LIST" ]; then
  echo "Configuring sparse checkout for 'llvm'..."
  git sparse-checkout init --cone
  git sparse-checkout set llvm
else
  echo "Sparse checkout already includes 'llvm', skipping."
fi

# cmake
if ! echo "$SPARSE_LIST" | grep -q '^cmake$'; then
  echo "[INFO] Adding 'cmake' directory to sparse checkout..."
  git sparse-checkout add cmake
else
  echo "[INFO] 'cmake' already included."
fi

# third-party
if ! echo "$SPARSE_LIST" | grep -q '^third-party$'; then
  echo "[INFO] Adding 'third-party' directory to sparse checkout..."
  git sparse-checkout add third-party
else
  echo "[INFO] 'third-party' already included."
fi

echo "[SUCCESS] LLVM sparse checkout is ready."