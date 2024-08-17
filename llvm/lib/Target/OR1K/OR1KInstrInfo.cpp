//=- OR1KInstrInfo.cpp - OR1K Instruction Information -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the OR1K implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "OR1KInstrInfo.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "OR1KGenInstrInfo.inc"

OR1KInstrInfo::OR1KInstrInfo(OR1KSubtarget &STI)
    // FIXME: add CFSetup and CFDestroy Inst when we implement function call.
    : OR1KGenInstrInfo(),

      STI(STI) {}
