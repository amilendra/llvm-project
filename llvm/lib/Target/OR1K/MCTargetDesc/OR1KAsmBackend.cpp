//===-- OR1KAsmBackend.cpp - OR1K Assembler Backend -*- C++ -*---===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the OR1KAsmBackend class.
//
//===----------------------------------------------------------------------===//

#include "OR1KAsmBackend.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCSection.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/EndianStream.h"
#include "llvm/Support/LEB128.h"
#include "llvm/Support/MathExtras.h"

#define DEBUG_TYPE "or1k-asmbackend"

using namespace llvm;

void OR1KAsmBackend::applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                                const MCValue &Target,
                                MutableArrayRef<char> Data, uint64_t Value,
                                bool IsResolved,
                                const MCSubtargetInfo *STI) const {
  // TODO: Apply the Value for given Fixup into the provided data fragment.
  return;
}

bool OR1KAsmBackend::shouldForceRelocation(const MCAssembler &Asm,
                                           const MCFixup &Fixup,
                                           const MCValue &Target,
                                           const MCSubtargetInfo *STI) {
  // TODO: Determine which relocation require special processing at linking
  // time.
  return false;
}

bool OR1KAsmBackend::writeNopData(raw_ostream &OS, uint64_t Count,
                                  const MCSubtargetInfo *STI) const {
  // Check for byte count not multiple of instruction word size
  if (Count % 4 != 0)
    return false;

  // The nop on OR1K is andi r0, r0, 0.
  for (; Count >= 4; Count -= 4)
    support::endian::write<uint32_t>(OS, 0x03400000, llvm::endianness::little);

  return true;
}

std::unique_ptr<MCObjectTargetWriter>
OR1KAsmBackend::createObjectTargetWriter() const {
  return createOR1KELFObjectWriter(OSABI, Is64Bit);
}

MCAsmBackend *llvm::createOR1KAsmBackend(const Target &T,
                                         const MCSubtargetInfo &STI,
                                         const MCRegisterInfo &MRI,
                                         const MCTargetOptions &Options) {
  const Triple &TT = STI.getTargetTriple();
  uint8_t OSABI = MCELFObjectTargetWriter::getOSABI(TT.getOS());
  return new OR1KAsmBackend(STI, OSABI, false /*TT.isArch64Bit*/);
}
