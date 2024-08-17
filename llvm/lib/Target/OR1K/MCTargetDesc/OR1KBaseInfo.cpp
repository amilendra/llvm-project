//= OR1KBaseInfo.cpp - Top level definitions for OR1K MC -*- C++ -*-//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements helper functions for the OR1K target useful for the
// compiler back-end and the MC libraries.
//
//===----------------------------------------------------------------------===//

#include "OR1KBaseInfo.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/TargetParser/Triple.h"

namespace llvm {

namespace OR1KABI {

ABI getTargetABI(StringRef ABIName) {
  auto TargetABI = StringSwitch<ABI>(ABIName)
                       .Case("ilp32s", ABI_ILP32S)
                       .Case("ilp32f", ABI_ILP32F)
                       .Case("ilp32d", ABI_ILP32D)
                       .Case("lp64s", ABI_LP64S)
                       .Case("lp64f", ABI_LP64F)
                       .Case("lp64d", ABI_LP64D)
                       .Default(ABI_Unknown);
  return TargetABI;
}

// FIXME: other register?
MCRegister getBPReg() { return OR1K::R31; }

} // namespace OR1KABI

} // namespace llvm
