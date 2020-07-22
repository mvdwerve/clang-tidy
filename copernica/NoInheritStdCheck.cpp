//===--- NoInheritStdCheck.cpp - clang-tidy -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoInheritStdCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace copernica {

void NoInheritStdCheck::registerMatchers(MatchFinder *Finder) {

  //Finder->addMatcher(functionDecl().bind("x"), this);
  Finder->addMatcher(cxxRecordDecl(isDerivedFrom(namedDecl(isInStdNamespace()))).bind("class"), this);
}

void NoInheritStdCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *MatchedDecl = Result.Nodes.getNodeAs<CXXRecordDecl>("class");
  diag(MatchedDecl->getBeginLoc(), "do not inherit from classes in std namespace") << MatchedDecl->getSourceRange();
}

} // namespace copernica
} // namespace tidy
} // namespace clang
