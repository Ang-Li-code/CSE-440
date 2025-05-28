# CSE-440
A project among 5 friends to build a compiler using LLVM, named after the compiler design course that is no longer offered at our alma mater.

# Building
1. Clone the repository: 

`git clone https://github.com/Ang-Li-code/CSE-440.git`

2. Run `./installer.sh` to install the llvm-project and only the directories required 

3. build llvm (requires CMake):

`cmake -S llvm -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo`
  - Feel free to modify these flags as described [in the llvm docs](https://llvm.org/docs/GettingStarted.html#getting-the-source-code-and-building-llvm)

`cd build`

`make -j<number-of-threads>` 

notes: 
  - The LLVM build requires about 45GB of free space
  - I recommend to use $\frac{1}{8}$ to $\frac{1}{2}$ of threads available on your system because building LLVM takes up a lot of memory and compute)
  - The error `c++: fatal error: Killed signal terminated program cc1plus` typically indicates that your system ran out of memory. Rerun with fewer threads and/or try restarting your pc to reset your memory cache.

3. Build language:

`TODO`

# Running
`TODO`