//===-- Cpu0InstrFormats.td - Cpu0 Instruction Formats -----*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Describe CPU0 instructions format
//
//  CPU INSTRUCTION FORMATS
//
//  opcode  - operation code.
//  ra      - dst reg, only used on 3 regs instr.
//  rb      - src reg.
//  rc      - src reg (on a 3 reg instr).
//  cx      - immediate
//
//===----------------------------------------------------------------------===//

// Format specifies the encoding used by the instruction.  This is part of the
// ad-hoc solution used to emit machine instruction encodings by our machine
// code emitter.
class Cpu0Format<bits<4> val> {
  bits<4> Value = val;
}

def Cpu0FormatA      : Cpu0Format<0>;
def Cpu0FormatL      : Cpu0Format<1>;
def Cpu0FormatJ      : Cpu0Format<2>;

// Generic Cpu0 Format
class Cpu0Inst<dag outs, dag ins, string asmstr, Cpu0Format f>
: Instruction
{
  let Namespace = "Cpu0";
  let Size = 4;
  Cpu0Format Form = f;

  bits<8> Opcode = 0;
  field bits<32> Inst;
  // Top 8 bits are the 'opcode' field
  let Inst{31-24} = Opcode;

  let InOperandList  = ins;
  let OutOperandList = outs;

  let AsmString   = asmstr;
}


//===----------------------------------------------------------------------===//
// Format A instruction class in Cpu0 : <|opcode|ra|rb|rc|cx|>
//===----------------------------------------------------------------------===//

class Cpu0InstrFormatA<bits<8> op, dag outs, dag ins, string asmstr>
: Cpu0Inst<outs, ins, !strconcat(asmstr, "\t$ra, $rb, $rc"), Cpu0FormatA>
{
  bits<4>  ra;
  bits<4>  rb;
  bits<4>  rc;
  bits<12> cx;

  let Opcode = op;
  let Inst{23-20} = ra;
  let Inst{19-16} = rb;
  let Inst{15-12} = rc;
  let Inst{11-0}  = cx;
}

//@class FL {
//===----------------------------------------------------------------------===//
// Format L instruction class in Cpu0 : <|opcode|ra|rb|cx|>
//===----------------------------------------------------------------------===//

class Cpu0InstrFormatL<bits<8> op, dag outs, dag ins, string asmstr>
: Cpu0Inst<outs, ins, asmstr, Cpu0FormatL>
{
  bits<4>  ra;
  bits<4>  rb;
  bits<16> imm16;

  let Opcode = op;

  let Inst{23-20} = ra;
  let Inst{19-16} = rb;
  let Inst{15-0}  = imm16;
}
//@class FL }

//===----------------------------------------------------------------------===//
// Format J instruction class in Cpu0 : <|opcode|address|>
//===----------------------------------------------------------------------===//
class Cpu0InstrFormatJ<bits<8> op, dag outs, dag ins, string asmstr>
: Cpu0Inst<outs, ins, asmstr, Cpu0FormatJ>
{
  bits<24> addr;

  let Opcode = op;

  let Inst{31-24} = op;
  let Inst{23-0} = addr;
}
