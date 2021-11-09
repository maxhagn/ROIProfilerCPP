# Introduction
This Tool can be used to transform C++ Code. 
The Tool adds performance counter to a given file and automatically prints the generated statistics. 
The input parameters are a .cpp or .cxx file. The output file can be specified with -o output.cpp.
With the --stmt parameter a specific statement can be traversed. If no --stmt is specified the programs
annotates the main function and return the performance times and statement ids for further investigation.

# Author
Technical University Vienna

Maximilian Hagn <br />
Brausewettergasse 16 / TOP 3 <br />
1220 Wien <br />
Austria

# Caveat
This documentation is generated directly from the source code with doxygen. Since my clang libtool is constantly under active development, what you're about to read is out of date!