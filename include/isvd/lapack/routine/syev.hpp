////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/routine/syev.hpp
/// @brief   The LAPACK SYEV routine.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_ROUTINE_SYEV_HPP_
#define ISVD_LAPACK_ROUTINE_SYEV_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix.hpp>
#include <isvd/lapack/lapack.hpp>
#include <isvd/lapack/driver/syev.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::lapack::SyevDriver::compute
///
//@{
template <JobOption _jobz, UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline void syev(
    DenseMatrix<_Scalar, _layout> &a,
    DenseVector<typename isvd::detail::ScalarTraits<_Scalar>::RealType> &w
) noexcept {
  SyevDriver<DenseMatrix<_Scalar, _layout>, _jobz, _uplo> driver(a);
  driver(a, w);
}
template <JobOption _jobz, UploOption _uplo = UploOption::LOWER, class _TypeA, class _TypeW>
inline void syev( _TypeA &&a, _TypeW &&w ) noexcept {
  syev<_jobz, _uplo>(a, w);
}
//@}

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_ROUTINE_SYEV_HPP_
