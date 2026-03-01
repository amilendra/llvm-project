//===-- H2BLBRegisterInfo.td - H2BLB Register defs ---------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the H2BLB register file
//===----------------------------------------------------------------------===//

let Namespace = "H2BLB" in {

def R0 : Register<"0", ["r0"]>;

}

def RegisterClass0 : RegisterClass<"H2BLB", [i32], 32, (add R0)> {
  let Size = 32;
}
