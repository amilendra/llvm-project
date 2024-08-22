//===- OR1KSubtarget.cpp - OR1K Subtarget Information -----------*- C++ -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the OR1K specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#include "OR1KSubtarget.h"
#include "OR1K.h"

using namespace llvm;

#define DEBUG_TYPE "or1k-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "OR1KGenSubtargetInfo.inc"

void OR1KSubtarget::anchor() {}

OR1KSubtarget &OR1KSubtarget::initializeSubtargetDependencies(StringRef CPU,
                                                              StringRef FS) {
  StringRef CPUName = CPU;
  if (CPUName.empty())
    CPUName = "generic";

  ParseSubtargetFeatures(CPUName, /*TuneCPU*/ CPU, FS);
  return *this;
}

OR1KSubtarget::OR1KSubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                             const OR1KTargetMachine &TM)
    : OR1KGenSubtargetInfo(TT, CPU, /*TuneCPU*/ CPU, FS), HasMul(false),
      HasDiv(false), HasRor(false), HasCmov(false), HasAddc(false),
      HasFfl1(false), HasExt(false), HasInterrupts(true),
      TLInfo(TM, initializeSubtargetDependencies(CPU, FS)), TSInfo() {}
