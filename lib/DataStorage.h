#ifndef CLANG_LLVM_DATASTORAGE_H
#define CLANG_LLVM_DATASTORAGE_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <numeric>
#include "Helper.cpp"

using namespace std;
using namespace std::chrono;

constexpr high_resolution_clock::time_point invalidTime = high_resolution_clock::time_point::min( );

struct StatementRuntime {
    string identifier;
    double called = 0;
    high_resolution_clock::time_point startTime = invalidTime;
    high_resolution_clock::time_point endTime = invalidTime;
};

struct MeasurementEvaluation {
    string identifier;
    string called;
    std::chrono::duration<double, std::nano> duration;
    double totalUsage;
    double scopeUsage;
};

#endif //CLANG_LLVM_DATASTORAGE_H
