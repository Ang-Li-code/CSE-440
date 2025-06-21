# CSE-440
A project among 5 friends to build a compiler using LLVM, named after the compiler design course that is no longer offered at our alma mater.

# Setup

## Prerequisites
- A working installation of **WSL** (Windows Subsystem for Linux) using an Ubuntu distribution (20.04 or later recommended)
- A terminal inside WSL with internet access
(This guide assumes a WSL + Ubuntu environment. You can adapt it to native Ubuntu or other Linux distributions, but some paths and dependencies may differ.)

### Step 0: Clone the Repository

1. Open a WSL terminal (Ubuntu)
2. Clone the repository and navigate to the `installation` folder:
   ```bash
   git clone https://github.com/Ang-Li-code/CSE-440.git
   cd CSE-440/installation
   ```

### Step 1: Install LLVM Locally

1. Open a WSL terminal (Ubuntu)
2. Nagivate to the "installation" directory
3. Make the install script executable:
   ```bash
   chmod +x install.sh
   ```
4. Run the script:
   ```bash
   ./install.sh
   ```
5. This will:
   - Install required packages
   - Download and extract LLVM 17.0.6 source code
   - Build and install LLVM and Clang to `~/llvm-install`
   - Configure environment variables in your `.bashrc`
   
### Step 2: Test LLVM with a Simple Program

1. Open a new WSL terminal (to pick up updated environment variables)
2. Navigate back to the installation directory:
   ```bash
   cd CSE-440/installation
   ```
3. Make the test script executable:
   ```bash
   chmod +x test.sh
   ```
4. Run the script:
   ```bash
   ./test.sh
   ```
5. If successful, you will see:
   ```bash
   Successfully created LLVM module!
   ```
