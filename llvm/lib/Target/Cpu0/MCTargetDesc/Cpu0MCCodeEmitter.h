//===-- Cpu0MCCodeEmitter.h - Convert Cpu0 Code to Machine Code -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the Cpu0MCCodeEmitter class.
//
//===----------------------------------------------------------------------===//
//

#ifndef LLVM_LIB_TARGET_CPU0_MCTARGETDESC_CPU0MCCODEEMITTER_H
#define LLVM_LIB_TARGET_CPU0_MCTARGETDESC_CPU0MCCODEEMITTER_H

#include "Cpu0Config.h"

#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/Support/DataTypes.h"

using namespace llvm;

namespace llvm {
class MCContext;
class MCExpr;
class MCInst;
class MCInstrInfo;
class MCFixup;
class MCOperand;
class MCSubtargetInfo;
class raw_ostream;

class Cpu0MCCodeEmitter : public MCCodeEmitter {
  Cpu0MCCodeEmitter(const Cpu0MCCodeEmitter &) = delete;
  void operator=(const Cpu0MCCodeEmitter &) = delete;
  const MCInstrInfo &MCII;
  MCContext &Ctx;
  bool IsLittleEndian;

public:
  Cpu0MCCodeEmitter(const MCInstrInfo &mcii, MCContext &Ctx_, bool IsLittle)
      : MCII(mcii), Ctx(Ctx_), IsLittleEndian(IsLittle) {}

  ~Cpu0MCCodeEmitter() override {}

  void encodeInstruction(const MCInst &MI, SmallVectorImpl<char> &CB,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;

  // getBinaryCodeForInstr - TableGen'erated function for getting the
  // binary encoding for an instruction.
  uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                 SmallVectorImpl<MCFixup> &Fixups,
                                 const MCSubtargetInfo &STI) const;

  // getBranch16TargetOpValue - Return binary encoding of the branch
  // target operand, such as BEQ, BNE. If the machine operand
  // requires relocation, record the relocation and return zero.
  unsigned getBranch16TargetOpValue(const MCInst &MI, unsigned OpNo,
                                    SmallVectorImpl<MCFixup> &Fixups,
                                    const MCSubtargetInfo &STI) const;

  // getBranch24TargetOpValue - Return binary encoding of the branch
  // target operand, such as JMP #BB01, JEQ, JSUB. If the machine operand
  // requires relocation, record the relocation and return zero.
  unsigned getBranch24TargetOpValue(const MCInst &MI, unsigned OpNo,
                                    SmallVectorImpl<MCFixup> &Fixups,
                                    const MCSubtargetInfo &STI) const;

  // getJumpTargetOpValue - Return binary encoding of the jump
  // target operand, such as JSUB #function_addr.
  // If the machine operand requires relocation,
  // record the relocation and return zero.
  unsigned getJumpTargetOpValue(const MCInst &MI, unsigned OpNo,
                                SmallVectorImpl<MCFixup> &Fixups,
                                const MCSubtargetInfo &STI) const;

  // getMachineOpValue - Return binary encoding of operand. If the machin
  // operand requires relocation, record the relocation and return zero.
  unsigned getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;

  unsigned getMemEncoding(const MCInst &MI, unsigned OpNo,
                          SmallVectorImpl<MCFixup> &Fixups,
                          const MCSubtargetInfo &STI) const;

  unsigned getExprOpValue(const MCExpr *Expr, SmallVectorImpl<MCFixup> &Fixups,
                          const MCSubtargetInfo &STI) const;
}; // class Cpu0MCCodeEmitter
} // namespace llvm.

#endif
