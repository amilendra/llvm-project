//===-- Implementation of the frexp function for GPU ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "src/math/frexp.h"
#include "src/__support/common.h"

#include "src/__support/macros/config.h"

namespace LIBC_NAMESPACE_DECL {

LLVM_LIBC_FUNCTION(double, frexp, (double x, int *p)) {
  return __builtin_frexp(x, p);
}

} // namespace LIBC_NAMESPACE_DECL
