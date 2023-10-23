//===-- RISCV0AsmParser.cpp - Parse RISCV0 assembly to MCInst instructions ===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/RISCV0MCTargetDesc.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCParser/MCAsmLexer.h"
#include "llvm/MC/MCParser/MCParsedAsmOperand.h"
#include "llvm/MC/MCParser/MCTargetAsmParser.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Casting.h"

using namespace llvm;

namespace {
struct RISCV0Operand;

class RISCV0AsmParser : public MCTargetAsmParser {
  SMLoc getLoc() const { return getParser().getTok().getLoc(); }

  bool MatchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                               OperandVector &Operands, MCStreamer &Out,
                               uint64_t &ErrorInfo,
                               bool MatchingInlineAsm) override;

  bool parseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) override;
  ParseStatus tryParseRegister(MCRegister &Reg, SMLoc &StartLoc,
                               SMLoc &EndLoc) override;

  bool ParseInstruction(ParseInstructionInfo &Info, StringRef Name,
                        SMLoc NameLoc, OperandVector &Operands) override;

  bool ParseDirective(AsmToken DirectiveID) override;

// Auto-generated instruction matching functions
#define GET_ASSEMBLER_HEADER
#include "RISCV0GenAsmMatcher.inc"

  ParseStatus parseImmediate(OperandVector &Operands);
  ParseStatus parseRegister(OperandVector &Operands);

  bool parseOperand(OperandVector &Operands);

public:
  enum RISCV0MatchResultTy {
    Match_Dummy = FIRST_TARGET_MATCH_RESULT_TY,
#define GET_OPERAND_DIAGNOSTIC_TYPES
#include "RISCV0GenAsmMatcher.inc"
#undef GET_OPERAND_DIAGNOSTIC_TYPES
  };

  RISCV0AsmParser(const MCSubtargetInfo &STI, MCAsmParser &Parser,
                  const MCInstrInfo &MII, const MCTargetOptions &Options)
      : MCTargetAsmParser(Options, STI, MII) {
    setAvailableFeatures(ComputeAvailableFeatures(STI.getFeatureBits()));
  }
};

/// RISCV0Operand - Instances of this class represent a parsed machine
/// instruction
struct RISCV0Operand : public MCParsedAsmOperand {

  enum KindTy {
    Token,
    Register,
    Immediate,
  } Kind;

  struct RegOp {
    unsigned RegNum;
  };

  struct ImmOp {
    const MCExpr *Val;
  };

  SMLoc StartLoc, EndLoc;
  union {
    StringRef Tok;
    RegOp Reg;
    ImmOp Imm;
  };

  RISCV0Operand(KindTy K) : MCParsedAsmOperand(), Kind(K) {}

public:
  RISCV0Operand(const RISCV0Operand &o) : MCParsedAsmOperand() {
    Kind = o.Kind;
    StartLoc = o.StartLoc;
    EndLoc = o.EndLoc;
    switch (Kind) {
    case Register:
      Reg = o.Reg;
      break;
    case Immediate:
      Imm = o.Imm;
      break;
    case Token:
      Tok = o.Tok;
      break;
    }
  }

  bool isToken() const override { return Kind == Token; }
  bool isReg() const override { return Kind == Register; }
  bool isImm() const override { return Kind == Immediate; }
  bool isMem() const override { return false; }

  bool isConstantImm() const {
    return isImm() && dyn_cast<MCConstantExpr>(getImm());
  }

  int64_t getConstantImm() const {
    const MCExpr *Val = getImm();
    return static_cast<const MCConstantExpr *>(Val)->getValue();
  }

  bool isSImm12() const {
    return (isConstantImm() && isInt<12>(getConstantImm()));
  }

  /// getStartLoc - Gets location of the first token of this operand
  SMLoc getStartLoc() const override { return StartLoc; }
  /// getEndLoc - Gets location of the last token of this operand
  SMLoc getEndLoc() const override { return EndLoc; }

  unsigned getReg() const override {
    assert(Kind == Register && "Invalid type access!");
    return Reg.RegNum;
  }

  const MCExpr *getImm() const {
    assert(Kind == Immediate && "Invalid type access!");
    return Imm.Val;
  }

  StringRef getToken() const {
    assert(Kind == Token && "Invalid type access!");
    return Tok;
  }

  void print(raw_ostream &OS) const override {
    switch (Kind) {
    case Immediate:
      OS << *getImm();
      break;
    case Register:
      OS << "<register x";
      OS << getReg() << ">";
      break;
    case Token:
      OS << "'" << getToken() << "'";
      break;
    }
  }

  static std::unique_ptr<RISCV0Operand> createToken(StringRef Str, SMLoc S) {
    auto Op = std::make_unique<RISCV0Operand>(Token);
    Op->Tok = Str;
    Op->StartLoc = S;
    Op->EndLoc = S;
    return Op;
  }

  static std::unique_ptr<RISCV0Operand> createReg(unsigned RegNo, SMLoc S,
                                                  SMLoc E) {
    auto Op = std::make_unique<RISCV0Operand>(Register);
    Op->Reg.RegNum = RegNo;
    Op->StartLoc = S;
    Op->EndLoc = E;
    return Op;
  }

  static std::unique_ptr<RISCV0Operand> createImm(const MCExpr *Val, SMLoc S,
                                                  SMLoc E) {
    auto Op = std::make_unique<RISCV0Operand>(Immediate);
    Op->Imm.Val = Val;
    Op->StartLoc = S;
    Op->EndLoc = E;
    return Op;
  }

  void addExpr(MCInst &Inst, const MCExpr *Expr) const {
    assert(Expr && "Expr shouldn't be null!");
    if (auto *CE = dyn_cast<MCConstantExpr>(Expr))
      Inst.addOperand(MCOperand::createImm(CE->getValue()));
    else
      Inst.addOperand(MCOperand::createExpr(Expr));
  }

  // Used by the TableGen Code
  void addRegOperands(MCInst &Inst, unsigned N) const {
    assert(N == 1 && "Invalid number of operands!");
    Inst.addOperand(MCOperand::createReg(getReg()));
  }

  void addImmOperands(MCInst &Inst, unsigned N) const {
    assert(N == 1 && "Invalid number of operands!");
    addExpr(Inst, getImm());
  }
};
} // end anonymous namespace.

#define GET_REGISTER_MATCHER
#define GET_MATCHER_IMPLEMENTATION
#include "RISCV0GenAsmMatcher.inc"

bool RISCV0AsmParser::MatchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                                              OperandVector &Operands,
                                              MCStreamer &Out,
                                              uint64_t &ErrorInfo,
                                              bool MatchingInlineAsm) {
  MCInst Inst;
  SMLoc ErrorLoc;

  switch (MatchInstructionImpl(Operands, Inst, ErrorInfo, MatchingInlineAsm)) {
  default:
    break;
  case Match_Success:
    Inst.setLoc(IDLoc);
    Out.emitInstruction(Inst, getSTI());
    return false;
  case Match_MissingFeature:
    return Error(IDLoc, "instruction use requires an option to be enabled");
  case Match_MnemonicFail:
    return Error(IDLoc, "unrecognized instruction mnemonic");
  case Match_InvalidOperand:
    ErrorLoc = IDLoc;
    if (ErrorInfo != ~0U) {
      if (ErrorInfo >= Operands.size())
        return Error(ErrorLoc, "too few operands for instruction");

      ErrorLoc = ((RISCV0Operand &)*Operands[ErrorInfo]).getStartLoc();
      if (ErrorLoc == SMLoc())
        ErrorLoc = IDLoc;
    }
    return Error(ErrorLoc, "invalid operand for instruction");
  case Match_InvalidSImm12:
    SMLoc ErrorLoc = ((RISCV0Operand &)*Operands[ErrorInfo]).getStartLoc();
    return Error(ErrorLoc,
                 "immediate must be an integer in the range [-2048, 2047]");
  }

  llvm_unreachable("Unknown match type detected!");
}

bool RISCV0AsmParser::parseRegister(MCRegister &Reg, SMLoc &StartLoc,
                                    SMLoc &EndLoc) {
  if (!tryParseRegister(Reg, StartLoc, EndLoc).isSuccess())
    return Error(StartLoc, "invalid register name");
  return false;
}

ParseStatus RISCV0AsmParser::tryParseRegister(MCRegister &RegNo,
                                              SMLoc &StartLoc, SMLoc &EndLoc) {
  const AsmToken &Tok = getParser().getTok();
  StartLoc = Tok.getLoc();
  EndLoc = Tok.getEndLoc();
  RegNo = 0;
  StringRef Name = getLexer().getTok().getIdentifier();

  if (!MatchRegisterName(Name) || !MatchRegisterAltName(Name)) {
    getParser().Lex(); // Eat identifier token.
    return ParseStatus::NoMatch;
  }

  return ParseStatus::Success;
}

ParseStatus RISCV0AsmParser::parseRegister(OperandVector &Operands) {
  SMLoc S = getLoc();
  SMLoc E = SMLoc::getFromPointer(S.getPointer() - 1);

  switch (getLexer().getKind()) {
  default:
    return ParseStatus::NoMatch;
  case AsmToken::Identifier:
    StringRef Name = getLexer().getTok().getIdentifier();
    unsigned RegNo = MatchRegisterName(Name);
    if (RegNo == 0) {
      RegNo = MatchRegisterAltName(Name);
      if (RegNo == 0)
        return ParseStatus::NoMatch;
    }
    getLexer().Lex();
    Operands.push_back(RISCV0Operand::createReg(RegNo, S, E));
  }
  return ParseStatus::Success;
}

ParseStatus RISCV0AsmParser::parseImmediate(OperandVector &Operands) {
  switch (getLexer().getKind()) {
  default:
    return ParseStatus::NoMatch;
  case AsmToken::LParen:
  case AsmToken::Minus:
  case AsmToken::Plus:
  case AsmToken::Integer:
  case AsmToken::String:
    break;
  }

  const MCExpr *IdVal;
  SMLoc S = getLoc();
  if (getParser().parseExpression(IdVal))
    return ParseStatus::Failure;

  SMLoc E = SMLoc::getFromPointer(S.getPointer() - 1);
  Operands.push_back(RISCV0Operand::createImm(IdVal, S, E));
  return ParseStatus::Success;
}

/// Looks at a token type and creates the relevant operand
/// from this information, adding to Operands.
/// If operand was parsed, returns false, else true.
bool RISCV0AsmParser::parseOperand(OperandVector &Operands) {
  // Attempt to parse token as register
  if (parseRegister(Operands).isSuccess())
    return false;

  // Attempt to parse token as an immediate
  if (parseImmediate(Operands).isSuccess())
    return false;

  // Finally we have exhausted all options and must declare defeat.
  Error(getLoc(), "unknown operand");
  return true;
}

bool RISCV0AsmParser::ParseInstruction(ParseInstructionInfo &Info,
                                       StringRef Name, SMLoc NameLoc,
                                       OperandVector &Operands) {
  // First operand is token for instruction
  Operands.push_back(RISCV0Operand::createToken(Name, NameLoc));

  // If there are no more operands, then finish
  if (getLexer().is(AsmToken::EndOfStatement))
    return false;

  // Parse first operand
  if (parseOperand(Operands))
    return true;

  // Parse until end of statement, consuming commas between operands
  while (getLexer().is(AsmToken::Comma)) {
    // Consume comma token
    getLexer().Lex();

    // Parse next operand
    if (parseOperand(Operands))
      return true;
  }

  if (getLexer().isNot(AsmToken::EndOfStatement)) {
    SMLoc Loc = getLexer().getLoc();
    getParser().eatToEndOfStatement();
    return Error(Loc, "unexpected token");
  }

  getParser().Lex(); // Consume the EndOfStatement.
  return false;
}

bool RISCV0AsmParser::ParseDirective(AsmToken DirectiveID) { return true; }

extern "C" void LLVMInitializeRISCV0AsmParser() {
  RegisterMCAsmParser<RISCV0AsmParser> X(getTheRISCV032Target());
  RegisterMCAsmParser<RISCV0AsmParser> Y(getTheRISCV064Target());
}
