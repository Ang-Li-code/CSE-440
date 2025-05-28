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

cd llvm-project || exit 1

# Init sparse checkout if needed
if [ ! -d ".git/info/sparse-checkout" ] && [ ! -f ".git/info/sparse-checkout" ]; then
  git sparse-checkout init --cone
fi

# Get current sparse list
SPARSE_LIST=$(git sparse-checkout list 2>/dev/null)

# Ensure directories exist
add_sparse_dir() {
  local dir="$1"
  if ! echo "$SPARSE_LIST" | grep -qx "$dir"; then
    echo "[INFO] Adding '$dir' to sparse checkout..."
    git sparse-checkout add "$dir"
  else
    echo "[INFO] '$dir' already included."
  fi
}

REQUIRED_DIRS=(
  "llvm"
  "cmake"
  "third-party"
)

for dir in "${REQUIRED_DIRS[@]}"; do
  add_sparse_dir "$dir"
done

echo "[SUCCESS] LLVM sparse checkout is ready."