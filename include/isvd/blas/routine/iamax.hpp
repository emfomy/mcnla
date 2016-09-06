////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/routine/iamax.hpp
/// @brief   The BLAS IAMAX routine.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_ROUTINE_IAMAX_HPP_
#define ISVD_BLAS_ROUTINE_IAMAX_HPP_

#include <cmath>
#include <complex>
#include <isvd/matrix.hpp>
#include <isvd/blas/blas/iamax.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::blas::internal::iamax
///
//@{
template <typename _Scalar>
inline index_t iamax(
    const DenseVector<_Scalar> &x
) noexcept {
  return internal::iamax(x.getLength(), x.getValue(), x.getIncrement());
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the element with maximum absolute value.
///
//@{
template <typename _Scalar>
inline typename isvd::internal::ScalarTraits<_Scalar>::RealType amax(
    const DenseVector<_Scalar> &x
) noexcept {
  index_t idx = internal::iamax(x.getLength(), x.getValue(), x.getIncrement());
  return std::abs(x(idx));
}
//@}

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_ROUTINE_IAMAX_HPP_
