//===-- OR1KTargetMachine.cpp - Define TargetMachine for OR1K ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Implements the info about OR1K target spec.
//
//===----------------------------------------------------------------------===//

#include "OR1KTargetMachine.h"
#include "MCTargetDesc/OR1KBaseInfo.h"
#include "OR1K.h"
#include "OR1KTargetTransformInfo.h"
#include "TargetInfo/OR1KTargetInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/TargetParser/Triple.h"
#include "llvm/Transforms/Scalar.h"
#include <optional>

using namespace llvm;

#define DEBUG_TYPE "or1k"

extern "C" void LLVMInitializeOR1KTarget() {
  // Register the target.
  RegisterTargetMachine<OR1KTargetMachine> X(getTheOR1KTarget());
}

static std::string computeDataLayout(const Triple &TT) {
  std::string Ret;
  Ret += "e";
  return Ret;
}
static Reloc::Model getEffectiveRelocModel(const Triple &TT,
                                           std::optional<Reloc::Model> RM) {
  if (!RM.has_value())
    return Reloc::Static;
  return *RM;
}
OR1KTargetMachine::OR1KTargetMachine(const Target &T, const Triple &TT,
                                     StringRef CPU, StringRef FS,
                                     const TargetOptions &Options,
                                     std::optional<Reloc::Model> RM,
                                     std::optional<CodeModel::Model> CM,
                                     CodeGenOptLevel OL, bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(TT), TT, CPU, FS, Options,
                        getEffectiveRelocModel(TT, RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()) {
  initAsmInfo();
}

OR1KTargetMachine::~OR1KTargetMachine() = default;

const OR1KSubtarget *
OR1KTargetMachine::getSubtargetImpl(const Function &F) const {
  Attribute CPUAttr = F.getFnAttribute("target-cpu");
  Attribute TuneAttr = F.getFnAttribute("tune-cpu");
  Attribute FSAttr = F.getFnAttribute("target-features");

  std::string CPU =
      CPUAttr.isValid() ? CPUAttr.getValueAsString().str() : TargetCPU;
  std::string TuneCPU =
      TuneAttr.isValid() ? TuneAttr.getValueAsString().str() : CPU;
  std::string FS =
      FSAttr.isValid() ? FSAttr.getValueAsString().str() : TargetFS;

  std::string Key = CPU + TuneCPU + FS;
  auto &I = SubtargetMap[Key];
  if (!I) {
    // This needs to be done before we create a new subtarget since any
    // creation will depend on the TM and the code generation flags on the
    // function that reside in TargetOptions.
    resetTargetOptions(F);
    auto ABIName = Options.MCOptions.getABIName();
    if (const MDString *ModuleTargetABI = dyn_cast_or_null<MDString>(
            F.getParent()->getModuleFlag("target-abi"))) {
      auto TargetABI = OR1KABI::getTargetABI(ABIName);
      if (TargetABI != OR1KABI::ABI_Unknown &&
          ModuleTargetABI->getString() != ABIName) {
        report_fatal_error("-target-abi option != target-abi module flag");
      }
      ABIName = ModuleTargetABI->getString();
    }
    I = std::make_unique<OR1KSubtarget>(TargetTriple, CPU, TuneCPU, FS, ABIName,
                                        *this);
  }
  return I.get();
}

namespace {
class OR1KPassConfig : public TargetPassConfig {
public:
  OR1KPassConfig(OR1KTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  OR1KTargetMachine &getOR1KTargetMachine() const {
    return getTM<OR1KTargetMachine>();
  }

  bool addInstSelector() override;
};
} // namespace

TargetPassConfig *OR1KTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new OR1KPassConfig(*this, PM);
}

TargetTransformInfo
OR1KTargetMachine::getTargetTransformInfo(const Function &F) const {
  return TargetTransformInfo(OR1KTTIImpl(this, F));
}

bool OR1KPassConfig::addInstSelector() {
  addPass(createOR1KISelDag(getOR1KTargetMachine()));

  return false;
}
