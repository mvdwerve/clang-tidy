//===--- VirtualDestructorCheck.cpp - clang-tidy -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "VirtualDestructorCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace copernica {

void VirtualDestructorCheck::registerMatchers(MatchFinder *Finder) {
  auto NonPureVirtualClass = anyOf(
      has(cxxMethodDecl(isUserProvided(), unless(anyOf(
        isPure(),
        unless(hasDescendant(stmt()))
      )))),
      has(fieldDecl()),
      has(cxxConstructorDecl(isUserProvided()))
  );
  
  // FIXME: Add matchers.
  // find all class definitions with destructors that are not virtual
  Finder->addMatcher(
    cxxRecordDecl(
      isDefinition(),
      isClass(),
      has(cxxDestructorDecl(
        unless(isVirtualAsWritten()),
        anyOf(
          isUserProvided(),
          isDefaulted()
        )
      ).bind("destructor")),
      unless(isLambda()),
      NonPureVirtualClass, // workaround for pure virtual classes
      unless(hasAnyBase(hasType(cxxRecordDecl(unless(NonPureVirtualClass)))))
    ),
    this);

  // find all class definitions that do not have a destructor defined
  Finder->addMatcher(
    cxxRecordDecl(
      isDefinition(),
      isClass(),
      unless(has(cxxDestructorDecl(anyOf(isUserProvided(), isDefaulted())))),
      unless(isLambda()),
      NonPureVirtualClass, // workaround for pure virtual classes
      unless(hasAnyBase(hasType(cxxRecordDecl(unless(NonPureVirtualClass)))))
    ).bind("destructorless"),
    this);
}

void VirtualDestructorCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *destructor = Result.Nodes.getNodeAs<CXXDestructorDecl>("destructor");
  const auto *destructorless = Result.Nodes.getNodeAs<CXXRecordDecl>("destructorless");

  if (destructor)     diag(destructor->getBeginLoc(), "destructor must be virtual") << destructor->getSourceRange();
  if (destructorless) diag(destructorless->getBeginLoc(), "destructor must be defined and virtual") << destructorless->getSourceRange();
}

} // namespace copernica
} // namespace tidy
} // namespace clang
