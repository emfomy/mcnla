////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/kit/zeroize.hpp
/// @brief   The zeroize routines.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_KIT_ZEROIZE_HPP_
#define MCNLA_CORE_MATRIX_KIT_ZEROIZE_HPP_

#include <cstring>
#include <mcnla/core/matrix/dense.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Set the vector to zero.
///
//@{
template <typename _Scalar>
inline void zeroize(
  DenseVector<_Scalar> &x
) noexcept {
  std::memset(x.getValue(), 0, x.getLength() * x.getStride() * sizeof(_Scalar));
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

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_KIT_ZEROIZE_HPP_
