//===--- DoNotThrowFromNonConstructorsCheck.cpp - clang-tidy --------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "DoNotThrowFromNonConstructorsCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace copernica {

void DoNotThrowFromNonConstructorsCheck::registerMatchers(MatchFinder *Finder) {
  // look for matchers _not_ in the 
  Finder->addMatcher(
    // matches throw expressions
    cxxThrowExpr(
        // except if...
        unless(
            anyOf(
                // we have a try statement surrounding it
                hasAncestor(cxxTryStmt()), 
                // or a constructor is declared
                hasAncestor(cxxConstructorDecl())
            )
        )
    ).bind("bad_throw"),
    this);
}

void DoNotThrowFromNonConstructorsCheck::check(const MatchFinder::MatchResult &Result) {
const auto *BadThrow = Result.Nodes.getNodeAs<CXXThrowExpr>("bad_throw");
diag(BadThrow->getSubExpr()->getBeginLoc(), "uncaught exception in non-constructor") << BadThrow->getSourceRange();
}

} // namespace copernica
} // namespace tidy
} // namespace clang
