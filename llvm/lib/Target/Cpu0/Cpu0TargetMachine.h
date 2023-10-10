//=- Cpu0TargetMachine.h - Define TargetMachine for Cpu0 --------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the Cpu0 specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CPU0_CPU0TARGETMACHINE_H
#define LLVM_LIB_TARGET_CPU0_CPU0TARGETMACHINE_H

#include "llvm/Target/TargetMachine.h"

namespace llvm {

class Cpu0TargetMachine : public LLVMTargetMachine {
protected: // Can only create subclasses.
  Cpu0TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                    StringRef FeatureStrings, const TargetOptions &Options,
                    std::optional<Reloc::Model> RM,
                    std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                    bool LE);
  bool IsLittleEndian;

public:
  ~Cpu0TargetMachine() override;
};

/// Cpu0 big endian target machine.
///
class Cpu0BETargetMachine : public Cpu0TargetMachine {
public:
  Cpu0BETargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                      StringRef FeatureStrings, const TargetOptions &Options,
                      std::optional<Reloc::Model> RM,
                      std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                      bool LE)
      : Cpu0TargetMachine(T, TT, CPU, FeatureStrings, Options, RM, CM, OL,
                          /*isLittleEndian*/ false) {}
};

/// Cpu0 little endian target machine.
///
class Cpu0LETargetMachine : public Cpu0TargetMachine {
public:
  Cpu0LETargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                      StringRef FeatureStrings, const TargetOptions &Options,
                      std::optional<Reloc::Model> RM,
                      std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                      bool LE)
      : Cpu0TargetMachine(T, TT, CPU, FeatureStrings, Options, RM, CM, OL,
                          /*LittleEndian*/ true) {}
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CPU0_CPU0TARGETMACHINE_H
