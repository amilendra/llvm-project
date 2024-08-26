//===-- OR1K.td - Describe the OR1K Target Machine ---------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces which we are implementing
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Register File, Instruction Descriptions
//===----------------------------------------------------------------------===//

include "OR1KRegisterInfo.td"
include "OR1KCallingConv.td"
include "OR1KInstrInfo.td"

def OR1KInstrInfo : InstrInfo;

def OR1KAsmParser : AsmParser;

def OR1KAsmWriter : AsmWriter;
//===----------------------------------------------------------------------===//
// OR1K processors supported.
//===----------------------------------------------------------------------===//

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;
def : Proc<"or1200",  []>;

//===----------------------------------------------------------------------===//
// Declare the target which we are implementing
//===----------------------------------------------------------------------===//

 def OR1K : Target {
  // Pull in Instruction Info:
  let InstructionSet = OR1KInstrInfo;
}
