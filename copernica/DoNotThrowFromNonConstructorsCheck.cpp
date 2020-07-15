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
  Finder->addMatcher(cxxThrowExpr(anyOf(unless(hasAncestor(cxxTryStmt())),
                                    unless(hasAncestor(cxxConstructorDecl()))))
                         .bind("throw"),
                     this);
}

void DoNotThrowFromNonConstructorsCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *MatchedDecl = Result.Nodes.getNodeAs<Expr>("throw");
  diag(MatchedDecl->getExprLoc(), "function is insufficiently awesome");
  //return;
  // if (MatchedDecl->getName().startswith("awesome_"))
  //   return;
  // 
  // diag(MatchedDecl->getLocation(), "insert 'awesome'", DiagnosticIDs::Note)
  //     << FixItHint::CreateInsertion(MatchedDecl->getLocation(), "awesome_");
}

} // namespace copernica
} // namespace tidy
} // namespace clang
