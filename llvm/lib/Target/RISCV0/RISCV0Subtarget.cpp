//===- RISCV0Subtarget.cpp - RISCV0 Subtarget Information ---------*- C++ -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the RISCV0 specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#include "RISCV0Subtarget.h"
#include "MCTargetDesc/RISCV0MCTargetDesc.h"
#include "llvm/Support/Debug.h"
#include "llvm/Target/TargetMachine.h"

#define DEBUG_TYPE "riscv0-subtarget"

#define GET_SUBTARGETINFO_CTOR
#define GET_SUBTARGETINFO_TARGET_DESC
#include "RISCV0GenSubtargetInfo.inc"

using namespace llvm;

RISCV0Subtarget::RISCV0Subtarget(const Triple &TT, StringRef CPU,
                                 StringRef TuneCPU, StringRef FS)
    : RISCV0GenSubtargetInfo(TT, CPU, TuneCPU, FS) {
  // StringRef CPU = "generic";

  // Parse features string.
  ParseSubtargetFeatures(CPU, /*TuneCPU=*/CPU, FS);
}
