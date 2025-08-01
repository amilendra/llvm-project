//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// WARNING: This test was generated by generate_feature_test_macro_components.py
// and should not be edited manually.

// <tuple>

// Test the feature test macros defined by <tuple>

// clang-format off

#include <tuple>
#include "test_macros.h"

#if TEST_STD_VER < 14

#  ifdef __cpp_lib_apply
#    error "__cpp_lib_apply should not be defined before c++17"
#  endif

#  ifdef __cpp_lib_constexpr_tuple
#    error "__cpp_lib_constexpr_tuple should not be defined before c++20"
#  endif

#  ifdef __cpp_lib_constrained_equality
#    error "__cpp_lib_constrained_equality should not be defined before c++26"
#  endif

#  ifdef __cpp_lib_make_from_tuple
#    error "__cpp_lib_make_from_tuple should not be defined before c++17"
#  endif

#  ifdef __cpp_lib_ranges_zip
#    error "__cpp_lib_ranges_zip should not be defined before c++23"
#  endif

#  ifdef __cpp_lib_tuple_element_t
#    error "__cpp_lib_tuple_element_t should not be defined before c++14"
#  endif

#  ifdef __cpp_lib_tuple_like
#    error "__cpp_lib_tuple_like should not be defined before c++23"
#  endif

#  ifdef __cpp_lib_tuples_by_type
#    error "__cpp_lib_tuples_by_type should not be defined before c++14"
#  endif

#elif TEST_STD_VER == 14

#  ifdef __cpp_lib_apply
#    error "__cpp_lib_apply should not be defined before c++17"
#  endif

#  ifdef __cpp_lib_constexpr_tuple
#    error "__cpp_lib_constexpr_tuple should not be defined before c++20"
#  endif

#  ifdef __cpp_lib_constrained_equality
#    error "__cpp_lib_constrained_equality should not be defined before c++26"
#  endif

#  ifdef __cpp_lib_make_from_tuple
#    error "__cpp_lib_make_from_tuple should not be defined before c++17"
#  endif

#  ifdef __cpp_lib_ranges_zip
#    error "__cpp_lib_ranges_zip should not be defined before c++23"
#  endif

#  ifndef __cpp_lib_tuple_element_t
#    error "__cpp_lib_tuple_element_t should be defined in c++14"
#  endif
#  if __cpp_lib_tuple_element_t != 201402L
#    error "__cpp_lib_tuple_element_t should have the value 201402L in c++14"
#  endif

#  ifdef __cpp_lib_tuple_like
#    error "__cpp_lib_tuple_like should not be defined before c++23"
#  endif

#  ifndef __cpp_lib_tuples_by_type
#    error "__cpp_lib_tuples_by_type should be defined in c++14"
#  endif
#  if __cpp_lib_tuples_by_type != 201304L
#    error "__cpp_lib_tuples_by_type should have the value 201304L in c++14"
#  endif

#elif TEST_STD_VER == 17

#  ifndef __cpp_lib_apply
#    error "__cpp_lib_apply should be defined in c++17"
#  endif
#  if __cpp_lib_apply != 201603L
#    error "__cpp_lib_apply should have the value 201603L in c++17"
#  endif

#  ifdef __cpp_lib_constexpr_tuple
#    error "__cpp_lib_constexpr_tuple should not be defined before c++20"
#  endif

#  ifdef __cpp_lib_constrained_equality
#    error "__cpp_lib_constrained_equality should not be defined before c++26"
#  endif

#  ifndef __cpp_lib_make_from_tuple
#    error "__cpp_lib_make_from_tuple should be defined in c++17"
#  endif
#  if __cpp_lib_make_from_tuple != 201606L
#    error "__cpp_lib_make_from_tuple should have the value 201606L in c++17"
#  endif

#  ifdef __cpp_lib_ranges_zip
#    error "__cpp_lib_ranges_zip should not be defined before c++23"
#  endif

#  ifndef __cpp_lib_tuple_element_t
#    error "__cpp_lib_tuple_element_t should be defined in c++17"
#  endif
#  if __cpp_lib_tuple_element_t != 201402L
#    error "__cpp_lib_tuple_element_t should have the value 201402L in c++17"
#  endif

#  ifdef __cpp_lib_tuple_like
#    error "__cpp_lib_tuple_like should not be defined before c++23"
#  endif

#  ifndef __cpp_lib_tuples_by_type
#    error "__cpp_lib_tuples_by_type should be defined in c++17"
#  endif
#  if __cpp_lib_tuples_by_type != 201304L
#    error "__cpp_lib_tuples_by_type should have the value 201304L in c++17"
#  endif

#elif TEST_STD_VER == 20

#  ifndef __cpp_lib_apply
#    error "__cpp_lib_apply should be defined in c++20"
#  endif
#  if __cpp_lib_apply != 201603L
#    error "__cpp_lib_apply should have the value 201603L in c++20"
#  endif

#  ifndef __cpp_lib_constexpr_tuple
#    error "__cpp_lib_constexpr_tuple should be defined in c++20"
#  endif
#  if __cpp_lib_constexpr_tuple != 201811L
#    error "__cpp_lib_constexpr_tuple should have the value 201811L in c++20"
#  endif

#  ifdef __cpp_lib_constrained_equality
#    error "__cpp_lib_constrained_equality should not be defined before c++26"
#  endif

#  ifndef __cpp_lib_make_from_tuple
#    error "__cpp_lib_make_from_tuple should be defined in c++20"
#  endif
#  if __cpp_lib_make_from_tuple != 201606L
#    error "__cpp_lib_make_from_tuple should have the value 201606L in c++20"
#  endif

#  ifdef __cpp_lib_ranges_zip
#    error "__cpp_lib_ranges_zip should not be defined before c++23"
#  endif

#  ifndef __cpp_lib_tuple_element_t
#    error "__cpp_lib_tuple_element_t should be defined in c++20"
#  endif
#  if __cpp_lib_tuple_element_t != 201402L
#    error "__cpp_lib_tuple_element_t should have the value 201402L in c++20"
#  endif

#  ifdef __cpp_lib_tuple_like
#    error "__cpp_lib_tuple_like should not be defined before c++23"
#  endif

#  ifndef __cpp_lib_tuples_by_type
#    error "__cpp_lib_tuples_by_type should be defined in c++20"
#  endif
#  if __cpp_lib_tuples_by_type != 201304L
#    error "__cpp_lib_tuples_by_type should have the value 201304L in c++20"
#  endif

#elif TEST_STD_VER == 23

#  ifndef __cpp_lib_apply
#    error "__cpp_lib_apply should be defined in c++23"
#  endif
#  if __cpp_lib_apply != 201603L
#    error "__cpp_lib_apply should have the value 201603L in c++23"
#  endif

#  ifndef __cpp_lib_constexpr_tuple
#    error "__cpp_lib_constexpr_tuple should be defined in c++23"
#  endif
#  if __cpp_lib_constexpr_tuple != 201811L
#    error "__cpp_lib_constexpr_tuple should have the value 201811L in c++23"
#  endif

#  ifdef __cpp_lib_constrained_equality
#    error "__cpp_lib_constrained_equality should not be defined before c++26"
#  endif

#  ifndef __cpp_lib_make_from_tuple
#    error "__cpp_lib_make_from_tuple should be defined in c++23"
#  endif
#  if __cpp_lib_make_from_tuple != 201606L
#    error "__cpp_lib_make_from_tuple should have the value 201606L in c++23"
#  endif

#  if !defined(_LIBCPP_VERSION)
#    ifndef __cpp_lib_ranges_zip
#      error "__cpp_lib_ranges_zip should be defined in c++23"
#    endif
#    if __cpp_lib_ranges_zip != 202110L
#      error "__cpp_lib_ranges_zip should have the value 202110L in c++23"
#    endif
#  else
#    ifdef __cpp_lib_ranges_zip
#      error "__cpp_lib_ranges_zip should not be defined because it is unimplemented in libc++!"
#    endif
#  endif

#  ifndef __cpp_lib_tuple_element_t
#    error "__cpp_lib_tuple_element_t should be defined in c++23"
#  endif
#  if __cpp_lib_tuple_element_t != 201402L
#    error "__cpp_lib_tuple_element_t should have the value 201402L in c++23"
#  endif

#  if !defined(_LIBCPP_VERSION)
#    ifndef __cpp_lib_tuple_like
#      error "__cpp_lib_tuple_like should be defined in c++23"
#    endif
#    if __cpp_lib_tuple_like != 202207L
#      error "__cpp_lib_tuple_like should have the value 202207L in c++23"
#    endif
#  else
#    ifdef __cpp_lib_tuple_like
#      error "__cpp_lib_tuple_like should not be defined because it is unimplemented in libc++!"
#    endif
#  endif

#  ifndef __cpp_lib_tuples_by_type
#    error "__cpp_lib_tuples_by_type should be defined in c++23"
#  endif
#  if __cpp_lib_tuples_by_type != 201304L
#    error "__cpp_lib_tuples_by_type should have the value 201304L in c++23"
#  endif

#elif TEST_STD_VER > 23

#  ifndef __cpp_lib_apply
#    error "__cpp_lib_apply should be defined in c++26"
#  endif
#  if __cpp_lib_apply != 201603L
#    error "__cpp_lib_apply should have the value 201603L in c++26"
#  endif

#  ifndef __cpp_lib_constexpr_tuple
#    error "__cpp_lib_constexpr_tuple should be defined in c++26"
#  endif
#  if __cpp_lib_constexpr_tuple != 201811L
#    error "__cpp_lib_constexpr_tuple should have the value 201811L in c++26"
#  endif

#  ifndef __cpp_lib_constrained_equality
#    error "__cpp_lib_constrained_equality should be defined in c++26"
#  endif
#  if __cpp_lib_constrained_equality != 202411L
#    error "__cpp_lib_constrained_equality should have the value 202411L in c++26"
#  endif

#  ifndef __cpp_lib_make_from_tuple
#    error "__cpp_lib_make_from_tuple should be defined in c++26"
#  endif
#  if __cpp_lib_make_from_tuple != 201606L
#    error "__cpp_lib_make_from_tuple should have the value 201606L in c++26"
#  endif

#  if !defined(_LIBCPP_VERSION)
#    ifndef __cpp_lib_ranges_zip
#      error "__cpp_lib_ranges_zip should be defined in c++26"
#    endif
#    if __cpp_lib_ranges_zip != 202110L
#      error "__cpp_lib_ranges_zip should have the value 202110L in c++26"
#    endif
#  else
#    ifdef __cpp_lib_ranges_zip
#      error "__cpp_lib_ranges_zip should not be defined because it is unimplemented in libc++!"
#    endif
#  endif

#  ifndef __cpp_lib_tuple_element_t
#    error "__cpp_lib_tuple_element_t should be defined in c++26"
#  endif
#  if __cpp_lib_tuple_element_t != 201402L
#    error "__cpp_lib_tuple_element_t should have the value 201402L in c++26"
#  endif

#  if !defined(_LIBCPP_VERSION)
#    ifndef __cpp_lib_tuple_like
#      error "__cpp_lib_tuple_like should be defined in c++26"
#    endif
#    if __cpp_lib_tuple_like != 202311L
#      error "__cpp_lib_tuple_like should have the value 202311L in c++26"
#    endif
#  else
#    ifdef __cpp_lib_tuple_like
#      error "__cpp_lib_tuple_like should not be defined because it is unimplemented in libc++!"
#    endif
#  endif

#  ifndef __cpp_lib_tuples_by_type
#    error "__cpp_lib_tuples_by_type should be defined in c++26"
#  endif
#  if __cpp_lib_tuples_by_type != 201304L
#    error "__cpp_lib_tuples_by_type should have the value 201304L in c++26"
#  endif

#endif // TEST_STD_VER > 23

// clang-format on
