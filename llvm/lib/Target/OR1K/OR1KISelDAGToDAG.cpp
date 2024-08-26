//=- OR1KISelDAGToDAG.cpp - A dag to dag inst selector for OR1K -===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines an instruction selector for the OR1K target.
//
//===----------------------------------------------------------------------===//

#include "OR1KISelDAGToDAG.h"
#include "MCTargetDesc/OR1KMCTargetDesc.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

using namespace llvm;

#define DEBUG_TYPE "or1k-isel"
#define PASS_NAME "OR1K DAG->DAG Pattern Instruction Selection"

void OR1KDAGToDAGISel::Select(SDNode *Node) {
  // If we have a custom node, we have already selected.
  if (Node->isMachineOpcode()) {
    LLVM_DEBUG(dbgs() << "== "; Node->dump(CurDAG); dbgs() << "\n");
    Node->setNodeId(-1);
    return;
  }

  // Instruction Selection not handled by the auto-generated tablegen selection
  // should be handled here.
  unsigned Opcode = Node->getOpcode();
  SDLoc DL(Node);

  switch (Opcode) {
  default:
    break;
    // TODO: Add selection nodes needed later.
  }

  // Select the default instruction.
  SelectCode(Node);
}

char OR1KDAGToDAGISelLegacy::ID;

INITIALIZE_PASS(OR1KDAGToDAGISelLegacy, DEBUG_TYPE, PASS_NAME, false, false)

/// createOR1KISelDag - This pass converts a legalized DAG into a
/// OR1K-specific DAG, ready for instruction scheduling.
FunctionPass *llvm::createOR1KISelDag(OR1KTargetMachine &TM) {
  return new OR1KDAGToDAGISelLegacy(TM);
}
