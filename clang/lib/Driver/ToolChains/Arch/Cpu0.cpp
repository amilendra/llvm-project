//===--- Cpu0.cpp - Cpu0 Helpers for Tools ------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Cpu0.h"

using namespace clang::driver::tools;
using namespace clang;
using namespace llvm::opt;

StringRef cpu0::getCpu0ABI(const ArgList &Args, const llvm::Triple &Triple) {
  assert((Triple.getArch() == llvm::Triple::cpu0 ||
          Triple.getArch() == llvm::Triple::cpu0el) &&
         "Unexpected triple");

  // If `-mabi=` is specified, use it.
  if (const Arg *A = Args.getLastArg(options::OPT_mabi_EQ))
    return A->getValue();

  // Choose a default based on the triple.
  // TODO: select appropiate ABI.
  return Triple.getArch() == llvm::Triple::cpu0 ? "ilp32d" : "lp64d";
}
