//===-- OR1KCallingConv.td - Calling Conventions OR1K ------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This describes the calling conventions for the OR1K architecture.
//
//===----------------------------------------------------------------------===//

// Callee-saved registers
// Tablegens CSR_OR1K_SaveList and CSR_OR1K_RegMask
def CSR_OR1K : CalleeSavedRegs<(add)>;
def CSR_OR1K_NoRegs : CalleeSavedRegs<(add)>;
def CSR_OR1K_Preserve_All : CalleeSavedRegs<(add)>;
