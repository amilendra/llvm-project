//=- OR1KFrameLowering.h - TargetFrameLowering for OR1K -*- C++ -*--//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class implements OR1K-specific bits of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_OR1K_OR1KFRAMELOWERING_H
#define LLVM_LIB_TARGET_OR1K_OR1KFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {
class OR1KSubtarget;

class OR1KFrameLowering : public TargetFrameLowering {
  const OR1KSubtarget &STI;

public:
  explicit OR1KFrameLowering(const OR1KSubtarget &STI)
      : TargetFrameLowering(StackGrowsDown,
                            /*StackAlignment=*/Align(16),
                            /*LocalAreaOffset=*/0),
        STI(STI) {}

  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

  bool hasFP(const MachineFunction &MF) const override;
  bool hasBP(const MachineFunction &MF) const;
};
} // namespace llvm
#endif // LLVM_LIB_TARGET_OR1K_OR1KFRAMELOWERING_H
