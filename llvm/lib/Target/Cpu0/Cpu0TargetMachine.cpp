//===-- Cpu0TargetMachine.cpp - Define TargetMachine for Cpu0 ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/Cpu0TargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "cpu0"

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeCpu0Target() {}
