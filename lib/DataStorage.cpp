#include <iostream>
#include <chrono>
#include <iomanip>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <ctime>

using namespace std;

struct StatementRuntime {
    string identifier;
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;

    bool operator<(const StatementRuntime& a) const
    {
        return startTime < endTime;
    }
};

class DataStorage {
public:
    std::vector<StatementRuntime> statementRuntimeVector;

    void startEvent( string identifier ) {
        auto match = std::find_if(statementRuntimeVector.begin(), statementRuntimeVector.end(),
                                  [&identifier](const StatementRuntime& currentStatementRuntime){ return currentStatementRuntime.identifier == identifier; });
        if (match != statementRuntimeVector.end()) {
            match->endTime = std::chrono::system_clock::now();
        } else {
            StatementRuntime newStatementRuntime;
            newStatementRuntime.identifier = identifier;
            newStatementRuntime.startTime = std::chrono::system_clock::now();
            statementRuntimeVector.push_back(newStatementRuntime);
        }
    }

    void endEvent( ) {

    }
    
    void print() {
        std::chrono::duration<double> totalRuntime;
        std::chrono::duration<double> statementRuntimeSum;
        std::chrono::duration<double> scopeRuntime = statementRuntimeVector.back().endTime - statementRuntimeVector.front().startTime;

        auto match = std::find_if(statementRuntimeVector.begin(), statementRuntimeVector.end(),
                                  [](const StatementRuntime& currentStatementRuntime){ return currentStatementRuntime.identifier == "Runtime"; });
        if (match != statementRuntimeVector.end()) {
            totalRuntime = match->endTime-match->startTime;
        }

        cout << "\n\n\n" << setw(82) << setfill('=') << "\n";
        cout << setw(45) << setfill(' ') << "Statistic" << setw(25) <<"\n";
        cout << setw(83) << setfill('=') << "\n\n";
        cout << setfill(' ') << setw(30) << "Description"
             << std::setw(5) << "|"
             << right << setw(13)  << "Time"
             << std::setw(5) << "|"
             << right << setw(12) << "% Scope"
             << std::setw(5) << "|"
             << right << setw(12) << "% Total\n";
        cout << setw(82) << setfill('-') << "\n";

        std::sort(statementRuntimeVector.begin(), statementRuntimeVector.end());
        for ( StatementRuntime currentStatementRuntimeVector :  statementRuntimeVector ) {
            std::chrono::duration<double> currentDuration = currentStatementRuntimeVector.endTime - currentStatementRuntimeVector.startTime;
            double totalUsagePercentage =  currentDuration / totalRuntime * 100;
            double scopeUsagePercentage =  currentDuration / scopeRuntime * 100;

            if ( currentStatementRuntimeVector.identifier != "Runtime" ) {
                statementRuntimeSum = statementRuntimeSum + currentDuration;
            }

            std::cout << setfill(' ') << std::setw(30) << currentStatementRuntimeVector.identifier
                      << std::setw(5) << "|"
                      << std::right << std::setw(10) << currentDuration/std::chrono::microseconds(1) << std::setw(3) << "ms"
                      << std::setw(5) << "|"
                      << std::right << std::setw(10) << std::setprecision(4) << scopeUsagePercentage << std::setw(2) << "%"
                      << std::setw(5) << "|"
                      << std::right << std::setw(9) << std::setprecision(4) << totalUsagePercentage << std::setw(3) << "%\n";
        }

        double hagnToolTotalUsagePercentage =  (totalRuntime-statementRuntimeSum) / totalRuntime * 100;
        double hagnToolScopeUsagePercentage =  (totalRuntime-statementRuntimeSum) / scopeRuntime * 100;
        std::cout << setfill(' ') << std::setw(30) << "Hagn Tool"
                  << std::setw(5) << "|"
                  << std::right << std::setw(10) << (totalRuntime-statementRuntimeSum)/std::chrono::microseconds(1) << std::setw(3) << "ms"
                  << std::setw(5) << "|"
                  << std::right << std::setw(10) << std::setprecision(4) << hagnToolScopeUsagePercentage << std::setw(2) << "%"
                  << std::setw(5) << "|"
                  << std::right << std::setw(9) << std::setprecision(4) << hagnToolTotalUsagePercentage << std::setw(3) << "%\n";
    }
};