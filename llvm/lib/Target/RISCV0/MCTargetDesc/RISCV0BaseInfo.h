//===-- RISCV0BaseInfo.h - Top level definitions for RISCV0 MC --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains small standalone enum definitions for the RISCV0 target
// useful for the compiler back-end and the MC libraries.
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_LIB_TARGET_RISCV0_MCTARGETDESC_RISCV0BASEINFO_H
#define LLVM_LIB_TARGET_RISCV0_MCTARGETDESC_RISCV0BASEINFO_H

#include "RISCV0MCTargetDesc.h"

namespace llvm {

// RISCV0II - This namespace holds all of the target specific flags that
// instruction info tracks. All definitions must match RISCV0InstrFormats.td.
namespace RISCV0II {
enum {
  InstFormatPseudo = 0,
  InstFormatR = 1,
  InstFormatI = 2,
  InstFormatS = 3,
  InstFormatB = 4,
  InstFormatU = 5,
  InstFormatOther = 6,

  InstFormatMask = 15
};
enum {
  MO_None,
  MO_LO,
  MO_HI,
  MO_PCREL_HI,
};
} // namespace RISCV0II

// Describes the predecessor/successor bits used in the FENCE instruction.
namespace RISCV0FenceField {
enum FenceField {
  I = 8,
  O = 4,
  R = 2,
  W = 1
};
}
} // namespace llvm

#endif
