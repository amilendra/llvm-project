//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___CXX03___TYPE_TRAITS_ALIGNED_UNION_H
#define _LIBCPP___CXX03___TYPE_TRAITS_ALIGNED_UNION_H

#include <__cxx03/__config>
#include <__cxx03/__type_traits/aligned_storage.h>
#include <__cxx03/__type_traits/integral_constant.h>
#include <__cxx03/cstddef>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

template <size_t _I0, size_t... _In>
struct __static_max;

template <size_t _I0>
struct __static_max<_I0> {
  static const size_t value = _I0;
};

template <size_t _I0, size_t _I1, size_t... _In>
struct __static_max<_I0, _I1, _In...> {
  static const size_t value = _I0 >= _I1 ? __static_max<_I0, _In...>::value : __static_max<_I1, _In...>::value;
};

template <size_t _Len, class _Type0, class... _Types>
struct aligned_union {
  static const size_t alignment_value =
      __static_max<_LIBCPP_PREFERRED_ALIGNOF(_Type0), _LIBCPP_PREFERRED_ALIGNOF(_Types)...>::value;
  static const size_t __len = __static_max<_Len, sizeof(_Type0), sizeof(_Types)...>::value;
  typedef typename aligned_storage<__len, alignment_value>::type type;
};

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___CXX03___TYPE_TRAITS_ALIGNED_UNION_H
