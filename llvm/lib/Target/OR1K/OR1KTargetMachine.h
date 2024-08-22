//===-- OR1KTargetMachine.h - Define TargetMachine for OR1K --- C++ ---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the OR1K specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef OR1K_TARGETMACHINE_H
#define OR1K_TARGETMACHINE_H

#include "OR1KSubtarget.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class OR1KTargetMachine : public LLVMTargetMachine {
  OR1KSubtarget Subtarget;
  std::unique_ptr<TargetLoweringObjectFile> TLOF;

public:
  OR1KTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                    StringRef FS, const TargetOptions &Options,
                    std::optional<Reloc::Model> RM,
                    std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                    bool JIT);
  ~OR1KTargetMachine() override;

  const OR1KSubtarget *getSubtargetImpl(const Function &F) const override {
    return &Subtarget;
  }

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};
} // namespace llvm

#endif
