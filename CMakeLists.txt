set(LLVM_LINK_COMPONENTS support)

add_clang_executable(hagn-tool
  HagnTool.cpp
  )
target_link_libraries(hagn-tool
  PRIVATE
  clangAST
  clangBasic
  clangDriver
  clangParse
  clangSema
  clangAnalysis
  clangEdit
  clangLex
  clangFrontend
  clangRewriteFrontend
  clangSerialization
  clangStaticAnalyzerFrontend
  clangTooling
  clangToolingSyntax
  clangASTMatchers
  )