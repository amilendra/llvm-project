//===- OR1KRegisterInfo.cpp - OR1K Register Information -*- C++ -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the OR1K implementation of the TargetRegisterInfo
// class.
//
//===----------------------------------------------------------------------===//

#include "OR1KRegisterInfo.h"
#include "OR1K.h"
#include "OR1KSubtarget.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "OR1KGenRegisterInfo.inc"

OR1KRegisterInfo::OR1KRegisterInfo(unsigned HwMode)
    : OR1KGenRegisterInfo(OR1K::NoRegister) {}

const MCPhysReg *
OR1KRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_OR1K_SaveList;
}

const uint32_t *
OR1KRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID CC) const {
  return CSR_OR1K_RegMask;
}

const uint32_t *OR1KRegisterInfo::getNoPreservedMask() const {
  return CSR_OR1K_NoRegs_RegMask;
}

BitVector OR1KRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  return Reserved;
}

Register OR1KRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return OR1K::NoRegister;
}

bool OR1KRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                           int SPAdj, unsigned FIOperandNum,
                                           RegScavenger *RS) const {
  llvm_unreachable("Subroutines not supported yet");
}
