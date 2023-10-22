//===-- RISCV0MCAsmInfo.h - RISCV0 Asm Info --------------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the RISCV0MCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_RISCV0_MCTARGETDESC_RISCV0MCASMINFO_H
#define LLVM_LIB_TARGET_RISCV0_MCTARGETDESC_RISCV0MCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class Triple;

class RISCV0MCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit RISCV0MCAsmInfo(const Triple &TargetTriple);
};

} // namespace llvm

#endif
