//===-- H2BLBMCTargetDesc.cpp - H2BLB Target Descriptions -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides H2BLB specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "H2BLBMCTargetDesc.h"
#include "llvm/MC/MCRegisterInfo.h"

#include "llvm/Support/Compiler.h" // For LLVM_EXTERNAL_VISIBILITY.

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "H2BLBGenRegisterInfo.inc"

extern "C" LLVM_ABI LLVM_EXTERNAL_VISIBILITY void
LLVMInitializeH2BLBTargetMC() {}
