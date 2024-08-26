//===-- OR1KTargetMachine.cpp - Define TargetMachine for OR1K ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Implements the info about OR1K target spec.
//
//===----------------------------------------------------------------------===//

#include "OR1KTargetMachine.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "or1k"

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeOR1KTarget() {}
