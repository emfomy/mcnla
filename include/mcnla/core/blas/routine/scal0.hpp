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
/// @attention  The out-of-range spaces are also copied. It is efficient if the stride is much larger.
///
//@{
template <typename _Scalar>
inline void scal0(
  DenseVector<_Scalar> &x
) noexcept {
  std::memset(x.getValue(), 0, x.getLength() * x.getStride() * sizeof(_Scalar));
}

template <typename _Scalar>
inline void scal0(
  DenseVector<_Scalar> &&x
) noexcept {
  scal0(x);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas1_module
/// @brief  Computes the product of a matrix by zero.
///
/// @attention  The out-of-range spaces are also copied. It is efficient if the leading dimension is much larger than the size.
///
//@{
template <typename _Scalar, Layout _layout>
inline void scal0(
  DenseMatrix<_Scalar, _layout> &x
) noexcept {
  scal0(x.vectorize());
}

template <typename _Scalar, Layout _layout>
inline void scal0(
  DenseMatrix<_Scalar, _layout> &&x
) noexcept {
  scal0(x.vectorize());
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas1_module
/// @brief  Computes the product of a cube by zero.
///
/// @attention  The out-of-range spaces are also copied. It is efficient if the pitches is much larger than the sizes.
///
//@{
template <typename _Scalar, Layout _layout>
inline void scal0(
  DenseCube<_Scalar, _layout> &x
) noexcept {
  scal0(x.vectorize());
}

template <typename _Scalar, Layout _layout>
inline void scal0(
  DenseCube<_Scalar, _layout> &&x
) noexcept {
  scal0(x.vectorize());
}
//@}

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_SCAL0_HPP_
