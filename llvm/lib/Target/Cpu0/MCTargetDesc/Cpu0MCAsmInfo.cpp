//===-- Cpu0MCAsmInfo.cpp - Cpu0 Asm Properties ----------------*- C++ -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the Cpu0MCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "Cpu0MCAsmInfo.h"

#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

void Cpu0MCAsmInfo::anchor() {}

Cpu0MCAsmInfo::Cpu0MCAsmInfo(const Triple &TheTriple) {
  if ((TheTriple.getArch() == Triple::cpu0))
    IsLittleEndian = false; // the default of IsLittleEndian is true

  AlignmentIsInBytes = false;
  Data16bitsDirective = "\t.2byte\t";
  Data32bitsDirective = "\t.4byte\t";
  Data64bitsDirective = "\t.8byte\t";
  PrivateGlobalPrefix = "$";
  // PrivateLabelPrefix: display $BB for the labels of basic block
  PrivateLabelPrefix = "$";
  CommentString = "#";
  ZeroDirective = "\t.space\t";
  WeakRefDirective = "\t.weak\t";
  UseAssignmentForEHBegin = true;

  SupportsDebugInformation = true;
  ExceptionsType = ExceptionHandling::DwarfCFI;
  DwarfRegNumForCFI = true;
}
