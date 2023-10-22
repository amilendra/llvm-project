//===-- RISCV0TargetInfo.cpp - RISCV0 Target Implementation ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "llvm/MC/TargetRegistry.h"
using namespace llvm;

namespace llvm {
Target &getTheRISCV032Target() {
  static Target TheRISCV032Target;
  return TheRISCV032Target;
}

Target &getTheRISCV064Target() {
  static Target TheRISCV064Target;
  return TheRISCV064Target;
}
} // namespace llvm

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISCV0TargetInfo() {
  RegisterTarget<Triple::riscv032> X(getTheRISCV032Target(), "riscv032",
                                     "32-bit RISC-V0", "RISCV0");
  RegisterTarget<Triple::riscv064> Y(getTheRISCV064Target(), "riscv064",
                                     "64-bit RISC-V0", "RISCV0");
}
