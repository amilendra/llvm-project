//===-- RISCV0MCAsmInfo.cpp - RISCV0 Asm properties -----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the RISCV0MCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "RISCV0MCAsmInfo.h"
#include "llvm/TargetParser/Triple.h"
using namespace llvm;

void RISCV0MCAsmInfo::anchor() {}

RISCV0MCAsmInfo::RISCV0MCAsmInfo(const Triple &TT) {
  CodePointerSize = CalleeSaveStackSlotSize = TT.isArch64Bit() ? 8 : 4;
  CommentString = "#";
  AlignmentIsInBytes = false;
  SupportsDebugInformation = true;
}
