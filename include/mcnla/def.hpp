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
#include <iostream>
#include <type_traits>
#include <mcnla/config.hpp>

#define MCNLA_( ... ) __VA_ARGS__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The MCNLA namespace
///
namespace mcnla {

/// @ingroup  core_module
/// The type of index.
#ifndef MCNLA_USE_ILP64
using index_t = std::int32_t;
#else  // MCNLA_USE_ILP64
using index_t = std::int64_t;
#endif  // MCNLA_USE_ILP64

/// @ingroup  core_module
/// The type of size.
using size_t = std::size_t;

/// @ingroup  core_module
/// The format width
static constexpr size_t kOsValWidth = 14;
static constexpr size_t kOsIdxWidth = 6;

/// @ingroup  core_module
/// The block size
static constexpr index_t kBlockSize = 64;

/// @ingroup  core_module
/// The index type literal.
static inline mcnla::index_t operator"" _i( unsigned long long int idx ) { return idx; }

}  // namespace mcnla

#ifndef MCNLA_DISABLE_LITERAL
using mcnla::operator"" _i;
#endif  // MCNLA_DISABLE_LITERAL

#ifdef MCNLA_USE_MKL
#define MKL_INT mcnla::index_t
#define MKL_Complex8 std::complex<float>
#define MKL_Complex16 std::complex<double>
#endif  // MCNLA_USE_MKL

/// @ingroup  core_module
//@{
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

#define mcnla_assert_pass( condition )  { auto err = condition; static_cast<void>(err); mcnla_assert_eq(err, 0); }
//@}

/// @ingroup  core_module
#define disp( expression ) std::cout << #expression << ":\n" << expression << std::endl;

/// @ingroup  core_module
#ifdef NDEBUG
  #define warning( expression ) static_cast<void>(0)
#else  // NDEBUG
  #ifndef MCNLA_USE_GTEST
    #define warning( expression ) std::cout << "Warning: " << #expression << std::endl;
  #else  // MCNLA_USE_GTEST
    #define warning( expression ) FAIL() << "Warning: " << #expression << std::endl;
  #endif  // MCNLA_USE_GTEST
#endif  // NDEBUG

#endif  // MCNLA_DEF_HPP_
