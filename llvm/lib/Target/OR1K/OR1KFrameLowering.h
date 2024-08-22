//===-- OR1KFrameLowering.h - Define frame lowering for OR1K ---*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//
//===----------------------------------------------------------------------===//

#ifndef OR1K_FRAMEINFO_H
#define OR1K_FRAMEINFO_H

#include "OR1K.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/Support/Alignment.h"

namespace llvm {
class OR1KSubtarget;

class OR1KFrameLowering : public TargetFrameLowering {
private:
  void determineFrameLayout(MachineFunction &MF) const;
  void replaceAdjDynAllocPseudo(MachineFunction &MF) const;

public:
  explicit OR1KFrameLowering()
      : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(4), 0) {}

  /// emitProlog/emitEpilog - These methods insert prolog and epilog code into
  /// the function.
  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

  MachineBasicBlock::iterator
  eliminateCallFramePseudoInstr(MachineFunction &MF, MachineBasicBlock &MBB,
                                MachineBasicBlock::iterator I) const override;

  bool hasFP(const MachineFunction &MF) const override;
  void determineCalleeSaves(MachineFunction &MF, BitVector &SavedRegs,
                            RegScavenger *RS = nullptr) const override;
};
} // namespace llvm

#endif
