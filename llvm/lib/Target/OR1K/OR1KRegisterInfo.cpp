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
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "OR1KGenRegisterInfo.inc"

OR1KRegisterInfo::OR1KRegisterInfo(unsigned HwMode)
    : OR1KGenRegisterInfo(OR1K::R1, /*DwarfFlavour*/ 0,
                          /*EHFlavor*/ 0,
                          /*PC*/ 0, HwMode) {}

const MCPhysReg *
OR1KRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  auto &Subtarget = MF->getSubtarget<OR1KSubtarget>();

  switch (Subtarget.getTargetABI()) {
  default:
    llvm_unreachable("Unrecognized ABI");
  case OR1KABI::ABI_ILP32S:
  case OR1KABI::ABI_LP64S:
    return CSR_ILP32S_LP64S_SaveList;
  case OR1KABI::ABI_ILP32F:
  case OR1KABI::ABI_LP64F:
    return CSR_ILP32F_LP64F_SaveList;
  case OR1KABI::ABI_ILP32D:
  case OR1KABI::ABI_LP64D:
    return CSR_ILP32D_LP64D_SaveList;
  }
}

const uint32_t *
OR1KRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID CC) const {
  auto &Subtarget = MF.getSubtarget<OR1KSubtarget>();

  switch (Subtarget.getTargetABI()) {
  default:
    llvm_unreachable("Unrecognized ABI");
  case OR1KABI::ABI_ILP32S:
  case OR1KABI::ABI_LP64S:
    return CSR_ILP32S_LP64S_RegMask;
  case OR1KABI::ABI_ILP32F:
  case OR1KABI::ABI_LP64F:
    return CSR_ILP32F_LP64F_RegMask;
  case OR1KABI::ABI_ILP32D:
  case OR1KABI::ABI_LP64D:
    return CSR_ILP32D_LP64D_RegMask;
  }
}

const uint32_t *OR1KRegisterInfo::getNoPreservedMask() const {
  return CSR_NoRegs_RegMask;
}

BitVector OR1KRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  const OR1KFrameLowering *TFI = getFrameLowering(MF);
  BitVector Reserved(getNumRegs());

  // Use markSuperRegs to ensure any register aliases are also reserved
  markSuperRegs(Reserved, OR1K::R0);  // zero
  markSuperRegs(Reserved, OR1K::R2);  // tp
  markSuperRegs(Reserved, OR1K::R3);  // sp
  markSuperRegs(Reserved, OR1K::R21); // non-allocatable
  if (TFI->hasFP(MF))
    markSuperRegs(Reserved, OR1K::R22); // fp
  // Reserve the base register if we need to realign the stack and allocate
  // variable-sized objects at runtime.
  if (TFI->hasBP(MF))
    markSuperRegs(Reserved, OR1KABI::getBPReg()); // bp

  assert(checkAllSuperRegsMarked(Reserved));
  return Reserved;
}

Register OR1KRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  const TargetFrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? OR1K::R22 : OR1K::R3;
}

bool OR1KRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                           int SPAdj, unsigned FIOperandNum,
                                           RegScavenger *RS) const {
  assert(SPAdj == 0 && "Unexpected non-zero SPAdj value");
  // TODO: Implement this when we have function calls
  return false;
}
