////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/copy.hpp
/// @brief   The BLAS COPY routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_COPY_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_COPY_HPP_

#include <mcnla/core/matrix.hpp>
#include <mcnla/core/blas/blas/copy.hpp>

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
/// @brief  Copies vector to another vector.
///
//@{
template <typename _Scalar>
inline void copy(
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &y
) noexcept {
  assert(x.getSizes() == y.getSizes());
  detail::copy(x.getLength(), x.getValue(), x.getStride(), y.getValue(), y.getStride());
}

template <typename _Scalar>
inline void copy(
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &&y
) noexcept {
  copy(x, y);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas1_module
/// @brief  Copies matrix to another matrix.
///
/// @attention  The out-of-range spaces are also copied. It is efficient if the leading dimension is much larger than the size.
///
//@{
template <typename _Scalar, Layout _layout>
inline void copy(
    const DenseMatrix<_Scalar, _layout> &x,
          DenseMatrix<_Scalar, _layout> &y
) noexcept {
  assert(x.getSizes() == y.getSizes() && y.getPitch() == x.getPitch());
  copy(x.vectorize(), y.vectorize());
}

template <typename _Scalar, Layout _layout>
inline void copy(
    const DenseMatrix<_Scalar, _layout> &x,
          DenseMatrix<_Scalar, _layout> &&y
) noexcept {
  assert(x.getSizes() == y.getSizes() && y.getPitch() == x.getPitch());
  copy(x.vectorize(), y.vectorize());
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas1_module
/// @brief  Copies cube to another cube.
///
/// @attention  The out-of-range spaces are also copied. It is efficient if the dimensions is much larger than the sizes.
///
//@{
template <typename _Scalar, Layout _layout>
inline void copy(
    const DenseCube<_Scalar, _layout> &x,
          DenseCube<_Scalar, _layout> &y
) noexcept {
  assert(x.getSizes() == y.getSizes() && y.getPitches() == x.getPitches());
  copy(x.vectorize(), y.vectorize());
}

template <typename _Scalar, Layout _layout>
inline void copy(
    const DenseCube<_Scalar, _layout> &x,
          DenseCube<_Scalar, _layout> &&y
) noexcept {
  assert(x.getSizes() == y.getSizes() && y.getPitches() == x.getPitches());
  copy(x.vectorize(), y.vectorize());
}
//@}

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_COPY_HPP_
