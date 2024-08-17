//===-- OR1K.td - Describe the OR1K Target -------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// OR1K subtarget features and instruction predicates.
//===----------------------------------------------------------------------===//

// OR1K is divided into two versions, the 32-bit version (LA32) and the
// 64-bit version (LA64).
def Feature64Bit
    : SubtargetFeature<"64bit", "HasLA64", "true",
                       "LA64 Basic Integer and Privilege Instruction Set">;
def IsLA64
    : Predicate<"Subtarget->is64Bit()">,
      AssemblerPredicate<(all_of Feature64Bit),
                         "LA64 Basic Integer and Privilege Instruction Set">;
def IsLA32
    : Predicate<"!Subtarget->is64Bit()">,
      AssemblerPredicate<(all_of(not Feature64Bit)),
                         "LA32 Basic Integer and Privilege Instruction Set">;

defvar LA32 = DefaultMode;
def LA64 : HwMode<"+64bit", [IsLA64]>;

// Single Precision floating point
def FeatureBasicF : SubtargetFeature<"f", "HasBasicF", "true",
                                     "'F' (Single-Precision Floating-Point)">;
def HasBasicF : Predicate<"Subtarget->hasBasicF()">,
                AssemblerPredicate<(all_of FeatureBasicF),
                                   "'F' (Single-Precision Floating-Point)">;

// Double Precision floating point
def FeatureBasicD : SubtargetFeature<"d", "HasBasicD", "true",
                                     "'D' (Double-Precision Floating-Point)",
                                     [FeatureBasicF]>;
def HasBasicD : Predicate<"Subtarget->hasBasicD()">,
                AssemblerPredicate<(all_of FeatureBasicD),
                                   "'D' (Double-Precision Floating-Point)">;

// OR1K SIMD eXtension (LSX)
def FeatureExtLSX
    : SubtargetFeature<"lsx", "HasExtLSX", "true",
                       "'LSX' (OR1K SIMD Extension)", [FeatureBasicD]>;
def HasExtLSX : Predicate<"Subtarget->hasExtLSX()">,
                AssemblerPredicate<(all_of FeatureExtLSX),
                                   "'LSX' (OR1K SIMD Extension)">;

// OR1K Advanced SIMD eXtension (LASX)
def FeatureExtLASX
    : SubtargetFeature<"lasx", "HasExtLASX", "true",
                       "'LASX' (OR1K Advanced SIMD Extension)",
                       [FeatureExtLSX]>;
def HasExtLASX
    : Predicate<"Subtarget->hasExtLASX()">,
      AssemblerPredicate<(all_of FeatureExtLASX),
                         "'LASX' (OR1K Advanced SIMD Extension)">;

// OR1K VirtualiZation (LVZ)
def FeatureExtLVZ
    : SubtargetFeature<"lvz", "HasExtLVZ", "true",
                       "'LVZ' (OR1K Virtualization Extension)">;
def HasExtLVZ : Predicate<"Subtarget->hasExtLVZ()">,
                AssemblerPredicate<(all_of FeatureExtLVZ),
                                   "'LVZ' (OR1K Virtualization Extension)">;

// OR1K Binary Translation (LBT)
def FeatureExtLBT
    : SubtargetFeature<"lbt", "HasExtLBT", "true",
                       "'LBT' (OR1K Binary Translation Extension)">;
def HasExtLBT
    : Predicate<"Subtarget->hasExtLBT()">,
      AssemblerPredicate<(all_of FeatureExtLBT),
                         "'LBT' (OR1K Binary Translation Extension)">;

//===----------------------------------------------------------------------===//
// Registers, instruction descriptions ...
//===----------------------------------------------------------------------===//

include "OR1KRegisterInfo.td"
include "OR1KCallingConv.td"
include "OR1KInstrInfo.td"

//===----------------------------------------------------------------------===//
// OR1K processors supported.
//===----------------------------------------------------------------------===//

def : ProcessorModel<"generic-la32", NoSchedModel, []>;
def : ProcessorModel<"generic-la64", NoSchedModel, [Feature64Bit]>;

def : ProcessorModel<"la464", NoSchedModel, [Feature64Bit,
                                             FeatureExtLASX,
                                             FeatureExtLVZ,
                                             FeatureExtLBT]>;

//===----------------------------------------------------------------------===//
// Define the OR1K target.
//===----------------------------------------------------------------------===//

def OR1KInstrInfo : InstrInfo {
  // guess mayLoad, mayStore, and hasSideEffects
  // This option is a temporary migration help. It will go away.
  let guessInstructionProperties = 1;
}

def OR1KAsmParser : AsmParser {
  let ShouldEmitMatchRegisterAltName = 1;
  let AllowDuplicateRegisterNames = 1;
}

def OR1KAsmParserVariant : AsmParserVariant {
  int Variant = 0;
  // Recognize hard coded registers.
  string RegisterPrefix = "$";
}

def OR1KAsmWriter : AsmWriter {
  int PassSubtarget = 1;
}

def OR1K : Target {
  let InstructionSet = OR1KInstrInfo;
  let AssemblyParsers = [OR1KAsmParser];
  let AssemblyParserVariants = [OR1KAsmParserVariant];
  let AssemblyWriters = [OR1KAsmWriter];
  let AllowRegisterRenaming = 1;
}
