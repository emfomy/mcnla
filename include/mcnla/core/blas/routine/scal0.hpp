////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/scal0.hpp
/// @brief   The BLAS SCAL0 routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_SCAL0_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_SCAL0_HPP_

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
/// @brief  Computes the product of a vector by zero.
///
/// @attention  It is inefficient if the stride is not 1.
///             Uses memset0 instead if the out-of-range spaces are useless.
/// @attention  However, memset0 is slow if the stride is vary large.
///
template <typename _Scalar>
inline void scal0(
  DenseVector<_Scalar> &x
) noexcept {
  if ( x.isShrunk() ) {
    std::memset(x.getValue(), 0, x.getNelem() * sizeof(_Scalar));
  } else {
    x.getValueValarray()[x.getValueMask()] = 0;
  }
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void scal0(
  DenseVector<_Scalar> &&x
) noexcept {
  scal0(x);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas1_module
/// @brief  Computes the product of a matrix by zero.
///
/// @attention  It is inefficient if the pitch is different from the size.
///             Uses memset0 instead if the out-of-range spaces are useless.
/// @attention  However, memset0 is slow if the pitch is vary large.
///
template <typename _Scalar, Layout _layout>
inline void scal0(
  DenseMatrix<_Scalar, _layout> &x
) noexcept {
  if ( x.isShrunk() ) {
    std::memset(x.getValue(), 0, x.getNelem() * sizeof(_Scalar));
  } else {
    x.getValueValarray()[x.getValueMask()] = 0;
  }
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout>
inline void scal0(
  DenseMatrix<_Scalar, _layout> &&x
) noexcept {
  scal0(x);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas1_module
/// @brief  Computes the product of a cube by zero.
///
/// @attention  It is inefficient if the pitches is different from the sizes.
///             Uses memset0 instead if the out-of-range spaces are useless.
/// @attention  However, memset0 is slow if the pitch is vary large.
///
template <typename _Scalar, Layout _layout>
inline void scal0(
  DenseCube<_Scalar, _layout> &x
) noexcept {
  if ( x.isShrunk() ) {
    std::memset(x.getValue(), 0, x.getNelem() * sizeof(_Scalar));
  } else {
    x.getValueValarray()[x.getValueMask()] = 0;
  }
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout>
inline void scal0(
  DenseCube<_Scalar, _layout> &&x
) noexcept {
  scal0(x);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_SCAL0_HPP_