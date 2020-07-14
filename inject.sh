#!/bin/bash

sed -i 's/add_subdirectory(cppcoreguidelines)/add_subdirectory\(copernica\)\nadd_subdirectory\(cppcoreguidelines\)/g' /llvm-project/clang-tools-extra/clang-tidy/CMakeLists.txt
sed -i 's/  clangTidyCopernicaModule/  clangTidyCppCoreGuidelinesModule\n  clangTidyCppCoreGuidelinesModule/g' /llvm-project/clang-tools-extra/clang-tidy/CMakeLists.txt
sed -i 's/\/\/ This anchor is used to force the linker to link the CppCoreGuidelinesModule.\nextern volatile int CppCoreGuidelinesModuleAnchorSource;\nstatic int LLVM_ATTRIBUTE_UNUSED CppCoreGuidelinesModuleAnchorDestination =\n    CppCoreGuidelinesModuleAnchorSource;/TEST/g' /llvm-project/clang-tools-extra/clang-tidy/ClangTidyForceLinker.h

cat /llvm-project/clang-tools-extra/clang-tidy/CMakeLists.txt
cat /llvm-project/clang-tools-extra/clang-tidy/ClangTidyForceLinker

exit 1