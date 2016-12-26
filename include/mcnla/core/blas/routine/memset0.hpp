////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/memset0.hpp
/// @brief   The BLAS MEMSET0 routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_MEMSET0_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_MEMSET0_HPP_

#include <cstring>
#include <mcnla/core/matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas1_module
/// @brief  Set a vector to zero.
///
/// @attention  the out-of-range spaces are also changed.
///
template <typename _Scalar>
inline void memset0(
  DenseVector<_Scalar> &x
) noexcept {
  std::memset(x.getValuePtr(), 0, x.getNelem() * sizeof(_Scalar));
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void memset0(
  DenseVector<_Scalar> &&x
) noexcept {
  memset0(x);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas1_module
/// @brief  Set a matrix to zero.
///
/// @attention  the out-of-range spaces are also changed.
///
template <typename _Scalar, Trans _trans>
inline void memset0(
  DenseMatrix<_Scalar, _trans> &x
) noexcept {
  std::memset(x.getValuePtr(), 0, x.getNelem() * sizeof(_Scalar));
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _trans>
inline void memset0(
  DenseMatrix<_Scalar, _trans> &&x
) noexcept {
  memset0(x);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_MEMSET0_HPP_
