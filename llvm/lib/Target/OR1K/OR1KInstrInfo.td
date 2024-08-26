//===-- OR1KInstrInfo.td - The OR1K Instruction Set --------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
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

class NOP_I<bits<2> op2Val, string asmstr>
  : InstBI<0x5, (outs), (ins i16imm:$imm),
           !strconcat(asmstr, "\t$imm"), []> {
  bits<2> op2;
  bits<16> imm;

  let Inst{25-24} = op2;
  let Inst{15-0} = imm;

  let op2 = op2Val;
}

def NOP  : NOP_I<0x1, "l.nop">;
