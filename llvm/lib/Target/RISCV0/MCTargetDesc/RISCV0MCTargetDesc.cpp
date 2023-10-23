//===-- RISCV0MCTargetDesc.cpp - RISCV0 Target Descriptions ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// This file provides RISCV0-specific target descriptions.
///
//===----------------------------------------------------------------------===//

#include "RISCV0MCTargetDesc.h"
#include "InstPrinter/RISCV0InstPrinter.h"
#include "RISCV0MCAsmInfo.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"

#define GET_INSTRINFO_MC_DESC
#include "RISCV0GenInstrInfo.inc"

#define GET_REGINFO_MC_DESC
#include "RISCV0GenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createRISCV0MCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitRISCV0MCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createRISCV0MCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitRISCV0MCRegisterInfo(X, RISCV0::X1);
  return X;
}

static MCAsmInfo *createRISCV0MCAsmInfo(const MCRegisterInfo &MRI,
                                        const Triple &TT,
                                        const MCTargetOptions &Options) {
  return new RISCV0MCAsmInfo(TT);
}

static MCInstPrinter *createRISCV0MCInstPrinter(const Triple &T,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCInstrInfo &MII,
                                                const MCRegisterInfo &MRI) {
  return new RISCV0InstPrinter(MAI, MII, MRI);
}

extern "C" void LLVMInitializeRISCV0TargetMC() {
  for (Target *T : {&getTheRISCV032Target(), &getTheRISCV064Target()}) {
    TargetRegistry::RegisterMCAsmInfo(*T, createRISCV0MCAsmInfo);
    TargetRegistry::RegisterMCInstrInfo(*T, createRISCV0MCInstrInfo);
    TargetRegistry::RegisterMCRegInfo(*T, createRISCV0MCRegisterInfo);
    TargetRegistry::RegisterMCAsmBackend(*T, createRISCV0AsmBackend);
    TargetRegistry::RegisterMCCodeEmitter(*T, createRISCV0MCCodeEmitter);
    TargetRegistry::RegisterMCInstPrinter(*T, createRISCV0MCInstPrinter);
  }
}
