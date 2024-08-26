//===-- OR1K.h - Top-level interface for OR1K ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// OR1K back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_OR1K_OR1K_H
#define LLVM_LIB_TARGET_OR1K_OR1K_H

#include "llvm/Target/TargetMachine.h"

namespace llvm {
class OR1KTargetMachine;
class AsmPrinter;
class FunctionPass;
class PassRegistry;
class MCInst;
class MCOperand;
class MachineInstr;
class MachineOperand;

bool lowerOR1KMachineInstrToMCInst(const MachineInstr *MI, MCInst &OutMI,
                                   AsmPrinter &AP);
bool lowerOR1KMachineOperandToMCOperand(const MachineOperand &MO,
                                        MCOperand &MCOp, const AsmPrinter &AP);

FunctionPass *createOR1KISelDag(OR1KTargetMachine &TM);

void initializeOR1KDAGToDAGISelLegacyPass(PassRegistry &);
} // namespace llvm

#endif // LLVM_LIB_TARGET_OR1K_OR1K_H
