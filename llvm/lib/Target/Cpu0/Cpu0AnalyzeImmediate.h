//===-- Cpu0AnalyzeImmediate.h - Analyze Immediates ------------*- C++ -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
#ifndef CPU0_ANALYZE_IMMEDIATE_H
#define CPU0_ANALYZE_IMMEDIATE_H

#include "Cpu0Config.h"

#include "llvm/ADT/SmallVector.h"
#include "llvm/Support/DataTypes.h"

namespace llvm {

class Cpu0AnalyzeImmediate {
public:
  struct Inst {
    unsigned Opc, ImmOpnd;
    Inst(unsigned Opc, unsigned ImmOpnd);
  };
  typedef SmallVector<Inst, 7> InstSeq;

  /// Analyze - Get an instruction sequence to load immediate Imm. The last
  /// instruction in the sequence must be an ADDiu if LastInstrIsADDiu is
  /// true;
  const InstSeq &Analyze(uint64_t Imm, unsigned Size, bool LastInstrIsADDiu);

private:
  typedef SmallVector<InstSeq, 5> InstSeqLs;

  /// AddInstr - Add I to all instruction sequences in SeqLs.
  void AddInstr(InstSeqLs &SeqLs, const Inst &I);

  /// GetInstSeqLsADDiu - Get instruction sequences which end with an ADDiu to
  /// load immediate Imm
  void GetInstSeqLsADDiu(uint64_t Imm, unsigned RemSize, InstSeqLs &SeqLs);

  /// GetInstSeqLsORi - Get instruction sequences which end with an ORi to
  /// load immediate Imm
  void GetInstSeqLsORi(uint64_t Imm, unsigned RemSize, InstSeqLs &SeqLs);

  /// GetInstSeqLsSHL - Get instruction sequences which end with a SHL to
  /// load immediate Imm
  void GetInstSeqLsSHL(uint64_t Imm, unsigned RemSize, InstSeqLs &SeqLs);

  /// GetInstSeqLs - Get instruction sequences to load immediate Imm.
  void GetInstSeqLs(uint64_t Imm, unsigned RemSize, InstSeqLs &SeqLs);

  /// ReplaceADDiuSHLWithLUi - Replace an ADDiu & SHL pair with a LUi.
  void ReplaceADDiuSHLWithLUi(InstSeq &Seq);

  /// GetShortestSeq - Find the shortest instruction sequence in SeqLs and
  /// return it in Insts.
  void GetShortestSeq(InstSeqLs &SeqLs, InstSeq &Insts);

  unsigned Size;
  unsigned ADDiu, ORi, SHL, LUi;
  InstSeq Insts;
};
} // namespace llvm

#endif
