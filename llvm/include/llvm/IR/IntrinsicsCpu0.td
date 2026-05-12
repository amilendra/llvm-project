//===- IntrinsicsCpu0.td - Defines Mips intrinsics ---------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines all of the CPU0-specific intrinsics.
//
//===----------------------------------------------------------------------===//

// __builtin_cpu0_gcd defined in
// https://github.com/Jonathan2251/lbt/blob/master/exlbt/clang/include/clang/Basic/BuiltinsCpu0.def
let TargetPrefix = "cpu0" in {  // All intrinsics start with "llvm.cpu0.".
def int_cpu0_gcd : ClangBuiltin<"__builtin_cpu0_gcd">,
  Intrinsic<[llvm_i32_ty], [llvm_i32_ty, llvm_i32_ty],
  [Commutative, IntrNoMem]>;
}