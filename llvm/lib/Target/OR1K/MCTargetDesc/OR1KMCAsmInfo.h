//===-- OR1KMCAsmInfo.h - OR1K Asm Info --------------*- C++ -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the OR1KMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_OR1K_MCTARGETDESC_OR1KMCASMINFO_H
#define LLVM_LIB_TARGET_OR1K_MCTARGETDESC_OR1KMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class Triple;

class OR1KMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit OR1KMCAsmInfo(const Triple &TargetTriple);
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_OR1K_MCTARGETDESC_OR1KMCASMINFO_H
