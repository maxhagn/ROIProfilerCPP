set(LLVM_LINK_COMPONENTS support)

add_clang_executable(roiwpc
  RegionProfile.cpp
  )
target_link_libraries(roiwpc
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