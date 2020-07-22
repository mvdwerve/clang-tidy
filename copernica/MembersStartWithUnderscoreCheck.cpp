//===--- MembersStartWithUnderscoreCheck.cpp - clang-tidy -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MembersStartWithUnderscoreCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace copernica {

void MembersStartWithUnderscoreCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(
    // find all private/protected members, skip lambdas
    fieldDecl(unless(anyOf(isPublic(), hasParent(cxxRecordDecl(isLambda()))))).bind("field"), this);
}

void MembersStartWithUnderscoreCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *MatchedDecl = Result.Nodes.getNodeAs<FieldDecl>("field");
  if (MatchedDecl->getNameAsString()[0] == '_') return;
  diag(MatchedDecl->getLocation(), "private or protected member is expected to start with an underscore _...");
}

} // namespace copernica
} // namespace tidy
} // namespace clang
