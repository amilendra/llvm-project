//===-- Cpu0ISEISelLowering.h - Cpu0ISE DAG Lowering Interface ----*- C++
//-*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Subclass of Cpu0ITargetLowering specialized for cpu032/64.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CPU0_CPU0SEISELLOWERING_H
#define LLVM_LIB_TARGET_CPU0_CPU0SEISELLOWERING_H

#include "Cpu0Config.h"

#include "Cpu0ISelLowering.h"
#include "Cpu0RegisterInfo.h"

namespace llvm {
class Cpu0SETargetLowering : public Cpu0TargetLowering {
public:
  explicit Cpu0SETargetLowering(const Cpu0TargetMachine &TM,
                                const Cpu0Subtarget &STI);

  SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const override;

private:
};
} // namespace llvm

#endif // Cpu0ISEISELLOWERING_H
