//===-- Implementation file of __libc_fini_array --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "startup/baremetal/fini.h"

#include "src/__support/macros/config.h"
#include <stddef.h>

namespace LIBC_NAMESPACE_DECL {

using FiniCallback = void(void);

extern "C" void __libc_fini_array(void) {
  size_t fini_array_size = __fini_array_end - __fini_array_start;
  for (size_t i = fini_array_size; i > 0; --i)
    reinterpret_cast<FiniCallback *>(__fini_array_start[i - 1])();
}

} // namespace LIBC_NAMESPACE_DECL
