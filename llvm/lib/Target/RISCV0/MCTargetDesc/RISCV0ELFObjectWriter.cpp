//===-- RISCV0ELFObjectWriter.cpp - RISCV0 ELF Writer ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/RISCV0MCTargetDesc.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

namespace {
class RISCV0ELFObjectWriter : public MCELFObjectTargetWriter {
public:
  RISCV0ELFObjectWriter(uint8_t OSABI, bool Is64Bit);

  ~RISCV0ELFObjectWriter() override;

protected:
  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override;
};
} // namespace

RISCV0ELFObjectWriter::RISCV0ELFObjectWriter(uint8_t OSABI, bool Is64Bit)
    : MCELFObjectTargetWriter(Is64Bit, OSABI, ELF::EM_RISCV0,
                              /*HasRelocationAddend*/ true) {}

RISCV0ELFObjectWriter::~RISCV0ELFObjectWriter() {}

unsigned RISCV0ELFObjectWriter::getRelocType(MCContext &Ctx,
                                             const MCValue &Target,
                                             const MCFixup &Fixup,
                                             bool IsPCRel) const {
  report_fatal_error("invalid fixup kind!");
}

std::unique_ptr<MCObjectTargetWriter>
llvm::createRISCV0ELFObjectWriter(uint8_t OSABI, bool Is64Bit) {
  return std::make_unique<RISCV0ELFObjectWriter>(OSABI, Is64Bit);
}
