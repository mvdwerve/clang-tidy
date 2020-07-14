//===-- CppCoreGuidelinesTidyModule.cpp - clang-tidy ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "../misc/NonPrivateMemberVariablesInClassesCheck.h"
#include "../misc/UnconventionalAssignOperatorCheck.h"
#include "../modernize/AvoidCArraysCheck.h"
#include "../modernize/UseOverrideCheck.h"
#include "../readability/MagicNumbersCheck.h"
#include "AvoidGotoCheck.h"

namespace clang {
namespace tidy {
namespace copernica {

/// A module containing checks of the C++ Core Guidelines
class CopernicaModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<AvoidGotoCheck>("copernica-avoid-goto");
  }
};

// Register the LLVMTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<CopernicaModule>
    X("copernica-module", "Adds checks for the C++ Core Guidelines.");

} // namespace cppcoreguidelines

// This anchor is used to force the linker to link in the generated object file
// and thus register the CppCoreGuidelinesModule.
volatile int CopernicaModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang