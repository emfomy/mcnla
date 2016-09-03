////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/routine/copy.hpp
/// @brief   The BLAS COPY routine.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_ROUTINE_COPY_HPP_
#define ISVD_BLAS_ROUTINE_COPY_HPP_

#include <isvd/matrix.hpp>
#include <isvd/blas/blas/copy.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::blas::internal::copy
///
//@{
template <typename _Scalar>
inline void copy(
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &y
) noexcept {
  assert(x.getSizes() == y.getSizes());
  internal::copy(x.getLength(), x.getValue(), x.getIncrement(), y.getValue(), y.getIncrement());
}

template <typename _Scalar>
inline void copy(
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &&y
) noexcept {
  copy(x, y);
}

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

template <typename _Scalar, Layout _layout>
inline void copy(
    const DenseCube<_Scalar, _layout> &x,
          DenseCube<_Scalar, _layout> &y
) noexcept {
  assert(x.getSizes() == y.getSizes() && y.getPitch1() == x.getPitch1() &&  y.getPitch2() == x.getPitch2());
  copy(x.vectorize(), y.vectorize());
}

template <typename _Scalar, Layout _layout>
inline void copy(
    const DenseCube<_Scalar, _layout> &x,
          DenseCube<_Scalar, _layout> &&y
) noexcept {
  assert(x.getSizes() == y.getSizes() && y.getPitch1() == x.getPitch1() &&  y.getPitch2() == x.getPitch2());
  copy(x.vectorize(), y.vectorize());
}
//@}

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_ROUTINE_COPY_HPP_
