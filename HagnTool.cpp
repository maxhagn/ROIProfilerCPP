#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"
#include "clang/Basic/TokenKinds.h"
#include "clang/Lex/Lexer.h"
#include "clang/AST/Stmt.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;


Rewriter rewriter;
SourceLocation initializationLocation;
SourceLocation summaryLocation;
string currentVisitIdentifier = "start";
int globalChildrenCounter = 0;
bool transformationSuccess = false;

// Common Options and Extra Help definition
static llvm::cl::OptionCategory MyToolCategory( "hagn-tool options" );
static cl::extrahelp CommonHelp( CommonOptionsParser::HelpMessage );
static cl::extrahelp
        MoreHelp( "\nWith the HagnTool you can add performance counter to different "
                  "statements in your Code. The Input File is an C File and the "
                  "Output contains the transformed code \n" );

// Custom Options definition
// Option -o to specify a custom output file path
static cl::opt <string> OutputFile( "o", cl::desc( "Write transformed file to custom location" ),
                                    cl::value_desc( "output file" ), cl::cat( MyToolCategory ));

// Option --stmt to specify search and replace depth
static cl::opt <string> Statement( "stmt", cl::desc( "Specifies the current traversal point" ),
                                   cl::value_desc( "id of stmt" ), cl::cat( MyToolCategory ));


/********************************************//**
 * ! \brief Traverses recursively through the body
 *  of the specified function body. Function Body
 *  is a set of statements.
 ***********************************************/
void traverseChildren( Stmt *funcBody, ASTContext *localContext ) {

    int childrenSize = 0;
    Stmt *parentStmt = NULL;

    // visit all children in function compound statement
    for ( Stmt::child_iterator i = funcBody->child_begin( ), e = funcBody->child_end( ); i != e; ++i ) {
        Stmt *currStmt = *i;
        // ignore all return statements
        if ( currStmt->getStmtClass( ) != Stmt::ReturnStmtClass ) {
            childrenSize++;

            // find call expressions and loops
            if ( currStmt->getStmtClass( ) == Stmt::CallExprClass
                 || currStmt->getStmtClass( ) == Stmt::ForStmtClass
                 || currStmt->getStmtClass( ) == Stmt::WhileStmtClass
                    ) {
                parentStmt = currStmt;
            }
        }
    }

    // if body has multiple children, annotate all statements with performance counter
    if ( childrenSize > 1 ) {
        int childCounter = 0;
        for ( Stmt::child_iterator i = funcBody->child_begin( ), e = funcBody->child_end( );
              i != e; ++i ) {
            Stmt *currStmt = *i;
            currStmt->getStmtClassName( );

            if ( currStmt->getStmtClass( ) != Stmt::ReturnStmtClass ) {

                SourceLocation beginLoc = currStmt->getBeginLoc( );
                SourceLocation endLoc = currStmt->getEndLoc( );

                int64_t id = currStmt->getID( *localContext );
                std::string idString = currStmt->getStmtClassName( ) + std::string( " " ) + std::to_string( id );
                std::string id_definition =
                        "ids[" + std::to_string( childCounter ) + "] = \"" + idString + "\";";
                std::string counter_start_name =
                        "times[" + std::to_string( childCounter ) + "][0] = std::chrono::high_resolution_clock::now();";
                std::string counter_end_name =
                        "times[" + std::to_string( childCounter ) + "][1] = std::chrono::high_resolution_clock::now();";

                Optional <Token> currentToken( clang::Lexer::findNextToken(
                        endLoc, localContext->getSourceManager( ),
                        localContext->getLangOpts( )));

                if ( currentToken->getKind( ) == clang::tok::raw_identifier ) {
                    endLoc = endLoc.getLocWithOffset( -1 );
                } else if ( currentToken->getKind( ) == clang::tok::semi ) {
                    endLoc = endLoc.getLocWithOffset( 0 );
                } else if ( currentToken->getKind( ) == clang::tok::r_brace ) {
                    endLoc = endLoc.getLocWithOffset( 1 );
                }

                SourceLocation locAfterSemi( clang::Lexer::findLocationAfterToken(
                        endLoc, clang::tok::semi,
                        localContext->getSourceManager( ),
                        localContext->getLangOpts( ), true ));

                SourceLocation locAfterBrace( clang::Lexer::findLocationAfterToken(
                        endLoc, clang::tok::r_brace,
                        localContext->getSourceManager( ),
                        localContext->getLangOpts( ), true ));

                if ( currentToken->getKind( ) == clang::tok::r_brace ) { }
                else if ( locAfterSemi.isValid( )) {
                    endLoc = locAfterSemi;
                } else if ( locAfterBrace.isValid( )) {
                    endLoc = locAfterBrace;
                }

                rewriter.InsertText( beginLoc, id_definition + "\n" );
                rewriter.InsertText( beginLoc, "//" + idString + " start time declaration\n" );
                rewriter.InsertText( beginLoc, counter_start_name + "\n" );

                rewriter.InsertText( endLoc, "//" + idString + " end time declaration\n" );
                rewriter.InsertText( endLoc, counter_end_name + "\n\n" );

                childCounter++;
            }
        }

        globalChildrenCounter = childCounter;

        // print program finished notification
        cout << "hagn-tool finished code transformation!\n";

        // set transformation successful
        transformationSuccess = true;

    }
    // if body has zero or one statements
    else {
        // if one children is parent of another set of statements
        // call traverseChildren recursively
        if ( parentStmt != NULL ) {
            if ( parentStmt->getStmtClass( ) == Stmt::CallExprClass ) {
                CallExpr *expr = cast<CallExpr>( parentStmt );
                Stmt *nextBody = expr->getDirectCallee( )->getBody( );
                traverseChildren( nextBody, localContext );
            }
            if ( parentStmt->getStmtClass( ) == Stmt::ForStmtClass ) {
                ForStmt *forStmt = cast<ForStmt>( parentStmt );
                Stmt *nextBody = forStmt->getBody( );
                traverseChildren( nextBody, localContext );
            }
            if ( parentStmt->getStmtClass( ) == Stmt::WhileStmtClass ) {
                WhileStmt *whileStmt = cast<WhileStmt>( parentStmt );
                Stmt *nextBody = whileStmt->getBody( );
                traverseChildren( nextBody, localContext );
            }
        // if return is the only statement annotate nothing
        } else {
            cout << "hagn-tool hasn't found any statements!\n";
        }
    }
}

// AST Tree Visitor
class Visitor : public RecursiveASTVisitor<Visitor> {
private:
    ASTContext *astContext; // used for getting additional AST info

public:
    explicit Visitor( ASTContext *Context )
            : astContext( Context ) // initialize private members
    {
        rewriter.setSourceMgr( astContext->getSourceManager( ),
                               astContext->getLangOpts( ));
    }

    virtual bool VisitStmt( Stmt *stmt ) {
        if ( astContext->getSourceManager( ).isInMainFile( stmt->getBeginLoc( ))) {
            if ( currentVisitIdentifier != "start" ) {
                int64_t currentId = stmt->getID( *astContext );
                std::string currentIdString = std::to_string( currentId );
                if ( currentIdString == currentVisitIdentifier ) {
                    if ( stmt->getStmtClass( ) == Stmt::CallExprClass ) {
                        CallExpr *expr = cast<CallExpr>( stmt );
                        Stmt *nextBody = expr->getDirectCallee( )->getBody( );
                        traverseChildren( nextBody, astContext );
                    }
                    if ( stmt->getStmtClass( ) == Stmt::ForStmtClass ) {
                        ForStmt *forStmt = cast<ForStmt>( stmt );
                        Stmt *nextBody = forStmt->getBody( );
                        traverseChildren( nextBody, astContext );
                    }
                    if ( stmt->getStmtClass( ) == Stmt::WhileStmtClass ) {
                        WhileStmt *whileStmt = cast<WhileStmt>( stmt );
                        Stmt *nextBody = whileStmt->getBody( );
                        traverseChildren( nextBody, astContext );
                    }
                    cout << "hagn-tool found the specified declaration.";
                }
            }
        }
        return true;
    }

    virtual bool VisitFunctionDecl( FunctionDecl *func ) {

        // find initialization location for includes and array definitions
        if ( initializationLocation.isInvalid( ) &&
             astContext->getSourceManager( ).isInMainFile( func->getLocation( ))) {
            initializationLocation = func->getOuterLocStart( );
        }

        // find summary location in main class
        if ( summaryLocation.isInvalid( ) &&
             astContext->getSourceManager( ).isInMainFile( func->getLocation( ))) {
            if ( func->isMain( )) {
                for ( Stmt::child_iterator i = func->getBody( )->child_begin( ), e = func->getBody( )->child_end( );
                      i != e; ++i ) {
                    Stmt *currStmt = *i;
                    if ( currStmt->getStmtClass( ) == Stmt::ReturnStmtClass ) {
                        summaryLocation = currStmt->getBeginLoc( );
                    }
                }
            }
        }

        // if first call traverse main function
        if ( astContext->getSourceManager( ).isInMainFile( func->getLocation( ))) {
            if ( currentVisitIdentifier == "start" ) {
                if ( func->isMain( )) {
                    traverseChildren( func->getBody( ), astContext );
                }
            }
        }
        return true;
    }
};

/********************************************//**
 * ! \brief Customizes a Instance of ASTConsumer.
 *   The Consumer is used by the Frontend Action
 *   to traverse the AST Tree
 ***********************************************/
class Consumer : public ASTConsumer {
private:
    Visitor Visitor;

public:
    explicit Consumer( ASTContext *Context )
            : Visitor( Context ) { }

    virtual void HandleTranslationUnit( ASTContext &Context ) override {
        Visitor.TraverseDecl( Context.getTranslationUnitDecl( ));
    }
};

/********************************************//**
 * ! \brief Creates ASTConsumer and returns ASTContext.
 *  A new ClangFrontendAction is created in the main,
 *  where the CompilerInstance and the SourceFiles are
 *  used to generate a new AST Tree Consumer.
 ***********************************************/
class ClangFrontendAction : public clang::ASTFrontendAction {
public:
    virtual std::unique_ptr <clang::ASTConsumer>
    CreateASTConsumer( clang::CompilerInstance &Compiler, llvm::StringRef InFile ) override {
        return std::make_unique<Consumer>( &Compiler.getASTContext( ));
    }
};

/********************************************//**
 * ! \brief The entry point of the tool.
 *  The main functions deals with the input files
 *  and options. Furthermore the ClangFrontendAction
 *  will be created and is used to transform the code.
 *  After transformation the rewritten code will be printed
 *  to the specified output file.
 ***********************************************/
int main( int argc, const char **argv ) {

    // create Common Option Parser
    auto ExpectedParser = CommonOptionsParser::create( argc, argv, MyToolCategory, llvm::cl::Required );

    // terminate if specified options are not expected
    if ( !ExpectedParser ) {
        llvm::errs( ) << ExpectedParser.takeError( );
        return 1;
    }

    // create local parameter variables
    std::string outputFilename = "output.cpp";
    std::string stmtId = "start";

    // create the stream for output file
    std::error_code err_code;

    // parse arguments
    for ( int i = 0; i < argc; ++i ) {

        // if output file is specified
        if ( std::string( argv[ i ] ) == "-o" ) {
            outputFilename = std::string( argv[ i + 1 ] );
            cout << "Transformed file is written to " << std::string( argv[ i + 1 ] ) << ".\n";
        }

        // if statement id is specified
        if ( std::string( argv[ i ] ) == "--stmt" ) {
            stmtId = std::string( argv[ i + 1 ] );
            cout << "Statement Id " << std::string( argv[ i + 1 ] ) << " detected ... \n";
        }
    }

    // print no statement id notification
    if ( stmtId == "start" ) {
        cout << "No statement id detected, annotating main function ...\n";
    }

    // add statement id to global scope
    currentVisitIdentifier = stmtId;

    // set destination of output file to the specified file
    llvm::raw_fd_ostream dest( outputFilename, err_code );

    // Parse the options and create new ClangTool
    CommonOptionsParser &OptionsParser = ExpectedParser.get( );
    ClangTool Tool( OptionsParser.getCompilations( ),
                    OptionsParser.getSourcePathList( ));


    // run the Clang Tool, creating a new FrontendAction
    int result =
            Tool.run( newFrontendActionFactory<ClangFrontendAction>( ).get( ));

    // add initialization and summary if transformation was successful
    if ( transformationSuccess ) {
        // insert includes and array definitions before first function
        if ( initializationLocation.isValid( )) {
            std::string initializationString =
                    "// Added Performance Counter to program\n// include chrono library to calculate performance times\n#include <chrono>\n#include <iomanip>\nstd::string ids[" +
                    std::to_string( globalChildrenCounter ) + "];\n"
                    + "std::chrono::high_resolution_clock::time_point times[" + std::to_string( globalChildrenCounter ) +
                    "][2];\n\n";
            rewriter.InsertText( initializationLocation, initializationString );
        }

        // insert time summery as last step in the main function
        if ( summaryLocation.isValid( )) {
            globalChildrenCounter--;
            std::string summaryString =
                    "std::cout << \"\\n\\nTotal Time in Scope: \" << (times[" + std::to_string( globalChildrenCounter ) +
                    "][1]-times[0][0])/std::chrono::nanoseconds(1) << \"ns\\n\";\n"
                    +
                    "std::cout << std::setw(30) << \"Description\" << std::right << std::setw(13) << std::setfill(' ') << \"Time\" << std::right <<  std::setw(17) << \"Percentage\\n\"; \n"
                    + "for ( int j = 0; j <= " + std::to_string( globalChildrenCounter ) + "; j++ ) {\n"
                    + "std::chrono::duration<double> sub = times[j][1]-times[j][0];\n"
                    + "std::chrono::duration<double> all = times[" + std::to_string( globalChildrenCounter ) +
                    "][1]-times[0][0];\n"
                    + "double diff =  sub / all * 100;\n"
                    +
                    "std::cout << std::setw(30) << ids[j] << std::right << std::setw(10) << (times[j][1]-times[j][0])/std::chrono::nanoseconds(1) << std::setw(3) << \"ns\"<< std::right << std::setw(15) << std::setprecision(4) << diff << std::setw(2) << \"%\\n\";\n"
                    + "}";
            rewriter.InsertText( summaryLocation, summaryString );
        }
    } else {
        cout << "No statements with id " << stmtId << " found.\n\n";
    }
    // add transformed code to output file
    rewriter.getEditBuffer( rewriter.getSourceMgr( ).getMainFileID( )).write( dest );
    return result;
}
