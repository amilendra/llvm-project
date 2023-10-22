//===-- RISCV0MCTargetDesc.h - RISCV0 Target Descriptions -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides RISCV0 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_RISCV0_MCTARGETDESC_RISCV0MCTARGETDESC_H
#define LLVM_LIB_TARGET_RISCV0_MCTARGETDESC_RISCV0MCTARGETDESC_H

#include "llvm/Config/config.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/Support/DataTypes.h"
#include <memory>

namespace llvm {
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class StringRef;
class Target;
class Triple;
class raw_ostream;
class raw_pwrite_stream;

Target &getTheRISCV032Target();
Target &getTheRISCV064Target();

MCCodeEmitter *createRISCV0MCCodeEmitter(const MCInstrInfo &MCII,
                                         MCContext &Ctx);

MCAsmBackend *createRISCV0AsmBackend(const Target &T,
                                     const MCSubtargetInfo &STI,
                                     const MCRegisterInfo &MRI,
                                     const MCTargetOptions &Options);

std::unique_ptr<MCObjectTargetWriter> createRISCV0ELFObjectWriter(uint8_t OSABI,
                                                                  bool Is64Bit);
} // namespace llvm

// Defines symbolic names for RISC-V0 registers.
#define GET_REGINFO_ENUM
#include "RISCV0GenRegisterInfo.inc"

// Defines symbolic names for RISC-V0 instructions.
#define GET_INSTRINFO_ENUM
#include "RISCV0GenInstrInfo.inc"

#endif
