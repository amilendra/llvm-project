//===-- OR1KMCTargetDesc.cpp - OR1K Target Descriptions ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides OR1K specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "OR1KMCTargetDesc.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

//@2 {
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeOR1KTargetMC() {}
//@2 }
