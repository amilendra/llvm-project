//===-- RISCV0InstrFormats.td - RISCV0 Instruction Formats -*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//
//  These instruction format definitions are structured to match the
//  description in the RISC-V0 User-Level ISA specification as closely as
//  possible. For instance, the specification describes instructions with the
//  MSB (31st bit) on the left and the LSB (0th bit) on the right. This is
//  reflected in the order of parameters to each instruction class.
//
//  One area of divergence is in the description of immediates. The
//  specification describes immediate encoding in terms of bit-slicing
//  operations on the logical value represented. The immediate argument to
//  these instruction formats instead represents the bit sequence that will be
//  inserted into the instruction. e.g. although JAL's immediate is logically
//  a 21-bit value (where the LSB is always zero), we describe it as an imm20
//  to match how it is encoded.
//
//===----------------------------------------------------------------------===//

// The following opcode names and match those given in Table 19.1 in the
// RISC-V0 User-level ISA specification ("RISC-V0 base opcode map").
class RISCV0Opcode<bits<7> val> {
  bits<7> Value = val;
}
def OPC_LOAD      : RISCV0Opcode<0b0000011>;
def OPC_LOAD_FP   : RISCV0Opcode<0b0000111>;
def OPC_MISC_MEM  : RISCV0Opcode<0b0001111>;
def OPC_OP_IMM    : RISCV0Opcode<0b0010011>;
def OPC_AUIPC     : RISCV0Opcode<0b0010111>;
def OPC_OP_IMM_32 : RISCV0Opcode<0b0011011>;
def OPC_STORE     : RISCV0Opcode<0b0100011>;
def OPC_STORE_FP  : RISCV0Opcode<0b0100111>;
def OPC_AMO       : RISCV0Opcode<0b0101111>;
def OPC_OP        : RISCV0Opcode<0b0110011>;
def OPC_LUI       : RISCV0Opcode<0b0110111>;
def OPC_OP_32     : RISCV0Opcode<0b0111011>;
def OPC_MADD      : RISCV0Opcode<0b1000011>;
def OPC_MSUB      : RISCV0Opcode<0b1000111>;
def OPC_NMSUB     : RISCV0Opcode<0b1001011>;
def OPC_NMADD     : RISCV0Opcode<0b1001111>;
def OPC_OP_FP     : RISCV0Opcode<0b1010011>;
def OPC_BRANCH    : RISCV0Opcode<0b1100011>;
def OPC_JALR      : RISCV0Opcode<0b1100111>;
def OPC_JAL       : RISCV0Opcode<0b1101111>;
def OPC_SYSTEM    : RISCV0Opcode<0b1110011>;

class RVInst<dag outs, dag ins, string opcodestr, string argstr,
             list<dag> pattern>
    : Instruction {
  field bits<32> Inst;
  let Size = 4;

  bits<7> Opcode = 0;

  let Inst{6-0} = Opcode;

  let Namespace = "RISCV0";

  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString = opcodestr # "\t" # argstr;
  let Pattern = pattern;
}

// Pseudo instructions
class Pseudo<dag outs, dag ins, list<dag> pattern>
    : RVInst<outs, ins, "", "", pattern> {
  let isPseudo = 1;
  let isCodeGenOnly = 1;
}

// Instruction formats are listed in the order they appear in the RISC-V0
// instruction set manual (R, I, S, B, U, J) with sub-formats (e.g. RVInstR4,
// RVInstRAtomic) sorted alphabetically.

class RVInstR<bits<7> funct7, bits<3> funct3, RISCV0Opcode opcode, dag outs,
              dag ins, string opcodestr, string argstr>
    : RVInst<outs, ins, opcodestr, argstr, []> {
  bits<5> rs2;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31-25} = funct7;
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Opcode = opcode.Value;
}

class RVInstI<bits<3> funct3, RISCV0Opcode opcode, dag outs, dag ins,
              string opcodestr, string argstr>
    : RVInst<outs, ins, opcodestr, argstr, []> {
  bits<12> imm12;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31-20} = imm12;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Opcode = opcode.Value;
}

class RVInstIShift<bit arithshift, bits<3> funct3, RISCV0Opcode opcode,
                   dag outs, dag ins, string opcodestr, string argstr>
    : RVInst<outs, ins, opcodestr, argstr, []> {
  bits<5> shamt;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31} = 0;
  let Inst{30} = arithshift;
  let Inst{29-25} = 0;
  let Inst{24-20} = shamt;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Opcode = opcode.Value;
}

class RVInstS<bits<3> funct3, RISCV0Opcode opcode, dag outs, dag ins,
              string opcodestr, string argstr>
    : RVInst<outs, ins, opcodestr, argstr, []> {
  bits<12> imm12;
  bits<5> rs2;
  bits<5> rs1;

  let Inst{31-25} = imm12{11-5};
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = imm12{4-0};
  let Opcode = opcode.Value;
}

class RVInstB<bits<3> funct3, RISCV0Opcode opcode, dag outs, dag ins,
              string opcodestr, string argstr>
    : RVInst<outs, ins, opcodestr, argstr, []> {
  bits<12> imm12;
  bits<5> rs2;
  bits<5> rs1;

  let Inst{31} = imm12{11};
  let Inst{30-25} = imm12{9-4};
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-8} = imm12{3-0};
  let Inst{7} = imm12{10};
  let Opcode = opcode.Value;
}

class RVInstU<RISCV0Opcode opcode, dag outs, dag ins, string opcodestr,
              string argstr>
    : RVInst<outs, ins, opcodestr, argstr, []> {
  bits<20> imm20;
  bits<5> rd;

  let Inst{31-12} = imm20;
  let Inst{11-7} = rd;
  let Opcode = opcode.Value;
}

class RVInstJ<RISCV0Opcode opcode, dag outs, dag ins, string opcodestr,
              string argstr>
    : RVInst<outs, ins, opcodestr, argstr, []> {
  bits<20> imm20;
  bits<5> rd;

  let Inst{31} = imm20{19};
  let Inst{30-21} = imm20{9-0};
  let Inst{20} = imm20{10};
  let Inst{19-12} = imm20{18-11};
  let Inst{11-7} = rd;
  let Opcode = opcode.Value;
}
