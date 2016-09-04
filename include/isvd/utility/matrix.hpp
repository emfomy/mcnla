////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/utility/matrix.hpp
/// @brief   The matrix utilities.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_UTILITY_MATRIX_HPP_
#define ISVD_UTILITY_MATRIX_HPP_

#include <cstring>
#include <isvd/matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Set the vector to zero.
///
//@{
template <typename _Scalar>
inline void zeroize(
  DenseVector<_Scalar> &x
) noexcept {
  std::memset(x.getValue, 0, x.getLength() * x.getIncrement * sizeof(_Scalar));
}

template <typename _Scalar>
inline void zeroize(
  DenseVector<_Scalar> &&x
) noexcept {
  zeroize(x);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Set the matrix to zero.
///
/// @attention  The out-of-range spaces are also copied. It is efficient if the leading dimension is much larger than the size.
///
//@{
template <typename _Scalar, Layout _layout>
inline void zeroize(
  DenseMatrix<_Scalar, _layout> &x
) noexcept {
  zeroize(x.vectorize());
}

template <typename _Scalar, Layout _layout>
inline void zeroize(
  DenseMatrix<_Scalar, _layout> &&x
) noexcept {
  zeroize(x.vectorize());
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Set the cube to zero.
///
/// @attention  The out-of-range spaces are also copied. It is efficient if the dimensions is much larger than the sizes.
///
//@{
template <typename _Scalar, Layout _layout>
inline void zeroize(
  DenseCube<_Scalar, _layout> &x
) noexcept {
  zeroize(x.vectorize());
}

template <typename _Scalar, Layout _layout>
inline void zeroize(
  DenseCube<_Scalar, _layout> &&x
) noexcept {
  zeroize(x.vectorize());
}
//@}

}  // namespace isvd

#endif  // ISVD_UTILITY_MATRIX_HPP_
