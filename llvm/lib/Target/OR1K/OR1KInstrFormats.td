//===-- OR1KInstrFormats.td - OR1K Instruction Formats -----*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

class Format<bits<2> value> {
  bits<2> Value = value;
}

def OtherFrm : Format<0>;
def AFrm : Format<1>;
def JFrm : Format<2>;

class InstOR1K<dag outs, dag ins, string asmstr, list<dag> pattern>
  : Instruction {
  field bits<32> Inst;
  field bits<32> SoftFail = 0;
  let Size = 4;

  let Namespace = "OR1K";
  let DecoderNamespace = "OR1K";

  Format format = OtherFrm;
  let TSFlags{1-0} = format.Value;

  bits<2> optype;
  bits<4> opcode;
  let Inst{31-30} = optype;
  let Inst{29-26} = opcode;

  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString = asmstr;
  let Pattern = pattern;
}


class InstRR<bits<4> op, dag outs, dag ins, string asmstr, list<dag> pattern>
  : InstOR1K<outs, ins, asmstr, pattern> {
  let optype = 0b11;
  let opcode = op;
}

class InstRI<bits<4> op, dag outs, dag ins, string asmstr, list<dag> pattern>
  : InstOR1K<outs, ins, asmstr, pattern> {
  let optype = 0b10;
  let opcode = op;
}

class InstBR<bits<4> op, dag outs, dag ins, string asmstr, list<dag> pattern>
  : InstOR1K<outs, ins, asmstr, pattern> {
  let optype = 0b01;
  let opcode = op;
}

class InstBI<bits<4> op, dag outs, dag ins, string asmstr, list<dag>pattern>
  : InstOR1K<outs, ins, asmstr, pattern> {
  let optype = 0;
  let opcode = op;
}

// Floating point instructions
class InstFRR<bits<8> op, dag outs, dag ins, string asmstr, list<dag> pattern>
  : InstOR1K<outs, ins, asmstr, pattern> {
  let optype = 0b11;
  let opcode = 0b0010;
  let Inst{7-0} = op;
}

// Pseudo instructions
class Pseudo<dag outs, dag ins, string asmstr, list<dag> pattern>
  : InstOR1K<outs, ins, asmstr, pattern> {
  let Inst{15-0} = 0;
  let isPseudo = 1;
}
