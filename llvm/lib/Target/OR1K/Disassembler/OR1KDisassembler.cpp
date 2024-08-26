//===-- OR1KDisassembler.cpp - Disassembler for OR1K ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the OR1KDisassembler class.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/OR1KBaseInfo.h"
#include "MCTargetDesc/OR1KMCTargetDesc.h"
#include "TargetInfo/OR1KTargetInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDecoderOps.h"
#include "llvm/MC/MCDisassembler/MCDisassembler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Endian.h"

using namespace llvm;

#define DEBUG_TYPE "or1k-disassembler"

typedef MCDisassembler::DecodeStatus DecodeStatus;

namespace {
class OR1KDisassembler : public MCDisassembler {
public:
  OR1KDisassembler(const MCSubtargetInfo &STI, MCContext &Ctx)
      : MCDisassembler(STI, Ctx) {}

  DecodeStatus getInstruction(MCInst &Instr, uint64_t &Size,
                              ArrayRef<uint8_t> Bytes, uint64_t Address,
                              raw_ostream &CStream) const override;
};
} // end anonymous namespace

static MCDisassembler *createOR1KDisassembler(const Target &T,
                                              const MCSubtargetInfo &STI,
                                              MCContext &Ctx) {
  return new OR1KDisassembler(STI, Ctx);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeOR1KDisassembler() {
  // Register the disassembler.
  TargetRegistry::RegisterMCDisassembler(getTheOR1KTarget(),
                                         createOR1KDisassembler);
}

#include "OR1KGenDisassemblerTables.inc"

DecodeStatus OR1KDisassembler::getInstruction(MCInst &MI, uint64_t &Size,
                                              ArrayRef<uint8_t> Bytes,
                                              uint64_t Address,
                                              raw_ostream &CS) const {
  uint32_t Insn;
  DecodeStatus Result;

  // We want to read exactly 4 bytes of data because all OR1K instructions
  // are fixed 32 bits.
  if (Bytes.size() < 4) {
    Size = 0;
    return MCDisassembler::Fail;
  }

  Insn = support::endian::read32be(Bytes.data());
  // Calling the auto-generated decoder function.
  Result = decodeInstruction(DecoderTableOR1K32, MI, Insn, Address, this, STI);
  Size = 4;

  return Result;
}
