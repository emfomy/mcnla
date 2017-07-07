////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/memset0.hpp
/// @brief   The BLAS MEMSET0 routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_MEMSET0_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_MEMSET0_HPP_

#include <mcnla/core/la/def.hpp>
#include <cstring>
#include <mcnla/core/matrix.hpp>

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
/// @attention  the out-of-range spaces are also changed.
///
template <typename _Val>
inline void memset0(
  DenseVector<_Val> &x
) noexcept {
  std::memset(x.valPtr(), 0, x.nelem() * sizeof(_Val));
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
/// @attention  the out-of-range spaces are also changed.
///
template <typename _Val, Trans _trans>
inline void memset0(
  DenseMatrix<_Val, _trans> &x
) noexcept {
  std::memset(x.valPtr(), 0, x.nelem() * sizeof(_Val));
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
inline void memset0(
  DenseMatrix<_Val, _trans> &&x
) noexcept {
  memset0(x);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_MEMSET0_HPP_
