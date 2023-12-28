<small>**🚀 Explore my digital universe: [maximilian.hagn.network](https://maximilian.hagn.network)!</small>**

# Regions Of Interest Profiler (1. BSc Thesis)

![Thumbnail](https://files.hagn.network/images/regions-of-interest-profiler/thumbnail.webp)

A tool from my bachelor thesis 'Identifying Performance Bottlenecks through AST Transformations,' designed to insert performance counters into C++ code for bottleneck analysis, developed using Clang's LibTooling library.


---
Ein in meiner Bachelorarbeit 'Erkennen von Leistungsengpässen durch AST-Transformationen' entwickeltes Tool, das C++-Code mittels Clangs LibTooling-Bibliothek analysiert und Leistungszähler zur Engpassanalyse einfügt.

## Key Facts

- University Low Level Development Project
- 35 Workdays
- Language: English
- Team Size: 2

### Roles

- Software Engineer

## Project Goals

The project aimed to develop a tool for dynamic transformation of C++ code by inserting performance counters into the source file. Utilizing the Clang LibTooling library, the tool was designed to traverse and annotate functions and statements within the Clang AST as needed. It featured options for specifying traversal entry points and customizing output file locations. This tool was intended to facilitate detailed performance analysis in C++ code development.


---
Ziel des Projekts war die Entwicklung eines Tools zur dynamischen Transformation von C++-Code, indem Leistungsindikatoren in die Quelldatei eingefügt wurden. Unter Verwendung der Clang LibTooling-Bibliothek war das Tool so konzipiert, dass es Funktionen und Anweisungen im Clang AST bei Bedarf durchläuft und annotiert. Es bot Optionen zur Spezifizierung von Traversierungseinstiegspunkten und zur Anpassung der Ausgabedatei-Orte. Dieses Tool sollte eine detaillierte Leistungsanalyse in der C++-Codeentwicklung erleichtern.

## Experience

In this project, my primary focus was on developing the ROIProfiler, a sophisticated tool for C++ code analysis. Using the Clang LibTooling library, I successfully built a system for dynamically inserting performance counters into C++ source files. My responsibilities included traversing and annotating functions and statements within the Clang AST, setting up various options for traversal entry points, and customizing output file locations. The experience honed my skills in C++ code analysis and optimization, and deepened my understanding of performance evaluation in software development.


---
In diesem Projekt konzentrierte ich mich hauptsächlich auf die Entwicklung des ROIProfilers, eines ausgeklügelten Tools zur Analyse von C++-Code. Mit der Clang LibTooling-Bibliothek baute ich erfolgreich ein System auf, das dynamisch Leistungsindikatoren in C++-Quelldateien einfügt. Meine Aufgaben umfassten das Durchlaufen und Annotieren von Funktionen und Anweisungen im Clang AST, das Einrichten verschiedener Optionen für Traversierungseinstiegspunkte und das Anpassen der Ausgabeorten für Dateien. Diese Erfahrung schärfte meine Fähigkeiten in der Analyse und Optimierung von C++-Code und vertiefte mein Verständnis für Leistungsbewertung in der Softwareentwicklung. Zudem meisterte ich die Komplexität des Aufbaus und der Konfiguration der Entwicklungsumgebung für dieses Tool auf Linux und macOS.

## Skills

### Programming Languages

 - C++
### Technologies

 - UNIX
 - CMake
 - Clang
 - GCC
 - Latex
### Soft Skill

 - Scientific Writing

## Visite

- [Book Detecting Performance Bottlenecks through AST Transformation](https://files.hagn.network/documents/thesis/bachelor-business-informatics.pdf)
- [Document Certificate Bachelor Business Informatics](https://files.hagn.network/documents/certificate/bachelor-business-informatics.pdf)
- [Document Report Bachelor Business Informatics](https://files.hagn.network/documents/certificate/bachelor-business-informatics-report.pdf)
- [Document Supplement Bachelor Business Informatics](https://files.hagn.network/documents/certificate/bachelor-business-informatics-supplement.pdf)
- [GitHub Repository](https://github.com/maxhagn/ROIProfilerCPP)
- [Website](https://roiprofiler.hagn.network)

## Gallery

![Image 01 Title Page](https://files.hagn.network/images/regions-of-interest-profiler/title-page.webp)
![Image 02 Example Code Showing a Simple C++ Application](https://files.hagn.network/images/regions-of-interest-profiler/example-code-cpp.webp)
![Image 03 Example Code Showing the Instructions Wrapped by Performance Counters](https://files.hagn.network/images/regions-of-interest-profiler/example-code-instructions-wrapped.webp)
![Image 04 The Desired Output of the Transformed Application](https://files.hagn.network/images/regions-of-interest-profiler/output-regions-of-interest-profiler.webp)
![Image 05 An Example of the Abstract Syntax Tree Provided by Clang](https://files.hagn.network/images/regions-of-interest-profiler/example-abstract-syntax-tree-clang.webp)
![Image 06 Flow Chart Representing the Logic of the ROIProfiler](https://files.hagn.network/images/regions-of-interest-profiler/roiprofiler-flow-chart.webp)
![Image 07 The Synopsis of the ROIProfiler](https://files.hagn.network/images/regions-of-interest-profiler/roiprofiler-synopsis.webp)
![Image 08 Runtime Comparison for the Varying Loop Runtimes Application](https://files.hagn.network/images/regions-of-interest-profiler/stats-forloop-comparison.webp)
![Image 09 Runtime Deviation for the Execution of the Varying Loop Runtimes Application](https://files.hagn.network/images/regions-of-interest-profiler/stats-forloop-deviation.webp)
![Image 10 Runtime Comparison for the Fibonacci Sequence Application](https://files.hagn.network/images/regions-of-interest-profiler/stats-fibonacci-comparison.webp)
![Image 11 Runtime Comparison for the Password Generator Application](https://files.hagn.network/images/regions-of-interest-profiler/stats-password-comparison.webp)
![Image 12 Runtime Comparison for the Variable Password Size Generator Application](https://files.hagn.network/images/regions-of-interest-profiler/stats-variable-password-comparison.webp)
![Image 13 Time Per Measurement Value Comparison for Various Test Cases](https://files.hagn.network/images/regions-of-interest-profiler/stats-conclusion-per-counter.webp)
![Image 14 Total Overhead Per Code Block Comparison for Various Test Cases](https://files.hagn.network/images/regions-of-interest-profiler/stats-conclusion-per-array-entry.webp)
![Image 15 Prime Number Comparison for the Prime Benchmark Application](https://files.hagn.network/images/regions-of-interest-profiler/stats-prime-comparison.webp)

## Technical Introduction
This tool transforms C++ code by adding performance counter dynamically to the source file.
Functions and statements are traversed in the Clang AST and annotated if necessary. If 
--stmt option is not specified the program annotates the first level. The --stmt option can
be used to specify a function or bundle of statements as traversal entry point. 
The output file is written to output.cpp or to the file specified with the -o option.
The program takes .cpp oder .cxx file as input.

The Tool is build with Clang LibTooling library. LibTooling is a library to support writing standalone tools based on Clang. \
Further Information: https://clang.llvm.org/docs/LibTooling.html

## Installation Guide
This section explains how to build the LLVM source. More information is available on the official Clang or LLVM page.

+ Clang Getting Started: [https://clang.llvm.org/get_started.html](https://clang.llvm.org/get_started.html)
+ Clang Settup LLVM for LibTooling: [https://clang.llvm.org/docs/HowToSetupToolingForLLVM.html](https://clang.llvm.org/docs/HowToSetupToolingForLLVM.html)
+ LLVM Getting Started: [https://llvm.org/docs/GettingStarted.html](https://llvm.org/docs/GettingStarted.html)

### Requirements
The program has been extensively tested on Linux and macOS and is definitely usable on these operating systems. Windows could also work with tools like cygwin or Linux subkernels, but you have to expect the normal performance losses that result from developing on Windows.

To follow my recommended workflow the packages `CMAKE`, `GCC`, `Python`, `zlib`, `GNU Make`, `Ninja` are required. These can be installed under Linux with `apt-get` or under macOS with `brew`. The packages should be available under any other Linux distro without `apt-get` package manager (`pacman`, `yum`), just follow the developer's web pages.

| Instruction                                                             | Operating System                   |
|-------------------------------------------------------------------------|------------------------------------|
| `sudo apt-get install cmake gcc python ninja-build`                     | Linux                              |
| `brew install cmake gcc python ninja`                                   | macOS                              |

### Build LLVM and ROI Profiler

I worked exclusively with the `ninja` build system for the development. Other options can be found on the official LLVM page, but `ninja` is used by most LLVM developers.

####  Checkout, configure and build LLVM with Ninja
1. `git clone https://github.com/llvm/llvm-project.git`
2. `cd llvm-project`
3. `mkdir build`
4. `cd build`
5. `cmake -G Ninja ../llvm -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" -DLLVM_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release`
6. `ninja`

#### Checkout, build and configure the ROI Profiler
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

### Workflow
#### Synopsis
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


#### Example
Coming Soon

## Autor
Maximilian Hagn <br>
1220 Wien <br>
Austria

**Institution**<br>
Technical University of Vienna<br>
Technische Universität Wien<br>
1040 Wien
