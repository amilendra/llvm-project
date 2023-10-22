//===-- RISCV0.td - Describe the RISCV0 Target Machine -----*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//

// RISC-V0 subtarget features and instruction predicates.
//===----------------------------------------------------------------------===//

def Feature64Bit : SubtargetFeature<"64bit", "HasRV64", "true",
                                    "Implements RV64">;

def RV64         : HwMode<"+64bit", []>;
def RV32         : HwMode<"-64bit", []>;

//===----------------------------------------------------------------------===//
// Register file, instruction descriptions.
//===----------------------------------------------------------------------===//

include "RISCV0RegisterInfo.td"
include "RISCV0InstrInfo.td"

def RISCV0InstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// RISC-V0 processors supported.
//===----------------------------------------------------------------------===//

def : ProcessorModel<"generic-rv32", NoSchedModel, []>;

def : ProcessorModel<"generic-rv64", NoSchedModel, [Feature64Bit]>;

//===----------------------------------------------------------------------===//
// Define the RISC-V0 target.
//===----------------------------------------------------------------------===//

def RISCV0 : Target {
  let InstructionSet = RISCV0InstrInfo;
}
