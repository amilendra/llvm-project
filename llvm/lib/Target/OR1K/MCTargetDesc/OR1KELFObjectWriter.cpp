//===-- OR1KELFObjectWriter.cpp - OR1K ELF Writer ---*- C++ -*---===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/OR1KMCTargetDesc.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

namespace {
class OR1KELFObjectWriter : public MCELFObjectTargetWriter {
public:
  OR1KELFObjectWriter(uint8_t OSABI, bool Is64Bit);

  ~OR1KELFObjectWriter() override;

  // Return true if the given relocation must be with a symbol rather than
  // section plus offset.
  bool needsRelocateWithSymbol(const MCValue &Val, const MCSymbol &Sym,
                               unsigned Type) const override {
    return true;
  }

protected:
  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override;
};
} // namespace

OR1KELFObjectWriter::OR1KELFObjectWriter(uint8_t OSABI, bool Is64Bit)
    : MCELFObjectTargetWriter(Is64Bit, OSABI, ELF::EM_OR1K,
                              /*HasRelocationAddend*/ true) {}

OR1KELFObjectWriter::~OR1KELFObjectWriter() {}

unsigned OR1KELFObjectWriter::getRelocType(MCContext &Ctx,
                                           const MCValue &Target,
                                           const MCFixup &Fixup,
                                           bool IsPCRel) const {
  const MCExpr *Expr = Fixup.getValue();
  // Determine the type of the relocation
  unsigned Kind = Fixup.getTargetKind();

  if (Kind >= FirstLiteralRelocationKind)
    return Kind - FirstLiteralRelocationKind;

  switch (Kind) {
  // TODO: Implement this when we defined fixup kind.
  default:
    return ELF::R_LARCH_NONE;
  }
}

std::unique_ptr<MCObjectTargetWriter>
llvm::createOR1KELFObjectWriter(uint8_t OSABI, bool Is64Bit) {
  return std::make_unique<OR1KELFObjectWriter>(OSABI, Is64Bit);
}
