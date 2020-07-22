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
#include <iostream>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace copernica {

void DoNotThrowFromNonConstructorsCheck::registerMatchers(MatchFinder *Finder) {
    auto caught = anyOf(
        // we have a try statement surrounding it
        hasAncestor(cxxTryStmt()), 
        // or a constructor is declared
        hasAncestor(cxxConstructorDecl())
    );

  // find all direct throw expressions
  Finder->addMatcher(
    // matches throw expressions
    cxxThrowExpr(
        // except if...
        unless(
            caught
        )
    ).bind("bad_throw"),
    this);

  // find all object instantiations
  Finder->addMatcher(
    // matches throw expressions
    expr(
        anyOf(
            cxxConstructExpr(
                unless(
                    caught
                ), 
                hasDeclaration(cxxConstructorDecl(
                    hasDescendant(cxxThrowExpr())
                ))
            ).bind("construct"),
            cxxTemporaryObjectExpr(
                unless(
                    caught
                ), 
                hasDeclaration(cxxConstructorDecl(
                    hasDescendant(cxxThrowExpr())
                ))
            ).bind("tempconstruct")
        )
    ),
    this);

    // @todo the nested 'throws' should be fixed
    // @todo the @throws expression should be parsed from the decl for all constructors that have impl in source
}

void DoNotThrowFromNonConstructorsCheck::check(const MatchFinder::MatchResult &Result) {
const auto *BadThrow = Result.Nodes.getNodeAs<CXXThrowExpr>("bad_throw");
const auto *construct = Result.Nodes.getNodeAs<CXXConstructExpr>("construct");
const auto *tmpconstruct = Result.Nodes.getNodeAs<CXXTemporaryObjectExpr>("tempconstruct");

//diag(construct->getBeginLoc(), "called");
if (BadThrow) diag(BadThrow->getBeginLoc(), "uncaught exception in non-constructor") << BadThrow->getSourceRange();
if (construct) diag(construct->getLocation(), "possible uncaught exception from constructor");
if (tmpconstruct) diag(tmpconstruct->getLocation(), "possible uncaught exception from constructed temporary");
}

} // namespace copernica
} // namespace tidy
} // namespace clang
