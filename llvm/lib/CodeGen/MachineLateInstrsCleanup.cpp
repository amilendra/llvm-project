//==--- MachineLateInstrsCleanup.cpp - Late Instructions Cleanup Pass -----===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This simple pass removes any identical and redundant immediate or address
// loads to the same register. The immediate loads removed can originally be
// the result of rematerialization, while the addresses are redundant frame
// addressing anchor points created during Frame Indices elimination.
//
//===----------------------------------------------------------------------===//

#include "llvm/CodeGen/MachineLateInstrsCleanup.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/PostOrderIterator.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/InitializePasses.h"
#include "llvm/Pass.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

#define DEBUG_TYPE "machine-latecleanup"

STATISTIC(NumRemoved, "Number of redundant instructions removed.");

namespace {

class MachineLateInstrsCleanup {
  const TargetRegisterInfo *TRI = nullptr;
  const TargetInstrInfo *TII = nullptr;

  // Data structures to map regs to their definitions and kills per MBB.
  struct Reg2MIMap : public SmallDenseMap<Register, MachineInstr *> {
    bool hasIdentical(Register Reg, MachineInstr *ArgMI) {
      MachineInstr *MI = lookup(Reg);
      return MI && MI->isIdenticalTo(*ArgMI);
    }
  };
  typedef SmallDenseMap<Register, TinyPtrVector<MachineInstr *>> Reg2MIVecMap;
  std::vector<Reg2MIMap> RegDefs;
  std::vector<Reg2MIVecMap> RegKills;

  // Walk through the instructions in MBB and remove any redundant
  // instructions.
  bool processBlock(MachineBasicBlock *MBB);

  void removeRedundantDef(MachineInstr *MI);
  void clearKillsForDef(Register Reg, MachineBasicBlock *MBB,
                        BitVector &VisitedPreds, MachineInstr *ToRemoveMI);

public:
  bool run(MachineFunction &MF);
};

class MachineLateInstrsCleanupLegacy : public MachineFunctionPass {
public:
  static char ID; // Pass identification, replacement for typeid

  MachineLateInstrsCleanupLegacy() : MachineFunctionPass(ID) {
    initializeMachineLateInstrsCleanupLegacyPass(
        *PassRegistry::getPassRegistry());
  }

  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.setPreservesCFG();
    MachineFunctionPass::getAnalysisUsage(AU);
  }

  bool runOnMachineFunction(MachineFunction &MF) override;

  MachineFunctionProperties getRequiredProperties() const override {
    return MachineFunctionProperties().setNoVRegs();
  }
};

} // end anonymous namespace

char MachineLateInstrsCleanupLegacy::ID = 0;

char &llvm::MachineLateInstrsCleanupID = MachineLateInstrsCleanupLegacy::ID;

INITIALIZE_PASS(MachineLateInstrsCleanupLegacy, DEBUG_TYPE,
                "Machine Late Instructions Cleanup Pass", false, false)

bool MachineLateInstrsCleanupLegacy::runOnMachineFunction(MachineFunction &MF) {
  if (skipFunction(MF.getFunction()))
    return false;

  return MachineLateInstrsCleanup().run(MF);
}

PreservedAnalyses
MachineLateInstrsCleanupPass::run(MachineFunction &MF,
                                  MachineFunctionAnalysisManager &MFAM) {
  MFPropsModifier _(*this, MF);
  if (!MachineLateInstrsCleanup().run(MF))
    return PreservedAnalyses::all();
  auto PA = getMachineFunctionPassPreservedAnalyses();
  PA.preserveSet<CFGAnalyses>();
  return PA;
}

bool MachineLateInstrsCleanup::run(MachineFunction &MF) {
  TRI = MF.getSubtarget().getRegisterInfo();
  TII = MF.getSubtarget().getInstrInfo();

  RegDefs.clear();
  RegDefs.resize(MF.getNumBlockIDs());
  RegKills.clear();
  RegKills.resize(MF.getNumBlockIDs());

  // Visit all MBBs in an order that maximises the reuse from predecessors.
  bool Changed = false;
  ReversePostOrderTraversal<MachineFunction *> RPOT(&MF);
  for (MachineBasicBlock *MBB : RPOT)
    Changed |= processBlock(MBB);

  return Changed;
}

// Clear any preceding kill flag on Reg after removing a redundant
// definition.
void MachineLateInstrsCleanup::clearKillsForDef(Register Reg,
                                                MachineBasicBlock *MBB,
                                                BitVector &VisitedPreds,
                                                MachineInstr *ToRemoveMI) {
  VisitedPreds.set(MBB->getNumber());

  // Clear kill flag(s) in MBB, that have been seen after the preceding
  // definition. If Reg or one of its subregs was killed, it would actually
  // be ok to stop after removing that (and any other) kill-flag, but it
  // doesn't seem noticeably faster while it would be a bit more complicated.
  Reg2MIVecMap &MBBKills = RegKills[MBB->getNumber()];
  if (auto Kills = MBBKills.find(Reg); Kills != MBBKills.end())
    for (auto *KillMI : Kills->second)
      KillMI->clearRegisterKills(Reg, TRI);

  // Definition in current MBB: done.
  Reg2MIMap &MBBDefs = RegDefs[MBB->getNumber()];
  MachineInstr *DefMI = MBBDefs[Reg];
  assert(DefMI->isIdenticalTo(*ToRemoveMI) && "Previous def not identical?");
  if (DefMI->getParent() == MBB)
    return;

  // If an earlier def is not in MBB, continue in predecessors.
  if (!MBB->isLiveIn(Reg))
    MBB->addLiveIn(Reg);
  assert(!MBB->pred_empty() && "Predecessor def not found!");
  for (MachineBasicBlock *Pred : MBB->predecessors())
    if (!VisitedPreds.test(Pred->getNumber()))
      clearKillsForDef(Reg, Pred, VisitedPreds, ToRemoveMI);
}

void MachineLateInstrsCleanup::removeRedundantDef(MachineInstr *MI) {
  Register Reg = MI->getOperand(0).getReg();
  BitVector VisitedPreds(MI->getMF()->getNumBlockIDs());
  clearKillsForDef(Reg, MI->getParent(), VisitedPreds, MI);
  MI->eraseFromParent();
  ++NumRemoved;
}

// Return true if MI is a potential candidate for reuse/removal and if so
// also the register it defines in DefedReg.  A candidate is a simple
// instruction that does not touch memory, has only one register definition
// and the only reg it may use is FrameReg. Typically this is an immediate
// load or a load-address instruction.
static bool isCandidate(const MachineInstr *MI, Register &DefedReg,
                        Register FrameReg) {
  DefedReg = MCRegister::NoRegister;
  bool SawStore = true;
  if (!MI->isSafeToMove(SawStore) || MI->isImplicitDef() || MI->isInlineAsm())
    return false;
  for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    if (MO.isReg()) {
      if (MO.isDef()) {
        if (i == 0 && !MO.isImplicit() && !MO.isDead())
          DefedReg = MO.getReg();
        else
          return false;
      } else if (MO.getReg() && MO.getReg() != FrameReg)
        return false;
    } else if (!(MO.isImm() || MO.isCImm() || MO.isFPImm() || MO.isCPI() ||
                 MO.isGlobal() || MO.isSymbol()))
      return false;
  }
  return DefedReg.isValid();
}

bool MachineLateInstrsCleanup::processBlock(MachineBasicBlock *MBB) {
  bool Changed = false;
  Reg2MIMap &MBBDefs = RegDefs[MBB->getNumber()];
  Reg2MIVecMap &MBBKills = RegKills[MBB->getNumber()];

  // Find reusable definitions in the predecessor(s).
  if (!MBB->pred_empty() && !MBB->isEHPad() &&
      !MBB->isInlineAsmBrIndirectTarget()) {
    MachineBasicBlock *FirstPred = *MBB->pred_begin();
    for (auto [Reg, DefMI] : RegDefs[FirstPred->getNumber()])
      if (llvm::all_of(
              drop_begin(MBB->predecessors()),
              [&, &Reg = Reg, &DefMI = DefMI](const MachineBasicBlock *Pred) {
                return RegDefs[Pred->getNumber()].hasIdentical(Reg, DefMI);
              })) {
        MBBDefs[Reg] = DefMI;
        LLVM_DEBUG(dbgs() << "Reusable instruction from pred(s): in "
                          << printMBBReference(*MBB) << ":  " << *DefMI);
      }
  }

  // Process MBB.
  MachineFunction *MF = MBB->getParent();
  const TargetRegisterInfo *TRI = MF->getSubtarget().getRegisterInfo();
  Register FrameReg = TRI->getFrameRegister(*MF);
  for (MachineInstr &MI : llvm::make_early_inc_range(*MBB)) {
    // If FrameReg is modified, no previous load-address instructions (using
    // it) are valid.
    if (MI.modifiesRegister(FrameReg, TRI)) {
      MBBDefs.clear();
      MBBKills.clear();
      continue;
    }

    Register DefedReg;
    bool IsCandidate = isCandidate(&MI, DefedReg, FrameReg);

    // Check for an earlier identical and reusable instruction.
    if (IsCandidate && MBBDefs.hasIdentical(DefedReg, &MI)) {
      LLVM_DEBUG(dbgs() << "Removing redundant instruction in "
                        << printMBBReference(*MBB) << ":  " << MI);
      removeRedundantDef(&MI);
      Changed = true;
      continue;
    }

    // Clear any entries in map that MI clobbers.
    for (auto DefI : llvm::make_early_inc_range(MBBDefs)) {
      Register Reg = DefI.first;
      if (MI.modifiesRegister(Reg, TRI)) {
        MBBDefs.erase(Reg);
        MBBKills.erase(Reg);
      } else if (MI.findRegisterUseOperandIdx(Reg, TRI, true /*isKill*/) != -1)
        // Keep track of all instructions that fully or partially kills Reg.
        MBBKills[Reg].push_back(&MI);
    }

    // Record this MI for potential later reuse.
    if (IsCandidate) {
      LLVM_DEBUG(dbgs() << "Found interesting instruction in "
                        << printMBBReference(*MBB) << ":  " << MI);
      MBBDefs[DefedReg] = &MI;
      assert(!MBBKills.count(DefedReg) && "Should already have been removed.");
    }
  }

  return Changed;
}
