//===-- Cpu0RegisterInfo.td - Cpu0 Register defs -----------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the CPU0 register file
//===----------------------------------------------------------------------===//

// We have banks of 16 registers each.
class Cpu0Reg<bits<4> Enc, string n> : Register<n> {
  let Namespace = "Cpu0";
  // For tablegen(... -gen-emitter)  in CMakeLists.txt
  let HWEncoding{3-0} = Enc;
}

// Cpu0 CPU Registers
class Cpu0GPRReg<bits<4> Enc, string n> : Cpu0Reg<Enc, n>;

// Co-processor 0 Registers
class Cpu0C0Reg<bits<4> Enc, string n> : Cpu0Reg<Enc, n>;

// Cpu0 other Registers
class Cpu0OtherReg<bits<4> Enc, string n> : Cpu0Reg<Enc, n>;

//===----------------------------------------------------------------------===//
//@ Register definitions
//===----------------------------------------------------------------------===//
//@ Table 2 : Cpu0 general purpose registers (GPR)
def R0 : Cpu0GPRReg<0,  "R0">;
def R1 : Cpu0GPRReg<1,  "R1">;
def R2 : Cpu0GPRReg<2,  "R2">;
def R3 : Cpu0GPRReg<3,  "R3">;
def R4 : Cpu0GPRReg<4,  "R4">;
def R5 : Cpu0GPRReg<5,  "R5">;
def R6 : Cpu0GPRReg<6,  "R6">;
def R7 : Cpu0GPRReg<7,  "R7">;
def R8 : Cpu0GPRReg<8,  "R8">;
def R9 : Cpu0GPRReg<9,  "R9">;
def R10 : Cpu0GPRReg<10, "R10">;
def GP : Cpu0GPRReg<11, "R11">;
def FP : Cpu0GPRReg<12, "R12">;
def SP : Cpu0GPRReg<13, "R13">;
def LR : Cpu0GPRReg<14, "R14">;
def SW : Cpu0GPRReg<15, "R15">;

//@ Table 3 : Cpu0 co-processor 0 registers (C0R)
def PC : Cpu0C0Reg<0, "PC">;
def EPC : Cpu0C0Reg<1, "EPC">;

//@ Table 4 Cpu0 other registers
def IR : Cpu0OtherReg<0, "IR">;
def MAR : Cpu0OtherReg<1, "MAR">;
def MDR : Cpu0OtherReg<2, "MDR">;
def HI : Cpu0OtherReg<3, "HI">;
def LO : Cpu0OtherReg<4, "LO">;

//===----------------------------------------------------------------------===//
//@ Register Classes
//===----------------------------------------------------------------------===//
def Cpu0GPR   : RegisterClass<"Cpu0", [i32], 32, (add R0, R1, R2, R3, R4, R5, R6)>;

//@ Hi/Lo Registers class
def HILO   : RegisterClass<"Cpu0", [i32], 32, (add HI, LO)>;

//@ Status Registers class
def SR     : RegisterClass<"Cpu0", [i32], 32, (add SW)>;

//@ Co-processor 0 Registers class
def C0Regs : RegisterClass<"Cpu0", [i32], 32, (add PC, EPC)>;
