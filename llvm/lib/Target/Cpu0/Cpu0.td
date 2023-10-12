//===-- Cpu0.td - Describe the Cpu0 Target Machine ---------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Registers, calling conventions, instruction descriptions.
//===----------------------------------------------------------------------===//

include "Cpu0RegisterInfo.td"
include "Cpu0InstrInfo.td"

//===----------------------------------------------------------------------===//
// Cpu0 processors supported.
//===----------------------------------------------------------------------===//

def : ProcessorModel<"generic-Cpu0", NoSchedModel, []>;

//===----------------------------------------------------------------------===//
// Define the Cpu0 target.
//===----------------------------------------------------------------------===//

def Cpu0InstrInfo : InstrInfo;

def Cpu0 : Target {
  let InstructionSet = Cpu0InstrInfo;
}
