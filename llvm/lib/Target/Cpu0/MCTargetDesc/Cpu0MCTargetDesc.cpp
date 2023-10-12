//===-- Cpu0MCTargetDesc.cpp - Cpu0 Target Descriptions ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides Cpu0 specific target descriptions.
//
//===----------------------------------------------------------------------===//
#include "Cpu0MCTargetDesc.h"
#include "TargetInfo/Cpu0TargetInfo.h"

#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "Cpu0GenInstrInfo.inc"

#define GET_REGINFO_MC_DESC
#include "Cpu0GenRegisterInfo.inc"

using namespace llvm;

static MCRegisterInfo *createCpu0MCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *Info = new MCRegisterInfo();
  InitCpu0MCRegisterInfo(Info, Cpu0::R5);
  return Info;
}

static MCInstrInfo *createCpu0MCInstrInfo() {
  MCInstrInfo *Info = new MCInstrInfo();
  InitCpu0MCInstrInfo(Info);
  return Info;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeCpu0TargetMC() {
  for (Target *T : {&getTheCpu0LETarget(), &getTheCpu0BETarget()}) {
    TargetRegistry::RegisterMCRegInfo(*T, createCpu0MCRegisterInfo);
    TargetRegistry::RegisterMCInstrInfo(*T, createCpu0MCInstrInfo);
  }
}
