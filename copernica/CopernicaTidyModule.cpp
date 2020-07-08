//===--- GoogleTidyModule.cpp - clang-tidy --------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "AvoidGotoCheck.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace copernica {

class CopernicaModule : public ClangTidyModule {
 public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<AvoidGotoCheck>(
        "copernica-avoid-goto");
  }

  ClangTidyOptions getModuleOptions() override {
    ClangTidyOptions Options;
    auto &Opts = Options.CheckOptions;
    return Options;
  }
};

// Register the CopernicaTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<CopernicaModule> X("copernica-module",
                                                    "Adds Copernica/MailerQ lint checks.");

}  // namespace copernica

// This anchor is used to force the linker to link in the generated object file
// and thus register the GoogleModule.
volatile int CopernicaModuleAnchorSource = 0;

}  // namespace tidy
}  // namespace clang
