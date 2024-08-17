//===-- OR1KSubtarget.cpp - OR1K Subtarget Information -*- C++ -*--=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the OR1K specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "OR1KSubtarget.h"
#include "OR1KFrameLowering.h"

using namespace llvm;

#define DEBUG_TYPE "or1k-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "OR1KGenSubtargetInfo.inc"

void OR1KSubtarget::anchor() {}

OR1KSubtarget &
OR1KSubtarget::initializeSubtargetDependencies(const Triple &TT, StringRef CPU,
                                               StringRef TuneCPU, StringRef FS,
                                               StringRef ABIName) {
  //  Is64Bit = false;
  if (CPU.empty())
    CPU = "generic";

  if (TuneCPU.empty())
    TuneCPU = CPU;

  ParseSubtargetFeatures(CPU, TuneCPU, FS);

  // TODO: ILP32{S,F} LP64{S,F}
  TargetABI = OR1KABI::ABI_ILP32D;
  return *this;
}

OR1KSubtarget::OR1KSubtarget(const Triple &TT, StringRef CPU, StringRef TuneCPU,
                             StringRef FS, StringRef ABIName,
                             const TargetMachine &TM)
    : OR1KGenSubtargetInfo(TT, CPU, TuneCPU, FS),
      FrameLowering(
          initializeSubtargetDependencies(TT, CPU, TuneCPU, FS, ABIName)),
      InstrInfo(*this), RegInfo(getHwMode()), TLInfo(TM, *this) {}
