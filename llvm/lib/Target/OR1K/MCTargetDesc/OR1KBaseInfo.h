//=- OR1KBaseInfo.h - Top level definitions for OR1K MC -*- C++ -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains small standalone enum definitions and helper function
// definitions for the OR1K target useful for the compiler back-end and the
// MC libraries.
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_LIB_TARGET_OR1K_MCTARGETDESC_OR1KBASEINFO_H
#define LLVM_LIB_TARGET_OR1K_MCTARGETDESC_OR1KBASEINFO_H

#include "MCTargetDesc/OR1KMCTargetDesc.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/MC/MCInstrDesc.h"
#include "llvm/TargetParser/SubtargetFeature.h"

namespace llvm {

namespace OR1KABI {
enum ABI {
  ABI_ILP32S,
  ABI_ILP32F,
  ABI_ILP32D,
  ABI_LP64S,
  ABI_LP64F,
  ABI_LP64D,
  ABI_Unknown
};

ABI getTargetABI(StringRef ABIName);

// Returns the register used to hold the stack pointer after realignment.
MCRegister getBPReg();
} // namespace OR1KABI

} // namespace llvm

#endif // LLVM_LIB_TARGET_OR1K_MCTARGETDESC_OR1KBASEINFO_H
