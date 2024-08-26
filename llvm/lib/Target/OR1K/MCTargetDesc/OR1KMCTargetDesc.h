//===- OR1KMCTargetDesc.h - OR1K Target Descriptions --*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides OR1K specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_OR1K_MCTARGETDESC_OR1KMCTARGETDESC_H
#define LLVM_LIB_TARGET_OR1K_MCTARGETDESC_OR1KMCTARGETDESC_H

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
class Target;

MCCodeEmitter *createOR1KMCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx);

MCAsmBackend *createOR1KAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                   const MCRegisterInfo &MRI,
                                   const MCTargetOptions &Options);

std::unique_ptr<MCObjectTargetWriter> createOR1KELFObjectWriter(uint8_t OSABI,
                                                                bool Is64Bit);

} // namespace llvm

// Defines symbolic names for OR1K registers.
#define GET_REGINFO_ENUM
#include "OR1KGenRegisterInfo.inc"

// Defines symbolic names for OR1K instructions.
#define GET_INSTRINFO_ENUM
#include "OR1KGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "OR1KGenSubtargetInfo.inc"

#endif // LLVM_LIB_TARGET_OR1K_MCTARGETDESC_OR1KMCTARGETDESC_H
