//===--- Cpu0.cpp - Implement Cpu0 target feature support -------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements Cpu0 TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#include "Cpu0.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/MacroBuilder.h"
#include "clang/Basic/TargetBuiltins.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/TargetParser/TargetParser.h"

using namespace clang;
using namespace clang::targets;

ArrayRef<const char *> Cpu0TargetInfo::getGCCRegNames() const {
  // TODO: To be implemented in future.
  return {};
}

ArrayRef<TargetInfo::GCCRegAlias> Cpu0TargetInfo::getGCCRegAliases() const {
  // TODO: To be implemented in future.
  return {};
}

bool Cpu0TargetInfo::validateAsmConstraint(
    const char *&Name, TargetInfo::ConstraintInfo &Info) const {
  // TODO: To be implemented in future.
  return false;
}

void Cpu0TargetInfo::getTargetDefines(const LangOptions &Opts,
                                      MacroBuilder &Builder) const {
  Builder.defineMacro("__cpu0__");
  // TODO: Define more macros.
}

llvm::SmallVector<Builtin::InfosShard>
Cpu0TargetInfo::getTargetBuiltins() const {
  // TODO: To be implemented in future.
  return {};
}
