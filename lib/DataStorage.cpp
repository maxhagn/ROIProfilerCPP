#include "DataStorage.h"

class DataStorage {
public:

    // saves runtime arrays
    StatementRuntime *statementRuntimeArray;

    // size of measured statements
    int statementRuntimeArraySize;

    // constructor
    DataStorage( string identifierString ) {
        // count entries in identifierStrings
        statementRuntimeArraySize = std::count( identifierString.begin( ), identifierString.end( ), ',' ) + 1;
        statementRuntimeArray = new StatementRuntime[statementRuntimeArraySize];
        statementRuntimeArraySize = 0;

        // split identifier string to array
        std::stringstream identifierStream( identifierString );
        string segment;
        while ( std::getline( identifierStream, segment, ',' )) {
            statementRuntimeArray[ statementRuntimeArraySize++ ].identifier = segment;
        }
    }

    // start event adds current timestamp as start time
    void startEvent( int identifier ) {
        statementRuntimeArray[ identifier ].called++;
        // if identifier is already measured, sum runtimes
        if ( statementRuntimeArray[ identifier ].startTime != invalidTime &&
             statementRuntimeArray[ identifier ].endTime != invalidTime ) {
            statementRuntimeArray[ identifier ].startTime = high_resolution_clock::now( ) -
                                                            ( statementRuntimeArray[ identifier ].endTime -
                                                              statementRuntimeArray[ identifier ].startTime );
        }
            // else add timestamp as start time
        else {
            statementRuntimeArray[ identifier ].startTime = high_resolution_clock::now( );
        }

        //cout << "\ntime:" << high_resolution_clock::now().time_since_epoch().count();
    }

    // end event adds current timestamp as end time
    void endEvent( int identifier ) {
        statementRuntimeArray[ identifier ].endTime = high_resolution_clock::now( );
        //cout << "\ntime:" << high_resolution_clock::now().time_since_epoch().count();
    }

    // print program statistics
    void print( ) {

        // calculate total runtime
        MeasurementEvaluation total;
        total.identifier = "Runtime";
        total.duration = statementRuntimeArray[ 0 ].endTime - statementRuntimeArray[ 0 ].startTime;

        ofstream outfile;
        outfile.open("Time_Without_Print.txt", ios_base::app);
        outfile << hlibhelp::convertToSpecifiedUnit( total.duration, "s" ) << "\n";

        // calculate scope runtime
        MeasurementEvaluation scope;
        scope.identifier = "Scope";
        scope.duration = statementRuntimeArray[ 1 ].endTime - statementRuntimeArray[ 1 ].startTime;

        // sum of runtime of all annotated statements
        std::chrono::duration<double, std::nano> statementRuntimeSum;

        // get unit for runtime if scope measured
        string unit = hlibhelp::getUnit( total.duration );

        // normally scope is measured
        bool scopeIsMeasured = true;

        cout << scope.duration.count();
        // if scope is not measured, calculate time between first and last counter
        if ( scope.duration.count( ) == 0 ) {
            scope.duration = statementRuntimeArray[ statementRuntimeArraySize - 1 ].endTime -
                             statementRuntimeArray[ 2 ].startTime;
            // get unit for runtime
            unit = hlibhelp::getUnit( scope.duration );
            scopeIsMeasured = false;
        }

        // print the statistic banner
        hlibhelp::printStatisticBanner( );

        // print table header
        hlibhelp::printTableSeparator( 115, "—", "top", "\n" );
        hlibhelp::printTableRow( "ID", "ClassType", 0, "", "Scope", "Total", "Calls" );
        hlibhelp::printTableSeparator( 115, "—", "middle", "\n" );

        double sumCalls = 0;

        // iterate through all measured statements
        for ( int i = 2; i < statementRuntimeArraySize; i++ ) {

            // calculate duration
            MeasurementEvaluation currentEvaluation;
            currentEvaluation.duration = statementRuntimeArray[ i ].endTime - statementRuntimeArray[ i ].startTime;
            currentEvaluation.totalUsage = currentEvaluation.duration / total.duration * 100;
            currentEvaluation.scopeUsage = currentEvaluation.duration / scope.duration * 100;
            sumCalls += statementRuntimeArray[ i ].called;
            std::ostringstream calledToString;
            calledToString << std::fixed << setprecision(0) << statementRuntimeArray[ i ].called;
            currentEvaluation.called = calledToString.str();

            statementRuntimeSum += currentEvaluation.duration;

            // split identifier in id and class type
            string *segments = hlibhelp::getSegmentsOfString( statementRuntimeArray[ i ].identifier );

            // current evaluation to string
            double durationBeautified = hlibhelp::convertToSpecifiedUnit( currentEvaluation.duration, unit );
            string scopeUsageBeautified = hlibhelp::getUsageAsString( currentEvaluation.scopeUsage );
            string totalUsageBeautified = hlibhelp::getUsageAsString( currentEvaluation.totalUsage );

            // print current evaluation the row table
            hlibhelp::printTableRow( segments[ 1 ], segments[ 0 ], durationBeautified, unit,
                                     scopeUsageBeautified, totalUsageBeautified, currentEvaluation.called );

        }

        // evaluate hagn tool runtime
        MeasurementEvaluation hagnTool;
        hagnTool.identifier = "Perf Counter";
        hagnTool.duration = scope.duration - statementRuntimeSum;
        hagnTool.totalUsage = hagnTool.duration / total.duration * 100;
        hagnTool.scopeUsage = hagnTool.duration / scope.duration * 100;
        std::ostringstream calledToString;
        sumCalls = sumCalls*2+2;
        calledToString << std::fixed << setprecision(0) << sumCalls;
        hagnTool.called = calledToString.str();

        // hagn tool evaluation to string
        double hagnToolDurationBeautified = hlibhelp::convertToSpecifiedUnit( hagnTool.duration, unit );
        string totalUsageBeautified = hlibhelp::getUsageAsString( hagnTool.totalUsage );
        string scopeUsageBeautified = hlibhelp::getUsageAsString( hagnTool.scopeUsage );

        // print hagnTool row table
        hlibhelp::printTableRow( hagnTool.identifier, "", hagnToolDurationBeautified, unit, scopeUsageBeautified,
                                 totalUsageBeautified, hagnTool.called );


        // check if scope measurement should be printed
        if ( scopeIsMeasured ) {
            hlibhelp::printTableSeparator( 115, "—", "middle", "\n" );
            double scopeDurationBeautified = hlibhelp::convertToSpecifiedUnit( scope.duration, unit );
            hlibhelp::printTableRow( scope.identifier, "", scopeDurationBeautified, unit, "", "", "" );
        } else {
            hlibhelp::printTableSeparator( 115, "—", "middle", "\n" );
        }

        // total duration to string
        double totalDurationBeautified = hlibhelp::convertToSpecifiedUnit( total.duration, unit );

        // print runtime row table
        hlibhelp::printTableRow( total.identifier, "", totalDurationBeautified, unit, "", "", "" );
        hlibhelp::printTableSeparator( 115, "—", "bottom", "\n" );
        cout << "\n\n";

    }
};