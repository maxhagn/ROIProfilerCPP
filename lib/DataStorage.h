#ifndef CLANG_LLVM_DATASTORAGE_H
#define CLANG_LLVM_DATASTORAGE_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include "Helper.cpp"

using namespace std;
using namespace std::chrono;

constexpr high_resolution_clock::time_point invalidTime = high_resolution_clock::time_point::min( );

struct StatementRuntime {
    string identifier;
    high_resolution_clock::time_point startTime = invalidTime;
    high_resolution_clock::time_point endTime = invalidTime;
};

struct MeasurementEvaluation {
    string identifier;
    std::chrono::duration<double, std::nano> duration;
    double totalUsage;
    double scopeUsage;
};

#endif //CLANG_LLVM_DATASTORAGE_H
