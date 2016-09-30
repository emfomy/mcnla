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
#include <complex>
#include <type_traits>
#include <mcnla/config.hpp>

#ifdef MCNLA_USE_MKL
#define MKL_Complex8 std::complex<float>
#define MKL_Complex16 std::complex<double>
#endif  // MCNLA_USE_MKL

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The MCNLA namespace
///
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The detail namespace.
///
namespace detail {}

}  // namespace mcnla

#endif  // MCNLA_DEF_HPP_
