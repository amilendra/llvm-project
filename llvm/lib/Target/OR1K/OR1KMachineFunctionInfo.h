//=- OR1KMachineFunctionInfo.h - OR1K machine function info -----===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares OR1K-specific per-machine-function information.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_OR1K_OR1KMACHINEFUNCTIONINFO_H
#define LLVM_LIB_TARGET_OR1K_OR1KMACHINEFUNCTIONINFO_H

#include "OR1KSubtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

/// OR1KMachineFunctionInfo - This class is derived from
/// MachineFunctionInfo and contains private OR1K-specific information for
/// each MachineFunction.
class OR1KMachineFunctionInfo : public MachineFunctionInfo {
private:
  /// FrameIndex for start of varargs area
  int VarArgsFrameIndex = 0;
  /// Size of the save area used for varargs
  int VarArgsSaveSize = 0;

  /// Size of stack frame to save callee saved registers
  unsigned CalleeSavedStackSize = 0;

public:
  OR1KMachineFunctionInfo(const MachineFunction &MF) {}

  int getVarArgsFrameIndex() const { return VarArgsFrameIndex; }
  void setVarArgsFrameIndex(int Index) { VarArgsFrameIndex = Index; }

  unsigned getVarArgsSaveSize() const { return VarArgsSaveSize; }
  void setVarArgsSaveSize(int Size) { VarArgsSaveSize = Size; }

  unsigned getCalleeSavedStackSize() const { return CalleeSavedStackSize; }
  void setCalleeSavedStackSize(unsigned Size) { CalleeSavedStackSize = Size; }
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_OR1K_OR1KMACHINEFUNCTIONINFO_H
