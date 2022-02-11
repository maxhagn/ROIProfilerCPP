// Helper Functions for DataStorage.cpp
namespace hlibhelp {

#include <iostream>
#include <chrono>
#include <string>

    using namespace std;
    using namespace std::chrono;

    // get perfect time unit for runtime
    string getUnit( std::chrono::duration<double, std::nano> duration ) {
        cout << "\n" << duration.count();
        if ( duration.count( ) > 60000000000 ) {
            return " s";
        }

        if ( duration.count( ) > 1000000000 ) {
            return "ms";
        }

        return "µs";
    }

    // convert usage double to usage string
    string getUsageAsString( double usage ) {
        std::ostringstream customPrecision;

        if ( usage < 0.01 ) {
            customPrecision << "<  0.01";
        } else if ( usage > 99.99 ) {
            customPrecision << "> 99.99";
        } else {
            customPrecision << std::fixed;
            customPrecision << std::setprecision( 2 );
            customPrecision << usage;
        }

        return customPrecision.str( );
    }

    // cast duration to the specified unit
    double convertToSpecifiedUnit( std::chrono::duration<double, std::nano> duration, string prefix ) {
        if ( prefix == "s" ) {
            return duration.count( ) / 1000000000;
        }

        if ( prefix == "ms" ) {
            return duration.count( ) / 1000000;
        }

        return duration.count( ) / 1000;
    }

    // print one row of the statistic table
    void printTableRow( string identifier, string stmtClass, double duration, string unit, string scopeUsage,
                        string totalUsage, string calls ) {
        string percentChar = "  %";
        string separatorChar = "  │  ";
        string hagnToolSeparatorChar = "  │  ";

        if ( identifier == "Runtime" || identifier == "Scope" ) {
            percentChar = "";
            separatorChar = "     ";
            hagnToolSeparatorChar = "     ";
        }
        if ( identifier == "Hagn-Tool" ) {
            hagnToolSeparatorChar = "     ";
        }


        std::ostringstream durationCustomPrecision;

        if ( duration < 0.001 ) {
            durationCustomPrecision << "< 0.001";
        } else {
            durationCustomPrecision << std::fixed;
            durationCustomPrecision << std::setprecision( 3 );
            durationCustomPrecision << duration;
        }


        std::cout << setfill( ' ' ) << "│   "
                  << std::setw( 15 ) << std::left << identifier << hagnToolSeparatorChar
                  << std::setw( 25 ) << std::left << stmtClass << separatorChar;

        if ( identifier == "ID" ) {
            std::cout << std::right << std::setw( 19 ) << "Runtime";
        } else {
            std::cout << std::right << std::setw( 15 ) << durationCustomPrecision.str( ) << "  " << unit;
        }

        std::cout
                << std::setw( 5 ) << separatorChar

                << std::right << std::setw( 10 ) << std::setprecision( 2 ) << scopeUsage + percentChar

                << std::setw( 5 ) << separatorChar

                << std::right << std::setw( 10 ) << std::setprecision( 2 ) << totalUsage + percentChar

                << std::setw( 5 ) << separatorChar

                << std::right << std::setw( 6 ) << std::setprecision( 0 ) << calls

                << std::setw( 5 ) << "   │" << "\n";
    }

    // print separator line for chars
    void printTableSeparator( int width, char separator, string escape ) {
        cout << setw( width ) << setfill( separator ) << escape;
    }

    // print separator line for strings at specified position
    void printTableSeparator( int width, string separator, string position, string escape ) {
        string leftSeparator = "├";
        string rightSeparator = "┤";

        if ( position == "top" ) {
            leftSeparator = "┌";
            rightSeparator = "┐";
        }

        if ( position == "bottom" ) {
            leftSeparator = "└";
            rightSeparator = "┘";
        }

        cout << leftSeparator;
        for ( int i = 0; i <= width; i++ ) {
            cout << separator;
        }

        cout << rightSeparator << escape;
    }

    // print statistic banner
    void printStatisticBanner( ) {
        cout << "\n\n";
        printTableSeparator( 108, '=', "\n" );
        cout << setw( 60 ) << setfill( ' ' ) << "Statistic\n";
        printTableSeparator( 109, '=', "\n\n" );
    }

    // string to array of strings
    string *getSegmentsOfString( string identifier ) {
        std::stringstream identifierStream( identifier );
        string identifierSegment;
        string *segments = new string[2];
        int segmentCounter = 0;
        while ( std::getline( identifierStream, identifierSegment, ' ' )) {
            segments[ segmentCounter++ ] = identifierSegment;
        }
        return segments;
    }

}