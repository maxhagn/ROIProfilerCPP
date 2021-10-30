# Introduction
This Tool can be used to transform C++ Code. The Tool adds performance counter to a given file and automatically prints the generated statistics. The input parameters are a .cpp or .cxx file. The output file can be specified with -o output.cpp Furthermore the depth can be specified with --depth, where d1 only adds performance counter to the statements and function calls in the main class. d2 also adds counter to all functions on the second level and so on. --depth adds performance counter to all statements

# Author
Technical University Vienna

Maximilian Hagn <br />
Brausewettergasse 16 / TOP 3 <br />
1220 Wien <br />
Austria

# Caveat
This documentation is generated directly from the source code with doxygen. Since my clang libtool is constantly under active development, what you're about to read is out of date!