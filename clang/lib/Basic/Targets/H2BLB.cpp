//===--- H2BLB.cpp - Implement H2BLB target feature support -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements H2BLB TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#include "Targets/H2BLB.h"
#include "clang/Basic/MacroBuilder.h"
#include "clang/Basic/TargetBuiltins.h"

using namespace clang;
using namespace clang::targets;

static constexpr int NumBuiltins =
    clang::H2BLB::LastTSBuiltin - Builtin::FirstTSBuiltin;

#define GET_BUILTIN_STR_TABLE
#include "clang/Basic/BuiltinsH2BLB.inc"
#undef GET_BUILTIN_STR_TABLE

static constexpr Builtin::Info BuiltinInfos[NumBuiltins] = {
#define GET_BUILTIN_INFOS
#include "clang/Basic/BuiltinsH2BLB.inc"
#undef GET_BUILTIN_INFOS
};

void H2BLBTargetInfo::getTargetDefines(const LangOptions &Opts,
                                       MacroBuilder &Builder) const {
  Builder.defineMacro("__H2BLB__", "1");
}

llvm::SmallVector<Builtin::InfosShard>
H2BLBTargetInfo::getTargetBuiltins() const {
  return {{&BuiltinStrings, BuiltinInfos}};
}
