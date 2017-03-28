////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/def.hpp
/// @brief   The MCNLA definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_DEF_HPP_
#define MCNLA_DEF_HPP_

#ifndef __cplusplus
#error C++ is required.
#elif __cplusplus < 201103L
#warning C++11 is required.
#endif

#include <cassert>
#include <cstdint>
#include <cmath>
#include <complex>
#include <type_traits>
#include <mcnla/config.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The MCNLA namespace
///
namespace mcnla {

/// The type of index.
#ifndef MCNLA_USE_ILP64
using index_t = std::int32_t;
#else  // MCNLA_USE_ILP64
using index_t = std::int64_t;
#endif  // MCNLA_USE_ILP64

/// The type of size.
using size_t = std::size_t;

/// The format width
static constexpr size_t kOsValWidth = 14;
static constexpr size_t kOsIdxWidth = 6;

}  // namespace mcnla

#ifdef MCNLA_USE_MKL
#define MKL_Complex8 std::complex<float>
#define MKL_Complex16 std::complex<double>
#define MKL_INT mcnla::index_t
#endif  // MCNLA_USE_MKL

#ifndef MCNLA_USE_GTEST

#define mcnla_assert_true( condition )   assert(condition);
#define mcnla_assert_false( condition )  assert(!(condition));

#define mcnla_assert_eq( val1, val2 )  assert(val1 == val2);
#define mcnla_assert_ne( val1, val2 )  assert(val1 != val2);
#define mcnla_assert_lt( val1, val2 )  assert(val1 <  val2);
#define mcnla_assert_le( val1, val2 )  assert(val1 <= val2);
#define mcnla_assert_gt( val1, val2 )  assert(val1 >  val2);
#define mcnla_assert_ge( val1, val2 )  assert(val1 >= val2);

#define mcnla_assert_gtlt( val, bound1, bound2 )  assert(val >  bound1 && val <  bound2);
#define mcnla_assert_gtle( val, bound1, bound2 )  assert(val >  bound1 && val <= bound2);
#define mcnla_assert_gelt( val, bound1, bound2 )  assert(val >= bound1 && val <  bound2);
#define mcnla_assert_gele( val, bound1, bound2 )  assert(val >= bound1 && val <= bound2);

#else  // MCNLA_USE_GTEST

#define mcnla_assert_true( condition )   EXPECT_TRUE(condition);
#define mcnla_assert_false( condition )  EXPECT_FALSE(condition);

#define mcnla_assert_eq( val1, val2 )  EXPECT_EQ(val1, val2);
#define mcnla_assert_ne( val1, val2 )  EXPECT_NE(val1, val2);
#define mcnla_assert_lt( val1, val2 )  EXPECT_LT(val1, val2);
#define mcnla_assert_le( val1, val2 )  EXPECT_LE(val1, val2);
#define mcnla_assert_gt( val1, val2 )  EXPECT_GT(val1, val2);
#define mcnla_assert_ge( val1, val2 )  EXPECT_GE(val1, val2);

#define mcnla_assert_gtlt( val, bound1, bound2 )  { EXPECT_GT(val, bound1); EXPECT_LT(val, bound2); }
#define mcnla_assert_gtle( val, bound1, bound2 )  { EXPECT_GT(val, bound1); EXPECT_LE(val, bound2); }
#define mcnla_assert_gelt( val, bound1, bound2 )  { EXPECT_GE(val, bound1); EXPECT_LT(val, bound2); }
#define mcnla_assert_gele( val, bound1, bound2 )  { EXPECT_GE(val, bound1); EXPECT_LE(val, bound2); }

#endif  // MCNLA_USE_GTEST

#endif  // MCNLA_DEF_HPP_
