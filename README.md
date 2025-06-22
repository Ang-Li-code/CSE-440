# CSE-440
A project among 5 friends to build a compiler using LLVM, named after the compiler design course that is no longer offered at our alma mater.

# Setup

## Prerequisites
- A working installation of **WSL** (Windows Subsystem for Linux) using an Ubuntu distribution (20.04 or later recommended)
- A terminal inside WSL with internet access

(This guide assumes a WSL + Ubuntu environment. You can adapt it to native Ubuntu or other Linux distributions, but some paths and dependencies may differ.)

### Step 0: Clone the Repository

1. Open your favorite terminal
2. Clone the repository with:
   ```bash
   git clone https://github.com/Ang-Li-code/CSE-440.git
   cd CSE-440
   ```

### Step 1: Install LLVM Locally

1. Open your favorite terminal, if it's not already open
2. Run the install script:
   ```bash
   ./install.sh [num]
   ```
   - Optionally pass in a number for the cores to be used ($<25$% of your CPU cores is recommeneded). By default ninja will use as many resources as they see fit, however this can sometimes take up too much RAM and terminate compilation.
3. This will:
   - Install required packages
   - Download and extract LLVM 17.0.6 source code
   - Build and install LLVM and Clang to `~/llvm-install`
   - Configure environment variables in your `.bashrc`
   
### Step 2: Test LLVM with a Simple Program

1. Open a new terminal instance (to pick up updated environment variables)
2. Navigate back to the tests directory:
   ```bash
   cd CSE-440/tests
   ```
3. Run the sample program script (this will create a test file, and link with llvm to ensure everything is working):
   ```bash
   ./sampleProgram.sh
   ```
4. If successful, you will see:
   ```bash
   Successfully created LLVM module!
   ```
