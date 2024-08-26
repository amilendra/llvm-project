//=- OR1KISelLowering.h - OR1K DAG Lowering Interface -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that OR1K uses to lower LLVM code into
// a selection DAG.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_OR1K_OR1KISELLOWERING_H
#define LLVM_LIB_TARGET_OR1K_OR1KISELLOWERING_H

#include "OR1K.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {
class OR1KSubtarget;
struct OR1KRegisterInfo;
namespace OR1KISD {
enum NodeType : unsigned {
  FIRST_NUMBER = ISD::BUILTIN_OP_END,

  // TODO: add more OR1KISDs

};
} // namespace OR1KISD

class OR1KTargetLowering : public TargetLowering {
  const OR1KSubtarget &Subtarget;

public:
  explicit OR1KTargetLowering(const TargetMachine &TM,
                              const OR1KSubtarget &STI);

  const OR1KSubtarget &getSubtarget() const { return Subtarget; }
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_OR1K_OR1KISELLOWERING_H
