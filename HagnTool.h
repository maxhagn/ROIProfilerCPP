#ifndef CLANG_LLVM_HAGNTOOL_H
#define CLANG_LLVM_HAGNTOOL_H

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
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;

// rewriter is used to add performance counter to input file
Rewriter rewriter;

// initializationLocation is used to initialize hagn lib
SourceLocation initializationLocation;

// runtimeStartLocation is used to start runtime timer
SourceLocation runtimeStartLocation;

// summaryLocation is used to end runtime timer and print summarty
SourceLocation summaryLocation;

string statementOption = "start";
string identifierString = "Runtime,Scope,";
int internalIdentifier = 2;
bool transformationSuccess = false;

// Options and Help Documentation
static llvm::cl::OptionCategory MyToolCategory( "hagn-tool options" );
static cl::extrahelp CommonHelp( CommonOptionsParser::HelpMessage );
static cl::extrahelp
        MoreHelp( "\nWith the HagnTool you can add performance counter to different "
                  "statements in your Code. The Input File is an C File and the "
                  "Output contains the transformed code \n" );

static cl::opt <string> OutputFile( "o", cl::desc( "Write transformed file to custom location" ),
                                    cl::value_desc( "output file" ), cl::cat( MyToolCategory ));

static cl::opt <string> Statement( "stmt", cl::desc( "Specifies the current traversal point" ),
                                   cl::value_desc( "id of stmt" ), cl::cat( MyToolCategory ));

#endif //CLANG_LLVM_HAGNTOOL_H
