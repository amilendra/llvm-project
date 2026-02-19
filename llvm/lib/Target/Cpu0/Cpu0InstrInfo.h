//===-- Cpu0InstrInfo.h - Cpu0 Instruction Information ----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the Cpu0 implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CPU0_CPU0INSTRINFO_H
#define LLVM_LIB_TARGET_CPU0_CPU0INSTRINFO_H

#include "Cpu0Config.h"

#include "Cpu0.h"
#include "Cpu0AnalyzeImmediate.h"
#include "Cpu0RegisterInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "Cpu0GenInstrInfo.inc"

namespace llvm {

class Cpu0InstrInfo : public Cpu0GenInstrInfo {
  virtual void anchor();

protected:
  const Cpu0Subtarget &Subtarget;

public:
  explicit Cpu0InstrInfo(const Cpu0Subtarget &STI,
                         const Cpu0RegisterInfo &RI);

  static const Cpu0InstrInfo *create(Cpu0Subtarget &STI);

  /// getRegisterInfo - TargetInstrInfo is a superset of MRegister info.  As
  /// such, whenever a client has an instance of instruction info, it should
  /// always be able to get register info as well (through this method).
  ///
  virtual const Cpu0RegisterInfo &getRegisterInfo() const = 0;

  /// Return the number of bytes of code the specified instruction may be.
  unsigned GetInstSizeInBytes(const MachineInstr &MI) const;

  void storeRegToStackSlot(
      MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, Register SrcReg,
      bool isKill, int FrameIndex, const TargetRegisterClass *RC,
      Register VReg, MachineInstr::MIFlag Flags = MachineInstr::NoFlags) const
    override {
    storeRegToStack(MBB, MBBI, SrcReg, isKill, FrameIndex, RC, nullptr, 0, Flags);
  }

  void loadRegFromStackSlot(
      MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI,
      Register DestReg, int FrameIndex, const TargetRegisterClass *RC,
      Register VReg, unsigned SubReg = 0,
      MachineInstr::MIFlag Flags = MachineInstr::NoFlags) const override {
    (void)SubReg;
    loadRegFromStack(MBB, MBBI, DestReg, FrameIndex, RC, nullptr, 0, Flags);
  }

  virtual void
  storeRegToStack(MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
                  Register SrcReg, bool isKill, int FrameIndex,
                  const TargetRegisterClass *RC, const TargetRegisterInfo *TRI,
                  int64_t Offset,
                  MachineInstr::MIFlag Flags = MachineInstr::NoFlags) const = 0;

  virtual void loadRegFromStack(
      MachineBasicBlock &MBB, MachineBasicBlock::iterator MI, Register DestReg,
      int FrameIndex, const TargetRegisterClass *RC,
      const TargetRegisterInfo *TRI, int64_t Offset,
      MachineInstr::MIFlag Flags = MachineInstr::NoFlags) const = 0;

  virtual void adjustStackPtr(unsigned SP, int64_t Amount,
                              MachineBasicBlock &MBB,
                              MachineBasicBlock::iterator I) const = 0;

protected:
  MachineMemOperand *GetMemOperand(MachineBasicBlock &MBB, int FI,
                                   MachineMemOperand::Flags Flags) const;
};
const Cpu0InstrInfo *createCpu0SEInstrInfo(const Cpu0Subtarget &STI);
} // namespace llvm

#endif
