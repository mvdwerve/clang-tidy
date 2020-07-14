set(LLVM_LINK_COMPONENTS
  FrontendOpenMP
  Support
  )

add_clang_library(clangTidyCopernicaModule
  AvoidGotoCheck.cpp
  CopernicaTidyModule.cpp

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTidy
  clangTidyReadabilityModule
  clangTidyUtils
  
  DEPENDS
  omp_gen
  )

clang_target_link_libraries(clangTidyCopernicaModule
  PRIVATE
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangSerialization
  clangTooling
  )