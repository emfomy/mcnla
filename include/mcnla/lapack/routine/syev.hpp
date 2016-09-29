////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/lapack/routine/syev.hpp
/// @brief   The LAPACK SYEV routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_LAPACK_ROUTINE_SYEV_HPP_
#define MCNLA_LAPACK_ROUTINE_SYEV_HPP_

#include <mcnla/mcnla.hpp>
#include <mcnla/matrix.hpp>
#include <mcnla/lapack/lapack.hpp>
#include <mcnla/lapack/driver/syev.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::lapack::SyevDriver::compute
///
//@{
template <JobOption _jobz, UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline void syev(
    DenseMatrix<_Scalar, _layout> &a,
    DenseVector<typename mcnla::detail::ScalarTraits<_Scalar>::RealType> &w
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

}  // namespace mcnla

#endif  // MCNLA_LAPACK_ROUTINE_SYEV_HPP_
