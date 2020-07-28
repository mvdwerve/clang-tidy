//===--- ShouldBeNoexceptCheck.cpp - clang-tidy ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ShouldBeNoexceptCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace copernica {

void ShouldBeNoexceptCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(
    cxxConstructorDecl(
      hasParent(    
        cxxRecordDecl(
          isDefinition(),
          isClass(),
          unless(isLambda())
        )
      ),
      unless(hasDescendant(
            cxxConstructExpr(
              unless(hasDeclaration(cxxConstructorDecl(
                anyOf(
                  isInStdNamespace(),
                  isNoThrow()
                )
              )
              ))
            )
      )),
      unless(hasDescendant(cxxThrowExpr())),
      unless(isNoThrow())
    ).bind("constructor"),
    this);
}

void ShouldBeNoexceptCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *MatchedDecl = Result.Nodes.getNodeAs<CXXConstructorDecl>("constructor");
  if (MatchedDecl) diag(MatchedDecl->getBeginLoc(), "constructor should be noexcept as it does not throw and has no throwing member variables");
  }

} // namespace copernica
} // namespace tidy
} // namespace clang
