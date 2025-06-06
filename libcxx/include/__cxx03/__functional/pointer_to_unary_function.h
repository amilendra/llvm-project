// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___CXX03___FUNCTIONAL_POINTER_TO_UNARY_FUNCTION_H
#define _LIBCPP___CXX03___FUNCTIONAL_POINTER_TO_UNARY_FUNCTION_H

#include <__cxx03/__config>
#include <__cxx03/__functional/unary_function.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

template <class _Arg, class _Result>
class _LIBCPP_TEMPLATE_VIS pointer_to_unary_function : public __unary_function<_Arg, _Result> {
  _Result (*__f_)(_Arg);

public:
  _LIBCPP_HIDE_FROM_ABI explicit pointer_to_unary_function(_Result (*__f)(_Arg)) : __f_(__f) {}
  _LIBCPP_HIDE_FROM_ABI _Result operator()(_Arg __x) const { return __f_(__x); }
};

template <class _Arg, class _Result>
inline _LIBCPP_HIDE_FROM_ABI pointer_to_unary_function<_Arg, _Result> ptr_fun(_Result (*__f)(_Arg)) {
  return pointer_to_unary_function<_Arg, _Result>(__f);
}

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___CXX03___FUNCTIONAL_POINTER_TO_UNARY_FUNCTION_H
