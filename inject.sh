#!/bin/bash

sed -i 's/add_subdirectory(cppcoreguidelines)/add_subdirectory\(copernica\)\nadd_subdirectory\(cppcoreguidelines\)/g' /llvm-project/clang-tools-extra/clang-tidy/CMakeLists.txt
sed -i 's/  clangTidyCppCoreGuidelinesModule/  clangTidyCopernicaModule\n  clangTidyCppCoreGuidelinesModule/g' /llvm-project/clang-tools-extra/clang-tidy/CMakeLists.txt
sed -i 's/This anchor is used to force the linker to link the CppCoreGuidelinesModule./\nextern volatile int CopernicaModuleAnchorSource; static int LLVM_ATTRIBUTE_UNUSED CopernicaModuleAnchorDestination = CopernicaModuleAnchorSource;/g' /llvm-project/clang-tools-extra/clang-tidy/ClangTidyForceLinker.h

cat /llvm-project/clang-tools-extra/clang-tidy/ClangTidyForceLinker.h

exit 1