//===- OR1KAsmPrinter.cpp - OR1K LLVM Assembly Printer -*- C++ -*--=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains a printer that converts from our internal representation
// of machine-dependent LLVM code to GAS-format OR1K assembly language.
//
//===----------------------------------------------------------------------===//

#include "OR1KAsmPrinter.h"
#include "OR1K.h"
#include "OR1KTargetMachine.h"
#include "TargetInfo/OR1KTargetInfo.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "or1k-asm-printer"

// Simple pseudo-instructions have their lowering (with expansion to real
// instructions) auto-generated.
#include "OR1KGenMCPseudoLowering.inc"

void OR1KAsmPrinter::emitInstruction(const MachineInstr *MI) {
  // Do any auto-generated pseudo lowerings.
  if (emitPseudoExpansionLowering(*OutStreamer, MI))
    return;

  MCInst TmpInst;
  if (!lowerOR1KMachineInstrToMCInst(MI, TmpInst, *this))
    EmitToStreamer(*OutStreamer, TmpInst);
}

bool OR1KAsmPrinter::runOnMachineFunction(MachineFunction &MF) {
  AsmPrinter::runOnMachineFunction(MF);
  return true;
}

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeOR1KAsmPrinter() {
  RegisterAsmPrinter<OR1KAsmPrinter> X(getTheOR1KTarget());
}
