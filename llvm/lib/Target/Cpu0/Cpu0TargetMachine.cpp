//===-- Cpu0TargetMachine.cpp - Define TargetMachine for Cpu0 ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Implements the info about Cpu0 target spec.
//
//===----------------------------------------------------------------------===//

#include "Cpu0TargetMachine.h"
#include "TargetInfo/Cpu0TargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "cpu0"

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeCpu0Target() {
  // Register the target.
  RegisterTargetMachine<Cpu0BETargetMachine> X(getTheCpu0BETarget());
  RegisterTargetMachine<Cpu0LETargetMachine> Y(getTheCpu0LETarget());
}

// FIXME: This is just a placeholder to make current commit buildable. Body of
// this function will be filled in later commits.
static std::string computeDataLayout(bool IsLittleEndian) {
  std::string Ret;
  if (IsLittleEndian)
    Ret += "e";
  else
    Ret += "E";
  return Ret;
}

static Reloc::Model getEffectiveRelocModel(std::optional<Reloc::Model> RM) {
  if (!RM.has_value())
    return Reloc::Static;
  return *RM;
}

Cpu0TargetMachine::Cpu0TargetMachine(const Target &T, const Triple &TT,
                                     StringRef CPU, StringRef FeatureStrings,
                                     const TargetOptions &Options,
                                     std::optional<Reloc::Model> RM,
                                     std::optional<CodeModel::Model> CM,
                                     CodeGenOptLevel OL, bool isLittle)
    : LLVMTargetMachine(T, computeDataLayout(isLittle), TT, CPU, FeatureStrings,
                        Options, getEffectiveRelocModel(RM),
                        ::getEffectiveCodeModel(CM, CodeModel::Small), OL),
      IsLittleEndian(isLittle) {
  initAsmInfo();
}

Cpu0TargetMachine::~Cpu0TargetMachine() = default;
