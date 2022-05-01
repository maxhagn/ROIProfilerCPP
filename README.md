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

+ Clang Getting Started: [https://clang.llvm.org/get_started.html](https://clang.llvm.org/get_started.html)
+ Clang Settup LLVM for LibTooling: [https://clang.llvm.org/docs/HowToSetupToolingForLLVM.html](https://clang.llvm.org/docs/HowToSetupToolingForLLVM.html)
+ LLVM Getting Started: [https://llvm.org/docs/GettingStarted.html](https://llvm.org/docs/GettingStarted.html)

## Requirements
The program has been extensively tested on Linux and macOS and is definitely usable on these operating systems. Windows could also work with tools like cygwin or Linux subkernels, but you have to expect the normal performance losses that result from developing on Windows.

To follow my recommended workflow the packages `CMAKE`, `GCC`, `Python`, `zlib`, `GNU Make`, `Ninja` are required. These can be installed under Linux with `apt-get` or under macOS with `brew`. The packages should be available under any other Linux distro without `apt-get` package manager (`pacman`, `yum`), just follow the developer's web pages.

| Instruction                                                             | Operating System                   |
|-------------------------------------------------------------------------|------------------------------------|
| `sudo apt-get install cmake gcc python ninja-build`                     | Linux                              |
| `brew install cmake gcc python ninja`                                   | macOS                              |

## Build LLVM and ROI Profiler

I worked exclusively with the `ninja` build system for the development. Other options can be found on the official LLVM page, but `ninja` is used by most LLVM developers.

###  Checkout, configure and build LLVM with Ninja
1. `git clone https://github.com/llvm/llvm-project.git`
2. `cd llvm-project`
3. `mkdir build`
4. `cd build`
5. `cmake -G Ninja ../llvm -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" -DLLVM_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release`
6. `ninja`

### Checkout, build and configure the ROI Profiler
1. `cd ../clang/tools`
2. `mkdir regionprofile`
3. `cd regionprofile`
4. `git clone https://github.com/maxhagn/ROIProfilerCPP.git`
5. Add ROI Profiler to CMakeLists.txt
   1. `cd ..`
   2. `vi CMakeLists.txt`
   3. Add line "add_clang_subdirectory(regionprofile)"
6. Build regionprofile
   1. `cd ../build`
   2. `ninja`

After the build is complete, a binary file called `roipc` should be found under `llvm-project/build/bin`. To use this binary globally you can either copy it to `/usr/bin` or export the path to the LLVM build directory. 

`export PATH=[pathToLLVMProject]/build/bin:$PATH`

## Workflow
### Synopsis
`roipc [options] <source0> [... <sourceN>]`

| Options                      | Description                                                      |
|------------------------------|------------------------------------------------------------------|
| `--help`                     | Display available options (--help-hidden for more)               |
| `--help-list`                | Display list of available options (--help-list-hidden for more)  |
| `--version`                  | Display the version of this program                              |
| `--extra-arg=<string>`       | Additional argument to append to the compiler command line       |
| `--extra-arg-before=<string>`| Additional argument to prepend to the compiler command line      |
| `-o=<output file>`           | Write transformed file to custom location                        |
| `-p=<string>`                | Build Path                                                       |
| `--stmt=<id of stmt>`        | Specifies the current traversal point                            |


### Example
Coming Soon

## Documentation
I plan to build a small website where the paper can be downloaded and the main idea, workflow and examples will be visualized. Furthermore, the Doxygen documentation will also be available. The offline version of the documentation is located in the `Documentation` directory in this repository.

Website (Coming Soon): [https://roiprofiler.hagn.network](https://roiprofiler.hagn.network) 


# Autor
Maximilian Hagn <br>
1220 Wien <br>
Austria

**Institution**<br>
Technical University of Vienna<br>
Technische Universität Wien<br>
1040 Wien
