# Introduction
This tool transforms C++ code by adding performance counter dynamically to the source file.
Functions and statements are traversed in the Clang AST and annotated if necessary. If 
--stmt option is not specified the program annotates the first level. The --stmt option can
be used to specify a function or bundle of statements as traversal entry point. 
The output file is written to output.cpp or to the file specified with the -o option.
The program takes .cpp oder .cxx file as input.

The Tool is build with Clang LibTooling library. LibTooling is a library to support writing standalone tools based on Clang. \
Further Information: https://clang.llvm.org/docs/LibTooling.html

# Installation Guide
This section explains how to build the LLVM source. More information is available on the official Clang or LLVM page.

Clang Getting Started: [https://clang.llvm.org/get_started.html](https://clang.llvm.org/get_started.html)
LLVM Getting Started: [https://llvm.org/docs/GettingStarted.html](https://llvm.org/docs/GettingStarted.html)


## Requirements
The program has been extensively tested on Linux and macOS and is definitely usable on these operating systems. Windows could also work with tools like cygwin or Linux subkernels, but you have to expect the normal performance losses that result from developing on Windows.

To follow my recommended workflow the packages `CMAKE`, `GCC`, `Python`, `zlib`, `GNU Make`, `Ninja` are required. These can be installed under Linux with `apt-get` or under macOS with `brew`:

| Instruction                                                             | Operating System                   |
|-------------------------------------------------------------------------|------------------------------------|
| `sudo apt-get install cmake gcc python ninja-build                      | Linux with apt-get Package Manager | 
| `brew install cmake gcc python ninja`                                   | macOS                              |



1. Install Requirements: CMAKE, GCC, Python, zlib, GNU Make, Ninja
2. Checkout, configure and build LLVM with Ninja
   1. Checkout LLVM: git clone https://github.com/llvm/llvm-project.git
   2. cd llvm-project
   3. mkdir build
   4. cd build
   5. cmake -G Ninja ../llvm -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" -DLLVM_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release
   6. ninja
3. Checkout ROIProfilerCPP
   1. cd ../clang/tools
   2. mkdir regionprofile
   3. cd regionprofile
   4. git clone https://github.com/maxhagn/ROIProfilerCPP.git
4. Add hagn-tool to CMakeLists.txt
   1. cd ..
   2. vi CMakeLists.txt
   3. Add line "add_clang_subdirectory(regionprofile)"
5. Build regionprofile
   1. cd ../build 
   2. ninja

Further information for LLVM and Clang installation:
* LLVM Installation: https://llvm.org/docs/GettingStarted.html
* Clang Installation: https://clang.llvm.org/get_started.html
* Clang Lib Tooling: https://clang.llvm.org/docs/HowToSetupToolingForLLVM.html

# Author
Technical University Vienna

Maximilian Hagn <br />
Brausewettergasse 16 / TOP 3 <br />
1220 Wien <br />
Austria

# Caveat
This documentation is generated directly from the source code with doxygen. Since my clang libtool is constantly under active development, what you're about to read is out of date!
