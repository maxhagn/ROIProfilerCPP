#include <iostream>
#include <iomanip>
#include <list>
#include <vector>

using namespace std;
using namespace std::chrono;
constexpr system_clock::time_point invalidTime = system_clock::time_point::min( );
bool repeatedStatements = false;

struct StatementRuntime {
    string identifier;
    system_clock::time_point startTime;
    system_clock::time_point endTime = invalidTime;

    bool operator<( const StatementRuntime &a ) const {
        return startTime - endTime > a.startTime - a.endTime;
    }
};

class DataStorage {
public:
    std::vector <StatementRuntime> statementRuntimeVector;

    void startEvent( string identifier ) {
        auto match = std::find_if( statementRuntimeVector.begin( ), statementRuntimeVector.end( ),
                                   [ &identifier ]( const StatementRuntime &currentStatementRuntime ) {
                                       return currentStatementRuntime.identifier == identifier;
                                   } );
        if ( match != statementRuntimeVector.end( )) {
            if ( match->endTime == invalidTime ) {
                match->endTime = system_clock::now( );
            } else {
                repeatedStatements = true;
            }
        } else {
            StatementRuntime newStatementRuntime;
            newStatementRuntime.identifier = identifier;
            newStatementRuntime.startTime = system_clock::now( );
            statementRuntimeVector.push_back( newStatementRuntime );
        }
    }

    void endEvent( ) {

    }

    void print( ) {
        std::chrono::duration<double> totalRuntime;
        std::chrono::duration<double> statementRuntimeSum;
        std::chrono::duration<double> scopeRuntime =
                statementRuntimeVector.back( ).endTime - statementRuntimeVector.front( ).startTime;

        auto match = std::find_if( statementRuntimeVector.begin( ), statementRuntimeVector.end( ),
                                   [ ]( const StatementRuntime &currentStatementRuntime ) {
                                       return currentStatementRuntime.identifier == "Runtime";
                                   } );
        if ( match != statementRuntimeVector.end( )) {
            totalRuntime = match->endTime - match->startTime;
        }

        cout << "\n\n\n" << setw( 82 ) << setfill( '=' ) << "\n";
        cout << setw( 45 ) << setfill( ' ' ) << "Statistic" << setw( 25 ) << "\n";
        cout << setw( 83 ) << setfill( '=' ) << "\n\n";
        cout << setfill( ' ' ) << setw( 30 ) << "Description"
             << std::setw( 5 ) << "|"
             << right << setw( 13 ) << "Time"
             << std::setw( 5 ) << "|"
             << right << setw( 12 ) << "% Scope"
             << std::setw( 5 ) << "|"
             << right << setw( 12 ) << "% Total\n";
        cout << setw( 82 ) << setfill( '-' ) << "\n";

        std::sort( statementRuntimeVector.begin( ), statementRuntimeVector.end( ));
        for ( StatementRuntime currentStatementRuntimeVector: statementRuntimeVector ) {
            std::chrono::duration<double> currentDuration =
                    currentStatementRuntimeVector.endTime - currentStatementRuntimeVector.startTime;
            double totalUsagePercentage = currentDuration / totalRuntime * 100;
            double scopeUsagePercentage = currentDuration / scopeRuntime * 100;

            if ( currentStatementRuntimeVector.identifier != "Runtime" ) {
                statementRuntimeSum = statementRuntimeSum + currentDuration;
            }

            if ( currentStatementRuntimeVector.identifier == "Runtime" && repeatedStatements ) {

            } else {
                std::cout << setfill( ' ' ) << std::setw( 30 ) << currentStatementRuntimeVector.identifier
                          << std::setw( 5 ) << "|"
                          << std::right << std::setw( 10 ) << currentDuration / milliseconds( 1 ) << std::setw( 3 ) << "ms"
                          << std::setw( 5 ) << "|"
                          << std::right << std::setw( 10 ) << std::setprecision( 4 ) << scopeUsagePercentage
                          << std::setw( 2 ) << "%"
                          << std::setw( 5 ) << "|"
                          << std::right << std::setw( 9 ) << std::setprecision( 4 ) << totalUsagePercentage
                          << std::setw( 3 ) << "%\n";
            }

        }

        if ( !repeatedStatements ) {

            double hagnToolTotalUsagePercentage = ( totalRuntime - statementRuntimeSum ) / totalRuntime * 100;
            double hagnToolScopeUsagePercentage = ( totalRuntime - statementRuntimeSum ) / scopeRuntime * 100;
            std::cout << setfill( ' ' ) << std::setw( 30 ) << "Hagn Tool"
                      << std::setw( 5 ) << "|"
                      << std::right << std::setw( 10 ) << ( totalRuntime - statementRuntimeSum ) / milliseconds( 1 )
                      << std::setw( 3 ) << "ms"
                      << std::setw( 5 ) << "|"
                      << std::right << std::setw( 10 ) << std::setprecision( 4 ) << hagnToolScopeUsagePercentage
                      << std::setw( 2 ) << "%"
                      << std::setw( 5 ) << "|"
                      << std::right << std::setw( 9 ) << std::setprecision( 4 ) << hagnToolTotalUsagePercentage
                      << std::setw( 3 ) << "%\n";

        }

    }
};