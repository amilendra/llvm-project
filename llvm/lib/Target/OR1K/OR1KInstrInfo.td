//===-- OR1KInstrInfo.td - Target Description for OR1K Target -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file describes the OR1K instructions in TableGen format.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Instruction format superclass
//===----------------------------------------------------------------------===//

include "OR1KInstrFormats.td"

// Extract bits 0-15 (low-end) of an immediate value.
def LO16 : SDNodeXForm<imm, [{
  return CurDAG->getTargetConstant((uint64_t)N->getZExtValue() & 0xffff,
                                   SDLoc(N), MVT::i32);
}]>;

// Extract bits 16-31 (high-end) of an immediate value.
// Transformation function: shift the immediate value down into the low bits.
def HI16 : SDNodeXForm<imm, [{
  return CurDAG->getTargetConstant((uint64_t)N->getZExtValue() >> 16,
                                   SDLoc(N), MVT::i32);
}]>;

// Negate immediate value
def NEG : SDNodeXForm<imm, [{
  return CurDAG->getTargetConstant(-N->getSExtValue(), SDLoc(N), MVT::i32);
}]>;


def brtarget : Operand<OtherVT>;
def calltarget : Operand<i32>;

def s6imm    : Operand<i32>;

def s16imm   : Operand<i32> {
  let PrintMethod = "printS16ImmOperand";
}

def immZExt6  : PatLeaf<(imm),
                [{return isInt<6>(N->getZExtValue()); }]>;

def immSExt16 : PatLeaf<(imm),
                [{return isInt<16>(N->getSExtValue()); }]>;

def immZExt16 : PatLeaf<(imm),
                [{return isUInt<16>(N->getZExtValue()); }], LO16>;

def immSExt16Neg : PatLeaf<(imm),
                   [{return isInt<16>(-N->getSExtValue()); }]>;

def i32lo16 : PatLeaf<(i32 imm), [{
  // i32lo16 predicate - true if the 32-bit immediate has only rightmost 16
  // bits set.
  return ((N->getZExtValue() & 0xFFFFULL) == N->getZExtValue());
}], LO16>;

def i32hi16 : PatLeaf<(i32 imm), [{
  // i32hi16 predicate - true if the 32-bit immediate has only leftmost 16
  // bits set.
  return ((N->getZExtValue() & 0xFFFF0000ULL) == N->getZExtValue());
}], HI16>;

// Addressing modes.
def ADDRri : ComplexPattern<i32, 2, "SelectAddr", [frameindex], []>;

// Address operands
def OR1KMemAsmOperand : AsmOperandClass {
 let Name = "Mem";
}
def MEMri : Operand<iPTR> {
  let ParserMatchClass = OR1KMemAsmOperand;
  let PrintMethod = "printMemOperand";
  let EncoderMethod = "getMemoryOpValue";
  let DecoderMethod = "DecodeMemoryValue";
  let MIOperandInfo = (ops GPR, i32imm);
}

// -------------------------------------------------- //
// ALU instructions
// -------------------------------------------------- //

class ALU_RI<bits<4> subOp, dag outs, dag ins, string asmstr,
             list<dag> pattern>
  : InstRI<subOp, outs, ins, asmstr, pattern> {
  bits<5> rD;
  bits<5> rA;
  bits<16> imm16;

  let Inst{25-21} = rD;
  let Inst{20-16} = rA;
  let Inst{15-0} = imm16;

  let format = AFrm;
}

class ALU_RIs<bits<4> subOp, string asmstr, SDNode OpNode>
  : ALU_RI<subOp, (outs GPR:$rD), (ins GPR:$rA, s16imm:$imm16),
           !strconcat(asmstr, "\t$rD, $rA, $imm16"),
           [(set GPR:$rD, (OpNode GPR:$rA, immSExt16:$imm16))]>;

class ALU_RIz<bits<4> subOp, string asmstr, SDNode OpNode>
  : ALU_RI<subOp, (outs GPR:$rD), (ins GPR:$rA, i32imm:$imm16),
           !strconcat(asmstr, "\t$rD, $rA, $imm16"),
           [(set GPR:$rD, (OpNode GPR:$rA, immZExt16:$imm16))]>;

class ALU_RR<bits<4> subOp, string asmstr, list<dag> pattern>
  : InstRR<0x8, (outs GPR:$rD), (ins GPR:$rA, GPR:$rB),
           !strconcat(asmstr, "\t$rD, $rA, $rB"), pattern> {
  bits<5> rD;
  bits<5> rA;
  bits<5> rB;
  bits<2> op2;
  bits<4> op3;

  let Inst{25-21} = rD;
  let Inst{20-16} = rA;
  let Inst{15-11} = rB;

  let Inst{9-8} = op2;
  let Inst{3-0} = op3;

  let op2 = 0;
  let op3 = subOp;
}

class ALU1_RR<bits<4> subOp, string asmstr, SDNode OpNode>
  : ALU_RR<subOp, asmstr,
           [(set GPR:$rD, (OpNode (i32 GPR:$rA), (i32 GPR:$rB)))]>;

class ALU2_RR<bits<2> subOp1, bits<4> subOp2, string asmstr, SDNode OpNode>
  : InstRR<0x8, (outs GPR:$rD), (ins GPR:$rA),
           !strconcat(asmstr, "\t$rD, $rA"),
           [(set GPR:$rD, (OpNode GPR:$rA))]> {
  bits<5> rD;
  bits<5> rA;
  bits<2> op2;
  bits<4> op3;

  let Inst{25-21} = rD;
  let Inst{20-16} = rA;

  let Inst{9-8} = op2;
  let Inst{3-0} = op3;

  let op2 = subOp1;
  let op3 = subOp2;
}

class ALU3_RR<bits<4> subOp1, bits<4> subOp2, string asmstr, list<dag> pattern>
  : InstRR<0x8, (outs GPR:$rD), (ins GPR:$rA),
           !strconcat(asmstr, "\t$rD, $rA"), pattern> {
  bits<5> rD;
  bits<5> rA;
  bits<4> op2;
  bits<4> op3;

  let Inst{25-21} = rD;
  let Inst{20-16} = rA;

  let Inst{9-6} = op2;
  let Inst{3-0} = op3;

  let op2 = subOp1;
  let op3 = subOp2;
}

def ADD  : ALU1_RR<0x0, "l.add", add>;
