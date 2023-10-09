//===-- Cpu0TargetInfo.cpp - Cpu0 Target Implementation ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/Cpu0TargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
using namespace llvm;

Target &llvm::getTheCpu0BETarget() {
  static Target TheCpu0BETarget;
  return TheCpu0BETarget;
}

Target &llvm::getTheCpu0LETarget() {
  static Target TheCpu0LETarget;
  return TheCpu0LETarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeCpu0TargetInfo() {
  RegisterTarget<Triple::cpu0, /*HasJIT=*/false> X(
      getTheCpu0BETarget(), "cpu0", "CPU0 (32-bit big endian)", "Cpu0");
  RegisterTarget<Triple::cpu0el, /*HasJIT=*/false> Y(
      getTheCpu0LETarget(), "cpu0el", "CPU0 (32-bit little endian)", "Cpu0");
}
