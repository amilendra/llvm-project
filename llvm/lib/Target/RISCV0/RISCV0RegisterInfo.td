//===-- RISCV0RegisterInfo.td - RISC-V0 Register defs ------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the RISC-V0 register files
//===----------------------------------------------------------------------===//

let Namespace = "RISCV0" in {
class RISCV0Reg<bits<5> Enc, string n, list<string> alt = []> : Register<n> {
  let HWEncoding{4-0} = Enc;
  let AltNames = alt;
}
def ABIRegAltName : RegAltNameIndex;
} // Namespace = "RISCV0"

// Integer registers
let RegAltNameIndices = [ABIRegAltName] in {
  def X0  : RISCV0Reg<0, "x0", ["zero"]>, DwarfRegNum<[0]>;
  def X1  : RISCV0Reg<1, "x1", ["ra"]>, DwarfRegNum<[1]>;
  def X2  : RISCV0Reg<2, "x2", ["sp"]>, DwarfRegNum<[2]>;
  def X3  : RISCV0Reg<3, "x3", ["gp"]>, DwarfRegNum<[3]>;
  def X4  : RISCV0Reg<4, "x4", ["tp"]>, DwarfRegNum<[4]>;
  def X5  : RISCV0Reg<5, "x5", ["t0"]>, DwarfRegNum<[5]>;
  def X6  : RISCV0Reg<6, "x6", ["t1"]>, DwarfRegNum<[6]>;
  def X7  : RISCV0Reg<7, "x7", ["t2"]>, DwarfRegNum<[7]>;
  def X8  : RISCV0Reg<8, "x8", ["s0"]>, DwarfRegNum<[8]>;
  def X9  : RISCV0Reg<9, "x9", ["s1"]>, DwarfRegNum<[9]>;
  def X10 : RISCV0Reg<10,"x10", ["a0"]>, DwarfRegNum<[10]>;
  def X11 : RISCV0Reg<11,"x11", ["a1"]>, DwarfRegNum<[11]>;
  def X12 : RISCV0Reg<12,"x12", ["a2"]>, DwarfRegNum<[12]>;
  def X13 : RISCV0Reg<13,"x13", ["a3"]>, DwarfRegNum<[13]>;
  def X14 : RISCV0Reg<14,"x14", ["a4"]>, DwarfRegNum<[14]>;
  def X15 : RISCV0Reg<15,"x15", ["a5"]>, DwarfRegNum<[15]>;
  def X16 : RISCV0Reg<16,"x16", ["a6"]>, DwarfRegNum<[16]>;
  def X17 : RISCV0Reg<17,"x17", ["a7"]>, DwarfRegNum<[17]>;
  def X18 : RISCV0Reg<18,"x18", ["s2"]>, DwarfRegNum<[18]>;
  def X19 : RISCV0Reg<19,"x19", ["s3"]>, DwarfRegNum<[19]>;
  def X20 : RISCV0Reg<20,"x20", ["s4"]>, DwarfRegNum<[20]>;
  def X21 : RISCV0Reg<21,"x21", ["s5"]>, DwarfRegNum<[21]>;
  def X22 : RISCV0Reg<22,"x22", ["s6"]>, DwarfRegNum<[22]>;
  def X23 : RISCV0Reg<23,"x23", ["s7"]>, DwarfRegNum<[23]>;
  def X24 : RISCV0Reg<24,"x24", ["s8"]>, DwarfRegNum<[24]>;
  def X25 : RISCV0Reg<25,"x25", ["s9"]>, DwarfRegNum<[25]>;
  def X26 : RISCV0Reg<26,"x26", ["s10"]>, DwarfRegNum<[26]>;
  def X27 : RISCV0Reg<27,"x27", ["s11"]>, DwarfRegNum<[27]>;
  def X28 : RISCV0Reg<28,"x28", ["t3"]>, DwarfRegNum<[28]>;
  def X29 : RISCV0Reg<29,"x29", ["t4"]>, DwarfRegNum<[29]>;
  def X30 : RISCV0Reg<30,"x30", ["t5"]>, DwarfRegNum<[30]>;
  def X31 : RISCV0Reg<31,"x31", ["t6"]>, DwarfRegNum<[31]>;
}

def XLenVT : ValueTypeByHwMode<[RV32, RV64, DefaultMode],
                               [i32,  i64,  i32]>;

// TODO: once codegen is implemented, registers should be listed in an order
// reflecting the preferred register allocation sequence.
def GPR : RegisterClass< "RISCV0", [XLenVT], 32, (add
    (sequence "X%u", 0, 31)
  )> {
  let RegInfos = RegInfoByHwMode<
      [RV32,              RV64,              DefaultMode],
      [RegInfo<32,32,32>, RegInfo<64,64,64>, RegInfo<32,32,32>]>;
}
