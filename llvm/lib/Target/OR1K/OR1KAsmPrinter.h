//===- OR1KAsmPrinter.h - OR1K LLVM Assembly Printer -*- C++ -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// OR1K Assembly printer class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_OR1K_OR1KASMPRINTER_H
#define LLVM_LIB_TARGET_OR1K_OR1KASMPRINTER_H

#include "OR1KSubtarget.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/Compiler.h"

namespace llvm {

class OR1KAsmPrinter : public AsmPrinter {
public:
  explicit OR1KAsmPrinter(TargetMachine &TM,
                          std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)) {}

  StringRef getPassName() const override { return "OR1K Assembly Printer"; }

  bool runOnMachineFunction(MachineFunction &MF) override;

  void emitInstruction(const MachineInstr *MI) override;

  // tblgen'erated function.
  bool lowerPseudoInstExpansion(const MachineInstr *MI, MCInst &Inst);
  bool emitPseudoExpansionLowering(MCStreamer &OutStreamer,
                                   const MachineInstr *MI) {
    return false;
  }
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_OR1K_OR1KASMPRINTER_H
