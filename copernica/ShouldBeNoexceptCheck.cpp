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
#include "clang/Lex/Lexer.h"
#include "clang/Tooling/FixIt.h"

using namespace clang::ast_matchers;

namespace clang { namespace tidy { namespace copernica {

void ShouldBeNoexceptCheck::registerMatchers(MatchFinder *Finder)
{
    // FIXME: Add matchers.
    Finder->addMatcher(cxxConstructorDecl(hasParent(cxxRecordDecl(isDefinition(), isClass(), unless(isLambda()))),
                                          unless(hasDescendant(cxxConstructExpr(unless(hasDeclaration(cxxConstructorDecl(anyOf(isInStdNamespace(), isNoThrow()))))))),
                                          unless(hasDescendant(cxxThrowExpr())), unless(isNoThrow()), unless(isDeleted()),
                                          isDefinition() // need a definition or we get a lot of false positives
                                          )
                           .bind("constructor"),
                       this);
}

void ShouldBeNoexceptCheck::check(const MatchFinder::MatchResult &Result)
{
    // FIXME: Add callback implementation.
    const auto *Decl = Result.Nodes.getNodeAs<CXXConstructorDecl>("constructor");

    if (!Decl) return;

    const auto *ProtoType = Decl->getType()->getAs<FunctionProtoType>();

    if (!ProtoType) return;

    if (isUnresolvedExceptionSpec(ProtoType->getExceptionSpecType())) return;

    if (isNoexceptExceptionSpec(ProtoType->getExceptionSpecType())) return;

    // Add FixIt hints.
    SourceManager &SM = *Result.SourceManager;

    SourceLocation NoexceptLoc;

    if (Decl->getNumParams() > 0)
        NoexceptLoc = Decl->getParamDecl(Decl->getNumParams() - 1)->getSourceRange().getEnd();
    else
        NoexceptLoc = Lexer::getLocForEndOfToken(Decl->getBeginLoc(), 0, SM, Result.Context->getLangOpts());
    
    if (!NoexceptLoc.isValid()) return;

    NoexceptLoc = Lexer::findLocationAfterToken(NoexceptLoc, tok::r_paren, SM, Result.Context->getLangOpts(), false);
    auto Diag = diag(Decl->getLocation(), "constructor should be noexcept as it does not throw and has no throwing member variables %0") << NoexceptLoc.printToString(SM);

    if (!NoexceptLoc.isValid()) return;

    Diag << FixItHint::CreateInsertion(NoexceptLoc, " noexcept ");
}

} // namespace copernica
} // namespace tidy
} // namespace clang
