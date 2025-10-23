//===-- Cpu0MCInstLower.h - Lower MachineInstr to MCInst -------*- C++ -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CPU0_CPU0MCINSTLOWER_H
#define LLVM_LIB_TARGET_CPU0_CPU0MCINSTLOWER_H

#include "Cpu0Config.h"

#include "MCTargetDesc/Cpu0MCExpr.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/Support/Compiler.h"

namespace llvm {
class MCContext;
class MCInst;
class MCOperand;
class MachineInstr;
class MachineFunction;
class Cpu0AsmPrinter;

//@1 {
/// This class is used to lower an MachineInstr into an MCInst.
class LLVM_LIBRARY_VISIBILITY Cpu0MCInstLower {
  //@2
  typedef MachineOperand::MachineOperandType MachineOperandType;
  MCContext *Ctx;
  Cpu0AsmPrinter &AsmPrinter;

public:
  Cpu0MCInstLower(Cpu0AsmPrinter &asmprinter);
  void Initialize(MCContext *C);
  void Lower(const MachineInstr *MI, MCInst &OutMI) const;
  MCOperand LowerOperand(const MachineOperand &MO, unsigned offset = 0) const;
  void LowerCPLOAD(SmallVector<MCInst, 4> &MCInsts);

private:
  MCOperand LowerSymbolOperand(const MachineOperand &MO,
                               MachineOperandType MOTy, unsigned Offset) const;
};
} // namespace llvm

#endif
