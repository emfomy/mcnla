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
template <typename _Scalar>
inline void copy(
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &y
) noexcept {
  mcnla_assert_eq(x.getSizes(), y.getSizes());
  detail::copy(x.getLength(), x.getValuePtr(), x.getStride(), y.getValuePtr(), y.getStride());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void copy(
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &&y
) noexcept {
  copy(x, y);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas1_module
/// @brief  Copies matrix to another matrix.
///
/// @attention  The out-of-range spaces are also copied. It is inefficient if the maximum size in the first dimension is much larger than the size.
///
template <typename _Scalar, Layout _layout>
inline void copy(
    const DenseMatrix<_Scalar, _layout> &x,
          DenseMatrix<_Scalar, _layout> &y
) noexcept {
  mcnla_assert_eq(x.getSizes(), y.getSizes());
  mcnla_assert_eq(x.getPitch(), y.getPitch());
  copy(x.vectorize(), y.vectorize());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout>
inline void copy(
    const DenseMatrix<_Scalar, _layout> &x,
          DenseMatrix<_Scalar, _layout> &&y
) noexcept {
  mcnla_assert_eq(x.getSizes(), y.getSizes());
  mcnla_assert_eq(x.getPitch(), y.getPitch());
  copy(x.vectorize(), y.vectorize());
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_COPY_HPP_
