////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/memset0.hpp
/// @brief   The BLAS MEMSET0 routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_MEMSET0_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_MEMSET0_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/utility.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1_module
/// @brief  Set a vector to zero.
///
template <typename _Val>
inline void memset0(
  DenseVector<_Val> &x
) noexcept {
  mcnla_assert_true(x.isShrunk());
  utility::memset0(x.valPtr(), x.nelem());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void memset0(
  DenseVector<_Val> &&x
) noexcept {
  memset0(x);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1m_module
/// @brief  Set a matrix to zero.
///
template <typename _Val, Trans _trans>
inline void memset0(
  DenseMatrix<_Val, _trans> &a
) noexcept {
  mcnla_assert_true(a.isShrunk());
  utility::memset0(a.valPtr(), a.nelem());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
inline void memset0(
  DenseMatrix<_Val, _trans> &&a
) noexcept {
  memset0(a);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_MEMSET0_HPP_
